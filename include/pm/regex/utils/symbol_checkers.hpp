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
#ifndef PM_REGEX_UTILS_SYMBOL_CHECKERS_HPP
#define PM_REGEX_UTILS_SYMBOL_CHECKERS_HPP

#include <functional>
#include <set>

namespace pm {
namespace regex {
namespace utils {

bool any_let(char c);
bool no_let(char c);
bool underscore_letter(char c);
bool latin_lowercase_letter(char c);
bool latin_uppercase_letter(char c);
bool decimal_letter(char c);
bool latin_letter(char c);
std::function<bool(char)> set(std::set<char> good_letters);
std::function<bool(char)> range(char bottom, char top);
std::function<bool(char)> let(char exact_letter);
bool c_id_head_letter(char c);
bool c_id_tail_letter(char c);

} // namespace utils
} // namespace regex
} // namespace pm

#endif
