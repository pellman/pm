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
#ifndef PM_STREAM_UTILS_READER_HPP
#define PM_STREAM_UTILS_READER_HPP

#include <cstddef>
#include <string>

namespace pm {
namespace stream {

class Position;

namespace utils {

class Buffer;

class Reader {
public:
  virtual ~Reader();
  virtual bool advance(Position & pos, Buffer & buffer) = 0;
  virtual bool advance(size_t size, Position & pos, Buffer & buffer) = 0;
  virtual size_t advance_at_most(size_t size, Position & pos, Buffer & buffer) = 0;
  virtual bool at_end(const Position & pos, Buffer & buffer) = 0;
  virtual bool get(char & c, Position & pos, Buffer & buffer) = 0;
  virtual bool get(std::string & s, size_t size, Position & pos, Buffer & buffer) = 0;
  virtual void get(std::string & s, const Position & bound, Position & pos, Buffer & buffer) = 0;
  virtual void get_at_most(std::string & s, size_t size, Position & pos, Buffer & buffer) = 0;
  virtual bool peek(char & c, const Position & pos, Buffer & buffer) = 0;
  virtual bool peek(std::string & s, size_t size, const Position & pos, Buffer & buffer) = 0;
  virtual void peek(std::string & s, const Position & bound, const Position & pos, Buffer & buffer) = 0;
  virtual void peek_at_most(std::string & s, size_t size, const Position & pos, Buffer & buffer) = 0;
};

} // namespace utils
} // namespace stream
} // namespace pm

#endif
