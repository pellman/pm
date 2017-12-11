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
#include "pm/type_abuse/funs.hpp"

#include "pm/type_abuse/functions.hpp"

namespace pm {
namespace type_abuse {
namespace funs {

BinFun clone() {return type_abuse::clone;}
BinFun swap() {return type_abuse::swap;}
UnFun unset() {return type_abuse::unset;}
UnFun char_to_string() {return type_abuse::char_to_string;}

} // namespace funs
} // namespace type_abuse
} // namespace pm
