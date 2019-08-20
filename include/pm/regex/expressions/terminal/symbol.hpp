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
#ifndef PM_REGEX_EXPRESSIONS_TERMINAL_SYMBOL_HPP
#define PM_REGEX_EXPRESSIONS_TERMINAL_SYMBOL_HPP

#include <set>

#include "pm/regex/regex.hpp"

namespace pm {
namespace regex {

// = general =
Regex let();
Regex let(char good_letter);
Regex let(std::set<char> good_letters);
Regex range(char bottom, char top);

// = specific =
Regex c_id_head_letter();
Regex c_id_tail_letter();
Regex decimal_letter();
Regex latin_letter();
Regex latin_lowercase_letter();
Regex latin_uppercase_letter();
Regex underscore_letter();

} // namespace regex
} // namespace pm

#endif
