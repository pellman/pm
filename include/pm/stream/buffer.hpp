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
#ifndef __PM_STREAM_BUFFER_HPP
#define __PM_STREAM_BUFFER_HPP

#include <cstddef>
#include <stack>
#include <string>

namespace pm {
namespace stream {

class StringBuffer {
public:
  // DEFAULTS
  // StringBuffer() -> StringBuffer(100)
  StringBuffer(const StringBuffer &) = delete;
  StringBuffer(StringBuffer &&) = delete;
  StringBuffer & operator =(const StringBuffer &) = delete;
  StringBuffer & operator =(StringBuffer &&) = delete;
  // CONSTRUCTORS
  inline StringBuffer(size_t size = 100);
  // ALTERING METHODS
  void clear();
  bool pop();
  bool pop(char & c);
  size_t pop(size_t size);
  size_t pop(std::string & s, size_t size);
  void push(char c);
  void push(const std::string & s);
  // ACCESS METHODS
  inline bool empty() const;

private:
  // ALTERING METHODS
  void fill_top_chunk_and_push_chunk_(std::string::const_iterator & it, size_t & to_push);
  bool peel_chunks_and_check_if_empty_();
  void pop_chunk_();
  void pop_from_top_chunk_(size_t size);
  void push_chunk_();
  void read_from_top_chunk_(char & c);
  void read_from_top_chunk_(std::string & s, size_t size);
  void read_top_chunk_and_pop_chunk_(std::string & s);
  void write_to_top_chunk_(char c);
  void write_to_top_chunk_(std::string::const_iterator & it, size_t to_push);
  // PRESERVING METHODS
  inline bool top_chunk_is_empty_() const;
  inline bool top_chunk_is_full_() const;
  // FIELDS
  const size_t chunk_size_;
  std::stack<std::string> chunks_;
  std::string::iterator top_chunk_it_;
  size_t top_chunk_free_, top_chunk_occupied_;
};


// implementation
StringBuffer::StringBuffer(size_t size)
  : chunk_size_(size == 0 ? 100 : size) {}

bool StringBuffer::empty() const {
  return
    chunks_.empty() ||
    (chunks_.size() == 1 && top_chunk_is_empty_());
}

bool StringBuffer::top_chunk_is_full_() const {return top_chunk_free_ == 0;}

bool StringBuffer::top_chunk_is_empty_() const {return top_chunk_occupied_ == 0;}

} // namespace stream
} // namespace pm

#endif
