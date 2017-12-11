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
#ifndef __PM_REGEXP_EXPRESSIONS_FUNCTIONS_HPP
#define __PM_REGEXP_EXPRESSIONS_FUNCTIONS_HPP

#include "pm/type_abuse/funs.hpp"
#include "pm/regexp/regexp.hpp"

namespace pm {
namespace regexp {

// apply binary function to [accumulator, source]
Regexp ac(const type_abuse::BinFun & f);
Regexp ac(type_abuse::BinFun && f);

// apply binary function to [source, accumulator]
Regexp as(const type_abuse::BinFun & f);
Regexp as(type_abuse::BinFun && f);

// modify accumulator with unary function
Regexp mc(const type_abuse::UnFun & f);
Regexp mc(type_abuse::UnFun && f);

// modify source with unary function
Regexp ms(const type_abuse::UnFun & f);
Regexp ms(type_abuse::UnFun && f);

} // namespace regexp
} // namespace pm

#endif
