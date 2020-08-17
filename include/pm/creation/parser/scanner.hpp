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
#ifndef PM_CREATION_PARSER_SCANNER_HPP
#define PM_CREATION_PARSER_SCANNER_HPP

#include <cstddef>

#include <string>

#include "pm/char_set.hpp"
#include "pm/parser.hpp"

namespace pm::parser::scanner {

Parser end();
Parser make(std::string s);
Parser make(size_t size);
Parser id(CharSet head, CharSet tail);
Parser id(CharSet cs);
Parser c_id();
Parser decimal();

} // namespace pm::parser::scanner

namespace pm::parser::scanner::suffix {

Parser strong(std::string s);
Parser weak(std::string s);

} // namespace pm::parser::scanner::suffix

namespace pm::parser::scanner::comment {

Parser strong(std::string open, std::string close);
Parser weak(std::string open, std::string close);

} // namespace pm::parser::scanner::comment

#endif
