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
#include "pm/regex/context.hpp"

//#include <string>
//#include "pm/data/data.hpp"

//#include "pm/regex/data_context.hpp"
//#include "pm/regex/string_context.hpp"

namespace pm {
namespace regex {

data::Data & Context::data(Target t) {
  return dc.data(t);
}

const data::Data & Context::data(Target t) const {
  return dc.data(t);
}

bool & Context::data_flag() {
  return dc.flag;
}

bool Context::data_flag() const {
  return dc.flag;
}

std::string & Context::str() {
  return sc.str;
}

const std::string & Context::str() const {
  return sc.str;
}

bool & Context::string_flag() {
  return sc.flag;
}

bool Context::string_flag() const {
  return sc.flag;
}

} // namespace regex
} // namespace pm