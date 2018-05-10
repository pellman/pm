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
#include "pm/regexp/expressions/terminal/string.hpp"

#include <string>
#include "pm/regexp/expressions/flow/control.hpp"
#include "pm/regexp/expressions/flow/data.hpp"
#include "pm/regexp/expressions/functional/specific.hpp"
#include "pm/regexp/expressions/terminal/symbol.hpp"

namespace pm {
namespace regexp {

Regexp decimal_string() {return id(digit_letter());}
Regexp c_id() {return id(c_id_head_letter(), c_id_tail_letter());}
Regexp id(const Regexp & letter) {return id(letter, letter);}
Regexp id(const Regexp & head_letter, const Regexp & tail_letter) {return concat(head_letter, cchar_to_string(), hide(concat(swap(), star(concat(tail_letter, sadd<std::string, char>())), swap())));}

} // namespace regexp
} // namespace pm
