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
#include "pm/devel/stream/streamed_ref.hpp"

#include <cstddef>

#include <iostream>
#include <string>
#include <utility>

#include "pm/devel/stream/buffer.hpp"

namespace pm::devel::stream {

StreamedRef::~StreamedRef() {}

StreamedRef::StreamedRef(size_t buffer_chunk_size_limit, std::istream & is)
  : Base(buffer_chunk_size_limit),
    is_(is) {}

bool StreamedRef::try_advance() {
  if(empty()) {
    return false;
  }
  ++position_;
  return true;
}

bool StreamedRef::try_advance(size_t size) {
  if(trim_(size) < size) {
    return false;
  }
  position_ += size;
  return true;
}

size_t StreamedRef::advance(size_t size) {
  size = trim_(size);
  position_ += size;
  return size;
}

std::optional<char> StreamedRef::try_get() {
  if(empty()) {
    return {};
  }
  return position_.get();
}

std::optional<std::string> StreamedRef::try_get(size_t size) {
  if(trim_(size) < size) {
    return {};
  }
  return position_.get(size);
}

std::string StreamedRef::get(size_t size) {
  return position_.get(trim_(size));
}

std::string StreamedRef::get(const Buffer::Iterator & bound) {
  return position_.get(bound);
}

std::optional<char> StreamedRef::try_peek() {
  if(empty()) {
    return {};
  }
  return *position_;
}

std::optional<std::string> StreamedRef::try_peek(size_t size) {
  if(trim_(size) < size) {
    return {};
  }
  return position_.peek(size);
}

std::string StreamedRef::peek(size_t size) {
  return position_.peek(trim_(size));
}

std::string StreamedRef::peek(const Buffer::Iterator & bound) {
  return position_.peek(bound);
}

Base * StreamedRef::clone() const {
  return new StreamedRef(*this);
}

bool StreamedRef::empty() const {
  if(position_ != buffer_->end()) {
    return false;
  }
  char c;
  if(!is_.get(c).good()) {
    return true;
  }
  buffer_->add(c);
  return false;
}

size_t StreamedRef::trim_(size_t size) const {
  const size_t buffered_size = position_.trim(size, buffer_->end());
  if(buffered_size == size) {
    return size;
  }
  std::string s = read_string_(size - buffered_size);
  if(s.empty()) {
    return buffered_size;
  }
  const size_t streamed_size = s.size();
  buffer_->add(std::move(s));
  return buffered_size + streamed_size;
}

std::string StreamedRef::read_string_(size_t size) const {
  // TODO may be increase safety: "static_cast" -> "if ... >= PTRDIFF_MAX, then ..., or something like that"
  std::string res;
  res.resize(size);
  is_.read(&res[0], static_cast<std::streamsize>(size));
  res.resize(static_cast<size_t>(is_.gcount()));
  return res;
}

} // namespace pm::devel::stream
