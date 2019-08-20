/*
    This file is part of the pm library package.
    Copyright (C) 2017-2019 Vladislav Podymov

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
#include "pm/set/set.hpp"

//#include <cstddef>
//#include <memory>
//#include <vector>
//#include "pm/data/data.hpp"

namespace pm {
namespace set {

data::Data & Set::operator [](size_t index) {
  return data(index);
}

data::Data & Set::data(size_t index) {
  if(index >= set_.size()) {
    set_.resize(index + 1);
  }
  auto & ptr = set_[index];
  if(!ptr) {
    ptr.reset(new data::Data());
  }
  return *ptr;
}

} // namespace set
} // namespace pm
