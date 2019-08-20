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
#include "pm/stream/position.hpp"

//#include <cstddef>
//#include <list>
//#include <vector>

namespace pm {
namespace stream {

bool Position::operator ==(const Position & pos) const {
  return global_position_ == pos.global_position_;
}

bool Position::operator !=(const Position & pos) const {
  return global_position_ != pos.global_position_;
}

bool Position::operator >(const Position & pos) const {
  return global_position_ > pos.global_position_;
}

bool Position::operator <(const Position & pos) const {
  return global_position_ < pos.global_position_;
}

bool Position::operator >=(const Position & pos) const {
  return global_position_ >= pos.global_position_;
}

bool Position::operator <=(const Position & pos) const {
  return global_position_ <= pos.global_position_;
}

size_t Position::operator -(const Position & pos) const {
  return global_position_ - pos.global_position_;
}

Position::Position(size_t chunk_size, size_t max_offset, size_t global_position, std::list<std::vector<char>>::const_iterator it, size_t offset)
  : chunk_size_(chunk_size),
    max_offset_(max_offset),
    global_position_(global_position),
    it_(it),
    offset_(offset) {}

Position & Position::operator +=(size_t size) {
  global_position_ += size;
  if(size != 0) {
    if(offset_ + size <= max_offset_) {
      offset_ += size;
    }
    else {
      size -= chunk_size_ - offset_;
      ++it_;
      while(size > max_offset_) {
        size -= chunk_size_;
        ++it_;
      }
      offset_ = size;
    }
  }
  return *this;
}

Position Position::operator +(size_t size) const {
  Position res = *this;
  res += size;
  return res;
}

Position & Position::operator ++() {
  ++global_position_;
  if(offset_ == max_offset_) {
    ++it_;
    offset_ = 0;
  }
  else {
    ++offset_;
  }
  return *this;
}

Position Position::operator ++(int) {
  Position res = *this;
  return ++res;
}

} // namespace stream
} // namespace pm
