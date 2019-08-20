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
#include "pm/regex/expressions/terminal/string.hpp"

//#include <cstddef>
//#include <string>
#include <utility>

#include "pm/regex/expressions/terminal/universal.hpp"
//#include "pm/regex/regex.hpp"
#include "pm/regex/utils/string_scanners.hpp"

namespace pm {
namespace regex {

Regex str(std::string s) {
  return str(utils::str(std::move(s)));
}

Regex str(size_t size) {
  return str(utils::len(size));
}

Regex future_str(std::string s) {
  return str(utils::future(std::move(s)));
}

Regex future_opt_str(std::string s) {
  return str(utils::optional_future(std::move(s)));
}


} // namespace regex
} // namespace pm
