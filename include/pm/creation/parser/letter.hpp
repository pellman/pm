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
#ifndef PM_CREATION_PARSER_LETTER_HPP
#define PM_CREATION_PARSER_LETTER_HPP

#include <set>

#include "pm/char_set.hpp"
#include "pm/parser.hpp"

namespace pm::parser::letter {

Parser make(char c);
Parser make(std::set<char> cs);
Parser make(CharSet cs);
Parser range(char bottom, char top);
Parser total();
Parser decimal();
Parser underscore();

} // namespace pm::parser::letter

namespace pm::parser::letter::latin {

Parser lowercase();
Parser uppercase();
Parser any();

} // namespace pm::parser::letter::latin

namespace pm::parser::letter::c_id {

Parser head();
Parser tail();

} // namespace pm::parser::letter::c_id

#endif
