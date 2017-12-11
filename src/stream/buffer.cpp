/*
    This file is part of the pm library package.
    Copyright (C) 2017, 2018 Vladislav Podymov
    
    This library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    
    To contact author, email to <vpod@cs.msu.ru>
 */
#include "pm/stream/buffer.hpp"

namespace pm {
namespace stream {

void StringBuffer::clear() {
  while(!chunks_.empty()) {
    chunks_.pop();
  }
}

bool StringBuffer::pop() {
  if(peel_chunks_and_check_if_empty_()) {
    return false;
  }
  pop_from_top_chunk_(1);
  return true;
}

bool StringBuffer::pop(char & c) {
  if(peel_chunks_and_check_if_empty_()) {
    return false;
  }
  read_from_top_chunk_(c);
  return true;
}

size_t StringBuffer::pop(size_t size) {
  if(size == 0 || peel_chunks_and_check_if_empty_()) {
    return 0;
  }
  size_t popped = 0;
  while(!chunks_.empty() && size > top_chunk_occupied_) {
    size -= top_chunk_occupied_;
    popped += top_chunk_occupied_;
    pop_chunk_();
  }
  if(!chunks_.empty() && size > 0) {
    popped += size;
    pop_from_top_chunk_(size);
  }
  return popped;
}

size_t StringBuffer::pop(std::string & s, size_t size) {
  s.clear();
  if(size == 0 || peel_chunks_and_check_if_empty_()) {
    return 0;
  }
  s.reserve(size);
  size_t popped = 0;
  while(!chunks_.empty() && size > top_chunk_occupied_) {
    size -= top_chunk_occupied_;
    popped += top_chunk_occupied_;
    read_top_chunk_and_pop_chunk_(s);
  }
  if(!chunks_.empty() && size > 0) {
    popped += size;
    read_from_top_chunk_(s, size);
  }
  return popped;
}

void StringBuffer::push(char c) {
  if(chunks_.empty() || top_chunk_is_full_()) {
    push_chunk_();
  }
  write_to_top_chunk_(c);
}

void StringBuffer::push(const std::string & s) {
  if(s.empty()) {
    return;
  }
  if(chunks_.empty() || top_chunk_is_full_()) {
    push_chunk_();
  }
  auto s_it = s.end();
  size_t to_push = s.size();
  while(to_push > top_chunk_free_) {
    fill_top_chunk_and_push_chunk_(s_it, to_push);
  }
  if(to_push > 0) {
    write_to_top_chunk_(s_it, to_push);
  }
}

void StringBuffer::fill_top_chunk_and_push_chunk_(std::string::const_iterator & it, size_t & to_push) {
  to_push -= top_chunk_free_;
  auto next_it = it - top_chunk_free_;
  chunks_.top().replace(chunks_.top().begin(), top_chunk_it_, next_it, it);
  push_chunk_();
  it = next_it;
}

bool StringBuffer::peel_chunks_and_check_if_empty_() {
  if(chunks_.empty()) {
    return true;
  }
  if(top_chunk_is_empty_()) {
    pop_chunk_();
  }
  return chunks_.empty();
}

void StringBuffer::pop_chunk_() {
  chunks_.pop();
  if(!chunks_.empty()) {
    top_chunk_it_ = chunks_.top().begin();
    top_chunk_free_ = 0;
    top_chunk_occupied_ = chunk_size_;
  }
}

void StringBuffer::pop_from_top_chunk_(size_t size) {
  top_chunk_it_ += size;
  top_chunk_free_ += size;
  top_chunk_occupied_ -= size;
}

void StringBuffer::push_chunk_() {
  chunks_.emplace(chunk_size_, '0');
  top_chunk_it_ = chunks_.top().end();
  top_chunk_free_ = chunk_size_;
  top_chunk_occupied_ = 0;
}

void StringBuffer::read_from_top_chunk_(char & c) {
  c = *(top_chunk_it_++);
  ++top_chunk_free_;
  --top_chunk_occupied_;
}

void StringBuffer::read_from_top_chunk_(std::string & s, size_t size) {
  top_chunk_free_ += size;
  top_chunk_occupied_ -= size;
  auto next_top_chunk_it = top_chunk_it_ + size;
  s.append(top_chunk_it_, next_top_chunk_it);
  top_chunk_it_ = next_top_chunk_it;
}

void StringBuffer::read_top_chunk_and_pop_chunk_(std::string & s) {
  s.append(top_chunk_it_, chunks_.top().end());
  pop_chunk_();
}

void StringBuffer::write_to_top_chunk_(char c) {
  *(--top_chunk_it_) = c;
  --top_chunk_free_;
  ++top_chunk_occupied_;
}

void StringBuffer::write_to_top_chunk_(std::string::const_iterator & it, size_t to_push) {
  top_chunk_free_ -= to_push;
  top_chunk_occupied_ += to_push;
  auto next_top_chunk_it = top_chunk_it_ - to_push;
  auto next_it = it - to_push;
  chunks_.top().replace(next_top_chunk_it, top_chunk_it_, next_it, it);
  top_chunk_it_ = next_top_chunk_it;
  it = next_it;
}

} // namespace stream
} // namespace pm
