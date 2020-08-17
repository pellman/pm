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
#ifndef PM_DEVEL_STREAM_STREAMED_PTR_HPP
#define PM_DEVEL_STREAM_STREAMED_PTR_HPP

#include <cstddef>

#include <iosfwd>
#include <memory>
#include <string>

#include "pm/devel/stream/base.hpp"
#include "pm/devel/stream/buffer.hpp"
#include "pm/devel/stream/streamed_ref.hpp"

namespace pm::devel::stream {

class StreamedPtr
  : public StreamedRef {
public:
  // = methods =
  // defaults
  // Streamed() = delete;
  // Streamed & operator =(const Streamed &) = delete;
  // Streamed & operator =(Streamed &&) = delete;
  virtual ~StreamedPtr();
  // constructors
  StreamedPtr(size_t buffer_chunk_size_limit, std::istream * is_ptr);
  // other
  Base * clone() const override;
protected:
  // = fields =
  std::shared_ptr<std::istream> is_ptr_;
};

} // namespace pm::devel::stream

#endif
