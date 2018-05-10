/*
    This file is part of the pm library package.
    Copyright (C) 2017, 2018 Vladislav Podymov
    
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
#ifndef __PM_REGEXP_EXPRESSIONS_TERMINAL_STRING_HPP
#define __PM_REGEXP_EXPRESSIONS_TERMINAL_STRING_HPP

#include <cstddef>
#include <string>
#include "pm/regexp/regexp.hpp"

namespace pm {
namespace regexp {

// = general =
Regexp str(const std::string & good_string);
Regexp str(std::string && good_string);
Regexp str(size_t len);

Regexp enclose(const std::string & opening_string, const std::string & closing_string);
Regexp enclose(const std::string & opening_string, std::string && closing_string);
Regexp enclose(std::string && opening_string, const std::string & closing_string);
Regexp enclose(std::string && opening_string, std::string && closing_string);

// = specific =
Regexp c_id();
Regexp decimal_string();
Regexp id(const Regexp & letter);
Regexp id(const Regexp & head_letter, const Regexp & tail_letter);

} // namespace regexp
} // namespace pm

#endif