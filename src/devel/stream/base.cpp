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
#include "pm/devel/stream/base.hpp"

#include "pm/devel/stream/buffer.hpp"

namespace pm::devel::stream {

Base::~Base() {}

Base::Base(size_t buffer_chunk_size)
  : buffer_(new Buffer(buffer_chunk_size)),
    position_(buffer_->begin()) {
}

Buffer::Iterator Base::get_position() const {
  return position_;
}

void Base::set_position(Buffer::Iterator position) {
  position_ = position;
}

} // namespace pm::devel::stream
