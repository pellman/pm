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
#include "pm/regex/expressions/terminal/symbol.hpp"

//#include <set>
#include <utility>

#include "pm/regex/expressions/terminal/universal.hpp"
//#include "pm/regex/regex.hpp"
#include "pm/regex/utils/symbol_checkers.hpp"

namespace pm {
namespace regex {

namespace {

// core
Regex pre_let = symbol(utils::any_let);
Regex pre_c_id_head_letter = symbol(utils::c_id_head_letter);
Regex pre_c_id_tail_letter = symbol(utils::c_id_tail_letter);
Regex pre_decimal_letter = symbol(utils::decimal_letter);
Regex pre_latin_letter = symbol(utils::latin_letter);
Regex pre_latin_lowercase_letter = symbol(utils::latin_lowercase_letter);
Regex pre_latin_uppercase_letter = symbol(utils::latin_uppercase_letter);
Regex pre_underscore_letter = symbol(utils::underscore_letter);

} // namespace

// interface
Regex let() {
  return pre_let;
}

Regex let(char good_letter) {
  return symbol(utils::let(good_letter));
}

Regex let(std::set<char> good_letters) {
  return symbol(utils::set(std::move(good_letters)));
}

Regex range(char bottom, char top) {
  return symbol(utils::range(bottom, top));
}

Regex c_id_head_letter() {
  return pre_c_id_head_letter;
}

Regex c_id_tail_letter() {
  return pre_c_id_tail_letter;
}

Regex decimal_letter() {
  return pre_decimal_letter;
}

Regex latin_letter() {
  return pre_latin_letter;
}

Regex latin_lowercase_letter() {
  return pre_latin_lowercase_letter;
}

Regex latin_uppercase_letter() {
  return pre_latin_uppercase_letter;
}

Regex underscore_letter() {
  return pre_underscore_letter;
}

} // namespace regex
} // namespace pm
