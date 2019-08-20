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
#ifndef PM_STREAM_UTILS_POSITION_HPP
#define PM_STREAM_UTILS_POSITION_HPP

#include <cstddef>
#include <list>
#include <vector>

namespace pm {
namespace stream {
namespace utils {

class Buffer;
class BufferReader;
class IStreamReader;

} // namespace utils

class Position {
public:
  bool operator ==(const Position & pos) const;
  bool operator !=(const Position & pos) const;
  bool operator >(const Position & pos) const;
  bool operator <(const Position & pos) const;
  bool operator >=(const Position & pos) const;
  bool operator <=(const Position & pos) const;
  size_t operator -(const Position & pos) const;
private:
  Position(size_t chunk_size, size_t max_offset, size_t global_position, std::list<std::vector<char>>::const_iterator it, size_t offset);
  Position & operator +=(size_t size);
  Position operator +(size_t size) const;
  Position & operator ++();
  Position operator ++(int);
  size_t chunk_size_;
  size_t max_offset_;
  size_t global_position_;
  std::list<std::vector<char>>::const_iterator it_;
  size_t offset_;
  friend class utils::Buffer;
  friend class utils::BufferReader;
  friend class utils::IStreamReader;
};

} // namespace stream
} // namespace pm

#endif
