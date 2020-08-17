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
#include "pm/creation/char_set/specific.hpp"

#include "pm/creation/char_set/composition.hpp"
#include "pm/creation/char_set/terminal.hpp"

namespace pm::char_set {

CharSet decimal() {
  static CharSet res = range('0', '9');
  return res;
}

CharSet underscore() {
  static CharSet res = make('_');
  return res;
}

} // namespace pm::char_set

namespace pm::char_set::latin {

CharSet lowercase() {
  static CharSet res = range('a', 'z');
  return res;
}

CharSet uppercase() {
  static CharSet res = range('A', 'Z');
  return res;
}
CharSet any() {
  static CharSet res = lowercase() | uppercase();
  return res;
}

} // namespace pm::char_set::latin

namespace pm::char_set::c_id {

CharSet head() {
  static CharSet res = latin::any() | underscore();
  return res;
}

CharSet tail() {
  static CharSet res = head() | decimal();
  return res;
}

} // namespace pm::char_set::c_id
