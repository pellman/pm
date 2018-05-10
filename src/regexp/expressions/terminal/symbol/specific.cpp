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
#include "pm/regexp/expressions/terminal/symbol.hpp"

#include "pm/regexp/expressions/flow/control.hpp"

namespace pm {
namespace regexp {

Regexp digit_letter() {return range('0', '9');}
Regexp latin_letter() {return alt(latin_lowercase_letter(), latin_uppercase_letter());}
Regexp latin_lowercase_letter() {return range('a', 'z');}
Regexp latin_uppercase_letter() {return range('A', 'Z');}
Regexp underscore_letter() {return let('_');}
Regexp c_id_head_letter() {return alt(latin_letter(), underscore_letter());}
Regexp c_id_tail_letter() {return alt(c_id_head_letter(), digit_letter());}

} // namespace regexp
} // namespace pm
