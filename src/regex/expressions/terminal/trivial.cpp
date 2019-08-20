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
#include "pm/regex/expressions/terminal/trivial.hpp"

#include "pm/regex/expressions/terminal/universal.hpp"
//#include "pm/regex/regex.hpp"
#include "pm/regex/utils/trivial_scanners.hpp"

namespace pm {
namespace regex {

namespace {

// core
Regex pre_end = trivial(utils::trivial_end);
Regex pre_false = trivial(utils::trivial_false);
Regex pre_true = trivial(utils::trivial_true);

} // namespace

// interface
Regex end() {
  return pre_end;
}

Regex re_false() {
  return pre_false;
}

Regex re_true() {
  return pre_true;
}

} // namespace regex
} // namespace pm
