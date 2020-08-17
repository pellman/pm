/*
    This file is part of the pm library package.
    Copyright (C) 2017-2020 Vladislav Podymov

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
#ifndef PM_STREAM_HPP
#define PM_STREAM_HPP

#include <cstddef>

#include <iosfwd>
#include <memory>
#include <optional>
#include <string>

#include "pm/devel/stream/base.hpp"
#include "pm/devel/stream/buffer.hpp"

namespace pm {

class Stream {
public:
  // TYPES
  using Iterator = devel::stream::Buffer::Iterator;
  // DEFAULTS
  Stream(const Stream & is);
  Stream(Stream && is) = default;
  Stream & operator =(const Stream & is);
  Stream & operator =(Stream && is) = default;
  // ADVANCE
  bool try_advance();
  bool try_advance(size_t size);
  size_t advance(size_t size);
  // GET
  std::optional<char> try_get();
  std::optional<std::string> try_get(size_t size);
  std::string get(size_t size);
  std::string get(const Iterator & bound);
  // PEEK
  std::optional<char> try_peek() const;
  std::optional<std::string> try_peek(size_t size) const;
  std::string peek(size_t size) const;
  std::string peek(const Iterator & bound) const;
  // OTHER
  bool empty() const;
  Stream get_prefix(Iterator bound) const;
  Stream get_prefix(size_t size) const;
  Iterator get_position() const;
  void set_position(Iterator position);
  // STATICS
  static Stream wrap(std::istream * is_ptr);
  static Stream wrap(std::istream & is);
  static Stream wrap(const std::string & s);
  static Stream wrap_file(const std::string & filename);

private:
  // CONSTRUCTORS
  Stream(devel::stream::Base * ptr);
  // FIELDS
  std::unique_ptr<devel::stream::Base> ptr_;
  static const size_t default_chunk_size = 100;
};

} // namespace pm

#endif
