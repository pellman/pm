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
#include "pm/grammar/utils/model.hpp"

//#include <cstddef>
//#include <memory>
#include <utility>
//#include <vector>

//#include "pm/grammar/utils/action.hpp"

namespace pm {
namespace grammar {
namespace utils {

Action & Model::operator [](size_t index) {
  return vec_[index];
}

size_t Model::add(Action a) {
  size_t res = vec_.size();
  vec_.push_back(std::move(a));
  return res;
}

} // namespace utils
} // namespace grammar
} // namespace pm
