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
#include "pm/creation/parser/generator/untyped.hpp"

#include "pm/creation/parser/functional.hpp"

namespace pm::parser::generator {

Parser copy() {
  static Parser res =
    fexecute(
  [](Stream &, Context & con) {
    con[1] = con[0];
  }
    );
  return res;
}

Parser swap() {
  static Parser res =
    fexecute(
  [](Stream &, Context & con) {
    swap(con[0], con[1]);
  }
    );
  return res;
}

Parser unset() {
  static Parser res =
    fexecute(
  [](Stream &, Context & con) {
    con[0].reset();
  }
    );
  return res;
}

} // namespace pm::parser::generator
