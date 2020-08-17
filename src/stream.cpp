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
#include "pm/stream.hpp"

#include <fstream>
#include <sstream>
#include <utility>

#include "pm/devel/stream/base.hpp"
#include "pm/devel/stream/bounded.hpp"
#include "pm/devel/stream/streamed_ptr.hpp"
#include "pm/devel/stream/streamed_ref.hpp"

namespace pm {

Stream::Stream(const Stream & is)
  : ptr_(is.ptr_->clone()) {}

Stream & Stream::operator =(const Stream & is) {
  ptr_.reset(is.ptr_->clone());
  return *this;
}

bool Stream::try_advance() {
  return ptr_->try_advance();
}

bool Stream::try_advance(size_t size) {
  return ptr_->try_advance(size);
}

size_t Stream::advance(size_t size) {
  return ptr_->advance(size);
}

std::optional<char> Stream::try_get() {
  return ptr_->try_get();
}

std::optional<std::string> Stream::try_get(size_t size) {
  return ptr_->try_get(size);
}

std::string Stream::get(size_t size) {
  return ptr_->get(size);
}

std::string Stream::get(const Stream::Iterator & bound) {
  return ptr_->get(bound);
}

std::optional<char> Stream::try_peek() const {
  return ptr_->try_peek();
}

std::optional<std::string> Stream::try_peek(size_t size) const {
  return ptr_->try_peek(size);
}

std::string Stream::peek(size_t size) const {
  return ptr_->peek(size);
}

std::string Stream::peek(const Stream::Iterator & bound) const {
  return ptr_->peek(bound);
}

bool Stream::empty() const {
  return ptr_->empty();
}

Stream Stream::get_prefix(Stream::Iterator bound) const {
  return Stream(new devel::stream::Bounded(*ptr_, bound));
}

Stream Stream::get_prefix(size_t size) const {
  Stream tmp = *this;
  tmp.advance(size);
  return get_prefix(tmp.get_position());
}

Stream::Iterator Stream::get_position() const {
  return ptr_->get_position();
}

void Stream::set_position(Stream::Iterator position) {
  ptr_->set_position(position);
}

Stream Stream::wrap(std::istream * is_ptr) {
  return Stream(new devel::stream::StreamedPtr(default_chunk_size, is_ptr));
}

Stream Stream::wrap(std::istream & is) {
  return Stream(new devel::stream::StreamedRef(default_chunk_size, is));
}

Stream Stream::wrap(const std::string & s) {
  return wrap(new std::istringstream(s));
}

Stream Stream::wrap_file(const std::string & filename) {
  return wrap(new std::ifstream(filename));
}

Stream::Stream(devel::stream::Base * ptr)
  : ptr_(ptr) {}

} // namespace pm
