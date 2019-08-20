/*
    This file is part of the pm library package.
    Copyright (C) 2017-2019 Vladislav Podymov

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
#include "pm/stream/utils/buffer.hpp"

#include <algorithm>
//#include <cstddef>
//#include <list>
//#include <string>
//#include <vector>

#include "pm/stream/position.hpp"

namespace pm {
namespace stream {
namespace utils {

Buffer::Buffer(size_t chunk_size)
  : chunk_size_(chunk_size),
    max_offset_(chunk_size - 1),
    chars_in_buffer_(0) {
  chunks_.emplace_back();
  last_chunk_ = chunks_.begin();
  last_chunk_->reserve(chunk_size);
}

void Buffer::add(char c) {
  last_chunk_->push_back(c);
  if(last_chunk_->size() == chunk_size_) {
    add_empty_chunk_();
  }
  ++chars_in_buffer_;
}

void Buffer::add(std::string::const_iterator it, size_t size) {
  // TODO may be increase safety: "static_cast" -> "if ... >= PTRDIFF_MAX, then ..."
  chars_in_buffer_ += size;
  if(size < chunk_size_ - last_chunk_->size()) {
    last_chunk_->insert(last_chunk_->end(), it, it + static_cast<ptrdiff_t>(size));
  }
  else {
    const size_t capacity = chunk_size_ - last_chunk_->size();
    std::string::const_iterator iend = it + static_cast<ptrdiff_t>(capacity);
    last_chunk_->insert(last_chunk_->end(), it, iend);
    size -= capacity;
    while(size >= chunk_size_) {
      it = iend;
      iend += static_cast<ptrdiff_t>(chunk_size_);
      add_full_chunk_(it, iend);
      size -= chunk_size_;
    }
    add_empty_chunk_();
    if(size != 0) {
      last_chunk_->insert(last_chunk_->end(), iend, iend + static_cast<ptrdiff_t>(size));
    }
  }
}

void Buffer::peek(char & c, const Position & pos) const {
  c = (*(pos.it_))[pos.offset_];
}

void Buffer::peek(std::string::iterator it, size_t size, const Position & pos) {
  // TODO may be increase safety: "static_cast" -> "if ... >= PTRDIFF_MAX, then ..."
  std::list<std::vector<char>>::const_iterator chunk = pos.it_;
  std::vector<char>::const_iterator ich = chunk->begin() + static_cast<ptrdiff_t>(pos.offset_);
  const size_t chunk_remainder = chunk_size_ - pos.offset_;
  if(size <= chunk_remainder) {
    std::copy(ich, ich + static_cast<ptrdiff_t>(size), it);
    return;
  }
  std::copy(ich, chunk->end(), it);
  ++chunk;
  it += static_cast<ptrdiff_t>(chunk_remainder);
  size -= chunk_remainder;
  while(size >= chunk_size_) {
    std::copy(chunk->begin(), chunk->end(), it);
    ++chunk;
    it += static_cast<ptrdiff_t>(chunk_size_);
    size -= chunk_size_;
  }
  if(size != 0) {
    ich = chunk->begin();
    std::copy(ich, ich + static_cast<ptrdiff_t>(size), it);
  }
}

size_t Buffer::available_forward(const Position & pos) const {
  return chars_in_buffer_ - pos.global_position_;
}

size_t Buffer::available_backward(const Position & pos) const {
  return pos.global_position_;
}

bool Buffer::at_end(const Position & pos) const {
  return chars_in_buffer_ == pos.global_position_;
}

bool Buffer::at_start(const Position & pos) const {
  return pos.global_position_ == 0;
}

Position Buffer::begin() const {
  return {chunk_size_, max_offset_, 0, chunks_.begin(), 0};
}

Position Buffer::end() const {
  return {chunk_size_, max_offset_, chars_in_buffer_, last_chunk_, last_chunk_->size()};
}

void Buffer::add_empty_chunk_() {
  chunks_.emplace_back();
  ++last_chunk_;
  last_chunk_->reserve(chunk_size_);
}

void Buffer::add_full_chunk_(const std::string::const_iterator & it, const std::string::const_iterator & iend) {
  chunks_.emplace_back(it, iend);
  ++last_chunk_;
}

} // namespace utils
} // namespace stream
} // namespace pm
