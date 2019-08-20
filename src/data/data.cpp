/*
    This file is part of the pm library package.
    Copyright (C) 2017-2019 Vladislav Podymov

    This library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the1
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    To contact author, email to <vpod@cs.msu.ru>
 */
#include "pm/data/data.hpp"

//#include <memory>
//#include <utility>

//#include "pm/data/utils/dbase.hpp"

namespace pm {
namespace data {

Data::Data(const Data & d)
  : ptr_(d.ptr_ == nullptr ? nullptr : d.ptr_->clone()) {}

Data::Data(Data && d)
  : ptr_(std::move(d.ptr_)) {}

Data & Data::operator =(const Data & d) {
  ptr_.reset(d.ptr_ == nullptr ? nullptr : d.ptr_->clone());
  return *this;
}

Data & Data::operator =(Data && d) {
  // TODO implement as swap?
  ptr_ = std::move(d.ptr_);
  return *this;
}

void Data::swap(Data & d) {
  ptr_.swap(d.ptr_);
}

void Data::unset() {
  ptr_.reset();
}

Data Data::clone() const {
  return ptr_ == nullptr
         ? Data()
         : Data(ptr_->clone());
}

bool Data::empty() const {
  return !nonempty();
}

bool Data::nonempty() const {
  return static_cast<bool>(ptr_);
}

Data::Data(utils::DBase * ptr)
  : ptr_(ptr) {}

} // namespace data
} // namespace pm
