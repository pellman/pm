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
#include "pm/data/utils/functions.hpp"

//#include <utility>

//#include "pm/data/data.hpp"

namespace pm {
namespace data {
namespace utils {

void equalize(Data & d_target, Data & d_source) {
  d_target = d_source;
}

void swap(Data & d1, Data & d2) {
  d1.swap(d2);
}

void unset(Data & d) {
  d.unset();
}

} // namespace utils
} // namespace data
} // namespace pm
