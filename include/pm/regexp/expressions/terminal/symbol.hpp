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
#ifndef __PM_REGEXP_EXPRESSIONS_TERMINAL_SYMBOL_HPP
#define __PM_REGEXP_EXPRESSIONS_TERMINAL_SYMBOL_HPP

#include <set>
#include <utility>
#include "pm/regexp/regexp.hpp"

namespace pm {
namespace regexp {

// = general =
Regexp let();
Regexp let(char good_char);
Regexp let(const std::set<char> & good_chars);
Regexp let(std::set<char> && good_chars);
template<typename ... Args>
Regexp let(Args && ... args) {return let(std::set<char>{std::forward<Args>(args) ...});}

Regexp range(char bottom_char, char top_char);

// = special =
Regexp c_id_head_letter();
Regexp c_id_tail_letter();
Regexp digit_letter();
Regexp latin_letter();
Regexp latin_lowercase_letter();
Regexp latin_uppercase_letter();
Regexp underscore_letter();

} // namespace regexp
} // namespace pm

#endif
