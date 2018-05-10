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
#include "pm/dataset/functions/specific.hpp"

#include "pm/type_abuse/funs.hpp"
#include "pm/dataset/functions/general.hpp"

namespace pm {
namespace dataset {

Function clone(size_t target1, size_t target2) {return dfun(type_abuse::funs::clone(), target1, target2);}
Function swap(size_t target1, size_t target2) {return dfun(type_abuse::funs::swap(), target1, target2);}
Function unset(size_t target) {return dfun(type_abuse::funs::unset(), target);}

Function char_to_string(size_t target) {return dfun(type_abuse::funs::char_to_string(), target);}

} // namespace dataset
} // namespace pm
