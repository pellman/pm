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
#include "pm/domain.hpp"

namespace pm {

size_t Domain::operator [](const std::string & name) const {
  return map_.insert({name, map_.size()}).first->second;
}

std::vector<size_t> Domain::operator [](const std::vector<std::string> & names) const {
  std::vector<size_t> res(names.size());
  for(size_t i = 0; i < names.size(); ++i) {
    res[i] = operator [](names[i]);
  }
  return res;
}

} // namespace pm
