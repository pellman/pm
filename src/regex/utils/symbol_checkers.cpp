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
#include "pm/regex/utils/symbol_checkers.hpp"

//#include <functional>
//#include <set>
#include <utility>

namespace pm {
namespace regex {
namespace utils {

bool any_let(char) {
  return true;
}

bool no_let(char) {
  return false;
}

bool underscore_letter(char c) {
  return c == '_';
}

bool latin_lowercase_letter(char c) {
  return 'a' <= c && c <= 'z';
}

bool latin_uppercase_letter(char c) {
  return 'A' <= c && c <= 'Z';
}

bool decimal_letter(char c) {
  return '0' <= c && c <= '9';
}

bool latin_letter(char c) {
  return latin_lowercase_letter(c) || latin_uppercase_letter(c);
}

std::function<bool(char)> set(std::set<char> good_letters) {
  return [good_letters = std::move(good_letters)](char c) -> bool {
    return good_letters.find(c) != good_letters.end();
  };
}

std::function<bool(char)> range(char bottom, char top) {
  return [bottom, top](char c) -> bool {
    return bottom <= c && c <= top;
  };
}

std::function<bool(char)> let(char exact_letter) {
  return [exact_letter](char c) -> bool {
    return c == exact_letter;
  };
}

bool c_id_head_letter(char c) {
  return underscore_letter(c) || latin_lowercase_letter(c) || latin_uppercase_letter(c);
}

bool c_id_tail_letter(char c) {
  return c_id_head_letter(c) || decimal_letter(c);
}

} // namespace utils
} // namespace regex
} // namespace pm
