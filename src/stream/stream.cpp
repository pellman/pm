/*
    This file is part of the pm library package.
    Copyright (C) 2017 Vladislav Podymov
    
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
#include "stream/stream.hpp"

namespace pm {
namespace stream {

size_t Stream::get(std::string & s, size_t size) {
  size_t popped = buffer_.pop(s, size);
  if(popped == size || !(stream_.good())) {
    return popped;
  }
  char * s_to_append = new char[size - popped + 1];
  stream_.read(s_to_append, size - popped);
  size_t popped_append = stream_.gcount();
  if(popped_append != 0) {
    s_to_append[popped_append] = 0;
    s += s_to_append;
  }
  delete s_to_append;
  return popped + popped_append;
}

bool Stream::get_strict(std::string & s, size_t size) {
  std::string s_get;
  if(get(s_get, size) == size) {
    s = std::move(s_get);
    return true;
  }
  else {
    unget(s_get);
    return false;
  }
}

size_t Stream::skip(size_t size) {
  size_t popped = buffer_.pop(size);
  if(popped == size) {
    return size;
  }
  stream_.ignore(size - popped);
  return popped + stream_.gcount();
}

} // namespace stream
} // namespace pm
