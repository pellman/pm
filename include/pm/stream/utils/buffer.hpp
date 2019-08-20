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
#ifndef PM_STREAM_UTILS_BUFFER_HPP
#define PM_STREAM_UTILS_BUFFER_HPP

#include <cstddef>
#include <list>
#include <string>
#include <vector>

namespace pm {
namespace stream {

class Position;

namespace utils {

class Buffer {
public:
  // DEFAULTS
  // Buffer() deleted
  Buffer(const Buffer &) = delete;
  Buffer(Buffer &&) = delete;
  Buffer & operator =(const Buffer &) = delete;
  Buffer & operator =(Buffer &&) = delete;
  // CONSTRUCTORS
  Buffer(size_t chunk_size);
  // ALTERING METHODS
  void add(char c);
  void add(std::string::const_iterator it, size_t size);
  // PRESERVING METHODS
  void peek(char & c, const Position & pos) const;
  void peek(std::string::iterator it, size_t size, const Position & pos);
  // ACCESS METHODS
  bool at_end(const Position & pos) const;
  bool at_start(const Position & pos) const;
  size_t available_backward(const Position & pos) const;
  size_t available_forward(const Position & pos) const;
  Position begin() const;
  Position end() const;

private:
  // ALTERING METHODS
  void add_empty_chunk_();
  void add_full_chunk_(const std::string::const_iterator & it, const std::string::const_iterator & iend);
  // FIELDS
  const size_t chunk_size_;
  const size_t max_offset_;
  size_t chars_in_buffer_;
  std::list<std::vector<char>> chunks_;
  std::list<std::vector<char>>::iterator last_chunk_;
};

} // namespace utils
} // namespace stream
} // namespace pm

#endif
