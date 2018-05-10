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
#ifndef __PM_STREAM_STREAM_HPP
#define __PM_STREAM_STREAM_HPP

#include <cstddef>
#include <istream>
#include <string>
#include "pm/stream/buffer.hpp"

namespace pm {
namespace stream {

class Stream {
public:
  // DEFAULTS
  // Stream() deleted
  // Stream(const Stream &) deleted
  // Stream(Stream &&) deleted
  // Stream & operator =(const Stream &) deleted
  // Stream & operator =(Stream &&) deleted
  // CONSTRUCTORS
  inline Stream(std::istream & s);
  inline Stream(std::istream & s, size_t buffer_size);
  // ALTERING METHODS
  inline bool get(char & c);
  size_t get(std::string & s, size_t size);
  bool get_strict(std::string & s, size_t size);
  inline bool skip();
  size_t skip(size_t size);
  inline bool skip_strict(size_t size);
  inline void unget(char c);
  inline void unget(const std::string & s);
  // ACCESS METHODS
  inline bool empty();

private:
  // FIELDS
  std::istream & stream_;
  StringBuffer buffer_;
};


// implementation
Stream::Stream(std::istream & s)
  : stream_(s) {}

Stream::Stream(std::istream & s, size_t buffer_size)
  : stream_(s),
    buffer_(buffer_size) {}

bool Stream::get(char & c) {return buffer_.pop(c) ? true : stream_.get(c).good();}

bool Stream::skip() {return buffer_.pop() ? true : stream_.ignore().good();}

bool Stream::skip_strict(size_t size) {
  std::string s_get;
  return get_strict(s_get, size);
}

void Stream::unget(char c) {buffer_.push(c);}

void Stream::unget(const std::string & s) {buffer_.push(s);}

bool Stream::empty() {
  if(!buffer_.empty()) {
    return false;
  }
  if(!stream_.good()) {
    return true;
  }
  char c;
  if(!stream_.get(c).good()) {
    return true;
  }
  unget(c);
  return false;
}

} // namespace stream
} // namespace pm

#endif
