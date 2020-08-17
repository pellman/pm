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
#ifndef PM_DEVEL_STREAM_STREAMED_REF_HPP
#define PM_DEVEL_STREAM_STREAMED_REF_HPP

#include <cstddef>

#include <iosfwd>
#include <string>

#include "pm/devel/stream/base.hpp"
#include "pm/devel/stream/buffer.hpp"

namespace pm::devel::stream {

class StreamedRef
  : public Base {
public:
  // = methods =
  // defaults
  // Streamed() = delete;
  // Streamed & operator =(const Streamed &) = delete;
  // Streamed & operator =(Streamed &&) = delete;
  virtual ~StreamedRef();
  // constructors
  StreamedRef(size_t buffer_chunk_size_limit, std::istream & is);
  // advance
  bool try_advance() override;
  bool try_advance(size_t size) override;
  size_t advance(size_t size) override;
  // get
  std::optional<char> try_get() override;
  std::optional<std::string> try_get(size_t size) override;
  std::string get(size_t size) override;
  std::string get(const Buffer::Iterator & bound) override;
  // peek
  std::optional<char> try_peek() override;
  std::optional<std::string> try_peek(size_t size) override;
  std::string peek(size_t size) override;
  std::string peek(const Buffer::Iterator & bound) override;
  // other
  Base * clone() const override;
  bool empty() const override;
protected:
  // = fields =
  std::istream & is_;
private:
  // = methods =
  size_t trim_(size_t size) const;
  std::string read_string_(size_t size) const;
};

} // namespace pm::devel::stream

#endif
