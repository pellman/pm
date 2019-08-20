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
#include "pm/stream/utils/istream_reader.hpp"

//#include <cstddef>
//#include <iosfwd>
#include <istream>
//#include <string>
#include <utility>

#include "pm/stream/position.hpp"
//#include "pm/stream/utils/reader.hpp"
#include "pm/stream/utils/buffer.hpp"

namespace pm {
namespace stream {
namespace utils {

IStreamReader::IStreamReader(std::istream & is)
  : is_(is) {}

bool IStreamReader::advance(Position & pos, Buffer & buffer) {
  if(buffer.at_end(pos)) {
    char c;
    if(!is_.get(c).good()) {
      return false;
    }
    buffer.add(c);
  }
  ++pos;
  return true;
}

bool IStreamReader::advance(size_t size, Position & pos, Buffer & buffer) {
  // TODO may be increase safety: "static_cast" -> "if ... >= PTRDIFF_MAX, then ..."
  const size_t buffered_size = buffer.available_forward(pos);
  if(buffered_size < size) {
    std::string tmps;
    const size_t remained_size = size - buffered_size;
    tmps.resize(remained_size);
    is_.read(&tmps[0], static_cast<std::streamsize>(remained_size));
    const size_t streamed_size = static_cast<size_t>(is_.gcount());
    buffer.add(tmps.begin(), streamed_size);
    if(streamed_size < remained_size) {
      return false;
    }
  }
  pos += size;
  return true;
}

size_t IStreamReader::advance_at_most(size_t size, Position & pos, Buffer & buffer) {
  // TODO may be increase safety: "static_cast" -> "if ... >= PTRDIFF_MAX, then ..."
  const size_t buffered_size = buffer.available_forward(pos);
  if(buffered_size < size) {
    std::string tmps;
    const size_t remained_size = size - buffered_size;
    tmps.resize(remained_size);
    is_.read(&tmps[0], static_cast<std::streamsize>(remained_size));
    const size_t streamed_size = static_cast<size_t>(is_.gcount());
    buffer.add(tmps.begin(), streamed_size);
    if(streamed_size < remained_size) {
      const size_t final_size = buffered_size + streamed_size;
      pos += final_size;
      return final_size;
    }
  }
  pos += size;
  return size;
}

bool IStreamReader::at_end(const Position & pos, Buffer & buffer) {
  if(buffer.at_end(pos)) {
    char c;
    if(!is_.get(c).good()) {
      return true;
    }
    buffer.add(c);
  }
  return false;
}

bool IStreamReader::get(char & c, Position & pos, Buffer & buffer) {
  if(!peek(c, pos, buffer)) {
    return false;
  }
  ++pos;
  return true;
}

bool IStreamReader::get(std::string & s, size_t size, Position & pos, Buffer & buffer) {
  if(!peek(s, size, pos, buffer)) {
    return false;
  }
  pos += size;
  return true;
}

void IStreamReader::get(std::string & s, const Position & bound, Position & pos, Buffer & buffer) {
  peek(s, bound, pos, buffer);
  pos = bound;
}

void IStreamReader::get_at_most(std::string & s, size_t size, Position & pos, Buffer & buffer) {
  peek_at_most(s, size, pos, buffer);
  pos += s.size();
}

bool IStreamReader::peek(char & c, const Position & pos, Buffer & buffer) {
  if(buffer.at_end(pos)) {
    if(!is_.get(c).good()) {
      return false;
    }
    buffer.add(c);
  }
  else {
    buffer.peek(c, pos);
  }
  return true;
}

bool IStreamReader::peek(std::string & s, size_t size, const Position & pos, Buffer & buffer) {
  // TODO may be increase safety: "static_cast" -> "if ... >= PTRDIFF_MAX, then ..."
  const size_t buffered_size = buffer.available_forward(pos);
  if(buffered_size >= size) {
    s.resize(size);
    buffer.peek(s.begin(), size, pos);
  }
  else {
    std::string tmps;
    tmps.resize(size);
    const size_t remained_size = size - buffered_size;
    is_.read(&tmps[buffered_size], static_cast<std::streamsize>(remained_size));
    const size_t streamed_size = static_cast<size_t>(is_.gcount());
    buffer.add(tmps.begin() + static_cast<ptrdiff_t>(buffered_size), streamed_size);
    if(streamed_size < remained_size) {
      return false;
    }
    buffer.peek(tmps.begin(), buffered_size, pos);
    s = std::move(tmps);
  }
  return true;
}

void IStreamReader::peek(std::string & s, const Position & bound, const Position & pos, Buffer & buffer) {
  const size_t size = bound - pos;
  s.resize(size);
  buffer.peek(s.begin(), size, pos);
}

void IStreamReader::peek_at_most(std::string & s, size_t size, const Position & pos, Buffer & buffer) {
  // TODO may be increase safety: "static_cast" -> "if ... >= PTRDIFF_MAX, then ..."
  const size_t buffered_size = buffer.available_forward(pos);
  if(buffered_size >= size) {
    s.resize(size);
    buffer.peek(s.begin(), size, pos);
  }
  else {
    std::string tmps;
    tmps.resize(size);
    const size_t remained_size = size - buffered_size;
    is_.read(&tmps[buffered_size], static_cast<std::streamsize>(remained_size));
    const size_t streamed_size = static_cast<size_t>(is_.gcount());
    buffer.add(tmps.begin() + static_cast<ptrdiff_t>(buffered_size), streamed_size);
    if(streamed_size < remained_size) {
      tmps.resize(buffered_size + streamed_size);
    }
    buffer.peek(tmps.begin(), buffered_size, pos);
    s = std::move(tmps);
  }
}

} // namespace utils
} // namespace stream
} // namespace pm
