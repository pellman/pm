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
#include "pm/devel/stream/bounded.hpp"

#include <utility>

namespace pm::devel::stream {

Bounded::~Bounded() {}

Bounded::Bounded(const Base & base, Buffer::Iterator end)
  : Base(base),
    end_(std::move(end)) {}

bool Bounded::try_advance() {
  if(position_ == end_) {
    return false;
  }
  ++position_;
  return true;
}

bool Bounded::try_advance(size_t size) {
  if(position_.trim(size, end_) < size) {
    return false;
  }
  position_ += size;
  return true;
}

size_t Bounded::advance(size_t size) {
  size = position_.trim(size, end_);
  position_ += size;
  return size;
}

std::optional<char> Bounded::try_get() {
  if(position_ == end_) {
    return {};
  }
  return position_.get();
}

std::optional<std::string> Bounded::try_get(size_t size) {
  if(position_.trim(size, end_) < size) {
    return {};
  }
  return position_.get(size);
}

std::string Bounded::get(size_t size) {
  return position_.get(position_.trim(size, end_));
}

std::string Bounded::get(const Buffer::Iterator & bound) {
  return position_.get(bound);
}

std::optional<char> Bounded::try_peek() {
  if(position_ == end_) {
    return {};
  }
  return *position_;
}

std::optional<std::string> Bounded::try_peek(size_t size) {
  if(position_.trim(size, end_) < size) {
    return {};
  }
  return position_.peek(size);
}

std::string Bounded::peek(size_t size) {
  return position_.peek(position_.trim(size, end_));
}

std::string Bounded::peek(const Buffer::Iterator & bound) {
  return position_.peek(bound);
}

Base * Bounded::clone() const {
  return new Bounded(*this);
}

bool Bounded::empty() const {
  return position_ == end_;
}

} // namespace pm::devel::stream
