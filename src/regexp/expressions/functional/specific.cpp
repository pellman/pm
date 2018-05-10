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
#include "pm/regexp/expressions/functional/specific.hpp"

#include "pm/type_abuse/funs.hpp"
#include "pm/regexp/expressions/functional/general.hpp"

namespace pm {
namespace regexp {

Regexp cget() {return ac(type_abuse::funs::clone());}
Regexp sget() {return as(type_abuse::funs::clone());}
Regexp swap() {return ac(type_abuse::funs::swap());}
Regexp cunset() {return mc(type_abuse::funs::unset());}
Regexp sunset() {return ms(type_abuse::funs::unset());}

Regexp cchar_to_string() {return mc(type_abuse::funs::char_to_string());}
Regexp schar_to_string() {return ms(type_abuse::funs::char_to_string());}

} // namespace regexp
} // namespace pm
