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
#ifndef PM_STREAM_STREAM_HPP
#define PM_STREAM_STREAM_HPP

//#include <cstddef>
#include <iosfwd>
#include <memory>
#include <string>

#include "pm/stream/position.hpp"

namespace pm {
namespace stream {

namespace utils {

class Reader;
class Buffer;

} // namespace utils


class Stream {
public:
  // DEFAULTS
  // Stream() deleted
  // CONSTRUCTORS
  Stream(std::istream & is);
  Stream(std::istream & is, size_t buffer_chunk_size);
  // ALTERING METHODS
  bool advance();
  bool advance(size_t size);
  size_t advance_at_most(size_t size);
  bool get(char & c);
  bool get(std::string & s, size_t size);
  void get(std::string & s, const Position & bound);
  void get_at_most(std::string & s, size_t size);
  void reposition(Position pos);
  // PRESERVING METHODS
  // = alter contents =
  bool empty() const;
  bool peek(char & c) const;
  bool peek(std::string & s, size_t size) const;
  void peek(std::string & s, const Position & bound) const;
  void peek_at_most(std::string & s, size_t size) const;
  // = preserve contents =
  Stream prefix(Position bound) const;
  // ACCESS METHODS
  Position pos() const;

private:
  // CONSTRUCTORS
  Stream(std::shared_ptr<utils::Buffer> buffer,
         Position pos,
         std::shared_ptr<utils::Reader> reader
        );
  // FIELDS
  std::shared_ptr<utils::Buffer> buffer_;
  Position pos_;
  std::shared_ptr<utils::Reader> reader_;
};

} // namespace stream
} // namespace pm

#endif
