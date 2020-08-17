/*
    This file is part of the pm library package.
    Copyright (C) 2017-2020 Vladislav Podymov

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
#include "pm/devel/stream/buffer.hpp"

#include <cstddef>

#include <algorithm>
#include <iterator>
#include <utility>

namespace pm::devel::stream {

Buffer::Iterator & Buffer::Iterator::operator ++() {
  advance_();
  return *this;
}

Buffer::Iterator Buffer::Iterator::operator ++(int) {
  auto res = *this;
  ++*this;
  return res;
}

Buffer::Iterator & Buffer::Iterator::operator +=(size_t size) {
  advance_(size);
  return *this;
}

Buffer::Iterator Buffer::Iterator::operator +(size_t size) const {
  auto res = *this;
  return res += size;
}

bool Buffer::Iterator::operator ==(const Buffer::Iterator & it) const {
  return chunk_it_ == it.chunk_it_ && offset_ == it.offset_;
}

bool Buffer::Iterator::operator !=(const Buffer::Iterator & it) const {
  return !(*this == it);
}

char Buffer::Iterator::operator *() const {
  return (*chunk_it_)[offset_];
}

char Buffer::Iterator::operator [](size_t size) {
  const size_t capacity = chunk_size_ - offset_;
  if(size < capacity) {
    return (*chunk_it_)[offset_ + size];
  }
  size_t rest = size - capacity;
  auto chit = std::next(chunk_it_);
  while(rest >= chunk_size_) {
    ++chit;
    rest -= chunk_size_;
  }
  return (*chit)[rest];
}

std::string Buffer::Iterator::peek(size_t size) const {
  const size_t capacity = chunk_size_ - offset_;
  // case 1: result fits in current chunk
  if(size <= capacity) {
    return chunk_it_->substr(offset_, size);
  }
  // case 2: result does not fit in current chunk
  std::string res;
  res.reserve(size);
  res += chunk_it_->substr(offset_, capacity);
  auto chit = std::next(chunk_it_);
  size -= capacity;
  while(size >= chunk_size_) {
    res += *chit;
    ++chit;
    size -= chunk_size_;
  }
  if(size > 0) {
    res += chit->substr(0, size);
  }
  return res;
}

std::string Buffer::Iterator::peek(const Buffer::Iterator & bound) const {
  // case 1: result fits in current chunk
  if(chunk_it_ == bound.chunk_it_) {
    return chunk_it_->substr(offset_, bound.offset_ - offset_);
  }
  // case 2: result does not fit in current chunk
  std::string res;
  res.reserve(bound - *this);
  res += chunk_it_->substr(offset_);
  auto chit = std::next(chunk_it_);
  while(chit != bound.chunk_it_) {
    res += *chit;
    ++chit;
  }
  if(bound.offset_ != 0) {
    res += bound.chunk_it_->substr(0, bound.offset_);
  }
  return res;
}

char Buffer::Iterator::get() {
  char res = **this;
  advance_();
  return res;
}

std::string Buffer::Iterator::get(size_t size) {
  const size_t capacity = chunk_size_ - offset_;
  // case 1: result fits in current chunk
  if(size <= capacity) {
    std::string res = chunk_it_->substr(offset_, size);
    offset_ += size;
    adjust_();
    return res;
  }
  // case 2: result does not fit in current chunk
  std::string res;
  res.reserve(size);
  res += chunk_it_->substr(offset_, capacity);
  ++chunk_it_;
  size -= capacity;
  while(size >= chunk_size_) {
    res += *chunk_it_;
    ++chunk_it_;
    size -= chunk_size_;
  }
  if(size > 0) {
    res += chunk_it_->substr(0, size);
  }
  offset_ = size;
  return res;
}

std::string Buffer::Iterator::get(const Buffer::Iterator & bound) {
  // case 1: result fits in current chunk
  if(chunk_it_ == bound.chunk_it_) {
    std::string res = chunk_it_->substr(offset_, bound.offset_ - offset_);
    offset_ = bound.offset_;
    return res;
  }
  // case 2: result does not fit in current chunk
  std::string res;
  res.reserve(bound - *this);
  res += chunk_it_->substr(offset_);
  while(++chunk_it_ != bound.chunk_it_) {
    res += *chunk_it_;
  }
  if(bound.offset_ != 0) {
    res += chunk_it_->substr(0, bound.offset_);
  }
  offset_ = bound.offset_;
  return res;
}

size_t Buffer::Iterator::operator -(const Buffer::Iterator & it) const {
  if(chunk_it_ == it.chunk_it_) {
    return offset_ - it.offset_;
  }
  size_t res = chunk_size_ - it.offset_;
  auto chit = std::next(it.chunk_it_);
  while(chit != chunk_it_) {
    ++chit;
    res += chunk_size_;
  }
  return res + offset_;
}

size_t Buffer::Iterator::trim(size_t size, const Buffer::Iterator & bound) const {
  if(chunk_it_ == bound.chunk_it_) {
    return std::min(size, bound.offset_ - offset_);
  }
  const size_t capacity = chunk_size_ - offset_;
  if(size <= capacity) {
    return size;
  }
  size_t rest = size - capacity;
  auto chit = std::next(chunk_it_);
  while(rest > chunk_size_ && chit != bound.chunk_it_) {
    rest -= chunk_size_;
    ++chit;
  }
  if(chit != bound.chunk_it_ || rest <= bound.offset_) {
    return size;
  }
  return size - (rest - bound.offset_);
}

Buffer::Iterator::Iterator(ChunkSeq::const_iterator it, size_t offset, size_t chunk_size)
  : chunk_it_(std::move(it)),
    offset_(offset),
    chunk_size_(chunk_size) {}

void Buffer::Iterator::advance_() {
  ++offset_;
  adjust_();
}

void Buffer::Iterator::advance_(size_t size) {
  while(size >= chunk_size_) {
    ++chunk_it_;
    size -= chunk_size_;
  }
  const size_t capacity = chunk_size_ - offset_;
  if(size < capacity) {
    offset_ += size;
  }
  else {
    ++chunk_it_;
    offset_ = size - capacity;
  }
}

void Buffer::Iterator::adjust_() {
  if(offset_ == chunk_size_) {
    ++chunk_it_;
    offset_ = 0;
  }
}

Buffer::Buffer(size_t chunk_size)
  : chunk_size_(chunk_size),
    chunks_(1) {
  chunks_.front().reserve(chunk_size);
}

void Buffer::add(char c) {
  chunks_.back().push_back(c);
  adjust_last_chunk_();
}

void Buffer::add(std::string s) {
  // case 1: s is empty
  if(s.empty()) {
    return;
  }
  // case 2: s is not empty and fits in last chunk
  if(s.size() <= chunk_size_ - chunks_.back().size()) {
    chunks_.back() += std::move(s);
    adjust_last_chunk_();
    return;
  }
  // case 3: s is not empty and does not fit in last chunk
  size_t substr_offset = chunk_size_ - chunks_.back().size();
  chunks_.back().append(s, 0, substr_offset);
  while(s.size() - substr_offset > chunk_size_) {
    chunks_.emplace_back(s.substr(substr_offset, chunk_size_));
    substr_offset += chunk_size_;
  }
  chunks_.emplace_back();
  chunks_.back().reserve(chunk_size_);
  chunks_.back().append(s, substr_offset);
  adjust_last_chunk_();
}

Buffer::Iterator Buffer::begin() {
  return {chunks_.begin(), 0, chunk_size_};
}

Buffer::Iterator Buffer::end() {
  return {std::prev(chunks_.end()), std::prev(chunks_.end())->size(), chunk_size_};
}

void Buffer::adjust_last_chunk_() {
  if(chunks_.back().size() == chunk_size_) {
    chunks_.emplace_back();
    chunks_.back().reserve(chunk_size_);
  }
}

Buffer::Iterator operator +(size_t i, const Buffer::Iterator & it) {
  return it + i;
}

} // namespace pm::devel::stream
