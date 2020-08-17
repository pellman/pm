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
#include "pm/devel/stream/streamed_ptr.hpp"

#include <cstddef>

#include <iostream>
#include <string>
#include <utility>

#include "pm/devel/stream/buffer.hpp"

namespace pm::devel::stream {

StreamedPtr::~StreamedPtr() {}

StreamedPtr::StreamedPtr(size_t buffer_chunk_size_limit, std::istream * is_ptr)
  : StreamedRef(buffer_chunk_size_limit, *is_ptr),
    is_ptr_(is_ptr) {}

Base * StreamedPtr::clone() const {
  return new StreamedPtr(*this);
}

} // namespace pm::devel::stream
