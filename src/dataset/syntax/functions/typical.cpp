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
#include "pm/dataset/syntax/functions/typical.hpp"

#include "pm/type_abuse/funs.hpp"
#include "pm/dataset/syntax/functions/base.hpp"

namespace pm {
namespace dataset {
namespace syntax {

Function clone(const std::string & target1, const std::string & target2) {return dfun(type_abuse::funs::clone(), target1, target2);}
Function clone(const std::string & target1, std::string && target2) {return dfun(type_abuse::funs::clone(), target1, std::move(target2));}
Function clone(std::string && target1, const std::string & target2) {return dfun(type_abuse::funs::clone(), std::move(target1), target2);}
Function clone(std::string && target1, std::string && target2) {return dfun(type_abuse::funs::clone(), std::move(target1), std::move(target2));}

Function swap(const std::string & target1, const std::string & target2) {return dfun(type_abuse::funs::swap(), target1, target2);}
Function swap(const std::string & target1, std::string && target2) {return dfun(type_abuse::funs::swap(), target1, std::move(target2));}
Function swap(std::string && target1, const std::string & target2) {return dfun(type_abuse::funs::swap(), std::move(target1), target2);}
Function swap(std::string && target1, std::string && target2) {return dfun(type_abuse::funs::swap(), std::move(target1), std::move(target2));}

Function unset(const std::string & target) {return dfun(type_abuse::funs::unset(), target);}
Function unset(std::string && target) {return dfun(type_abuse::funs::unset(), std::move(target));}

Function char_to_string(const std::string & target) {return dfun(type_abuse::funs::char_to_string(), target);}
Function char_to_string(std::string && target) {return dfun(type_abuse::funs::char_to_string(), std::move(target));}

} // namespace syntax
} // namespace dataset
} // namespace pm
