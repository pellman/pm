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
#include "pm/stream/utils/buffer_reader.hpp"

#include <algorithm>
//#include <cstddef>
//#include <string>
#include <utility>

//#include "pm/stream/position.hpp"
#include "pm/stream/utils/buffer.hpp"
//#include "pm/stream/utils/reader.hpp"

namespace pm {
namespace stream {
namespace utils {

BufferReader::BufferReader(Position bound)
  : bound_(std::move(bound)) {}

bool BufferReader::get(char & c, Position & pos, Buffer & buffer) {
  if(!peek(c, pos, buffer)) {
    return false;
  }
  ++pos;
  return true;
}

bool BufferReader::get(std::string & s, size_t size, Position & pos, Buffer & buffer) {
  if(!peek(s, size, pos, buffer)) {
    return false;
  }
  pos += size;
  return true;
}

void BufferReader::get(std::string & s, const Position & bound, Position & pos, Buffer & buffer) {
  peek(s, bound, pos, buffer);
  pos = bound;
}

void BufferReader::get_at_most(std::string & s, size_t size, Position & pos, Buffer & buffer) {
  peek_at_most(s, size, pos, buffer);
  pos += s.size();
}

bool BufferReader::peek(char & c, const Position & pos, Buffer & buffer) {
  if(pos == bound_) {
    return false;
  }
  buffer.peek(c, pos);
  return true;
}

bool BufferReader::peek(std::string & s, size_t size, const Position & pos, Buffer & buffer) {
  if(bound_ - pos < size) {
    return false;
  }
  s.resize(size);
  buffer.peek(s.begin(), size, pos);
  return true;
}

void BufferReader::peek(std::string & s, const Position & bound, const Position & pos, Buffer & buffer) {
  const size_t size = bound - pos;
  s.resize(size);
  buffer.peek(s.begin(), size, pos);
}

void BufferReader::peek_at_most(std::string & s, size_t size, const Position & pos, Buffer & buffer) {
  const size_t actual_size = std::min(size, bound_ - pos);
  s.resize(actual_size);
  buffer.peek(s.begin(), actual_size, pos);
}

bool BufferReader::advance(Position & pos, Buffer &) {
  if(pos == bound_) {
    return false;
  }
  ++pos;
  return true;
}

bool BufferReader::advance(size_t size, Position & pos, Buffer &) {
  if(bound_ - pos < size) {
    return false;
  }
  pos += size;
  return true;
}

size_t BufferReader::advance_at_most(size_t size, Position & pos, Buffer &) {
  const size_t available_size = bound_ - pos;
  if(available_size <= size) {
    pos = bound_;
    return available_size;
  }
  else {
    pos += size;
    return size;
  }
}

bool BufferReader::at_end(const Position & pos, Buffer &) {
  return pos == bound_;
}

} // namespace utils
} // namespace stream
} // namespace pm
