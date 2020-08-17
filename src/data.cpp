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
#include "pm/data.hpp"

#include <utility>

namespace pm {

Data::Data(const Data & d)
  : ptr_(d.ptr_ ? d.ptr_->clone() : nullptr) {}

Data & Data::operator =(const Data & d) {
  ptr_.reset(d.ptr_ ? d.ptr_->clone() : nullptr);
  return *this;
}

void Data::swap(Data & d) {
  ptr_.swap(d.ptr_);
}

void Data::reset() {
  ptr_.reset();
}

bool Data::has_value() const {
  return static_cast<bool>(ptr_);
}

Data::Data(devel::data::ClonerBase * base)
  : ptr_(base) {}

void swap(Data & d1, Data & d2) {
  d1.swap(d2);
}

} // namespace pm
