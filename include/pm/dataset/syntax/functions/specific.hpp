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
#ifndef __PM_DATASET_SYNTAX_FUNCTIONS_SPECIFIC_HPP
#define __PM_DATASET_SYNTAX_FUNCTIONS_SPECIFIC_HPP

#include <string>
#include <utility>
#include "pm/type_abuse/funs.hpp"
#include "pm/dataset/syntax/function.hpp"
#include "pm/dataset/syntax/functions/general.hpp"

namespace pm {
namespace dataset {
namespace syntax {

// untyped functions
Function clone(const std::string & target, const std::string & source);
Function clone(const std::string & target, std::string && source);
Function clone(std::string && target, const std::string & source);
Function clone(std::string && target, std::string && source);

template<typename T, typename ... Args>
Function set(const std::string & target, Args && ... args) {return dfun(type_abuse::funs::set<T>(std::forward<Args>(args) ...), target);}
template<typename T, typename ... Args>
Function set(std::string && target, Args && ... args) {return dfun(type_abuse::funs::set<T>(std::forward<Args>(args) ...), std::move(target));}

Function swap(const std::string & target1, const std::string & target2);
Function swap(const std::string & target1, std::string && target2);
Function swap(std::string && target1, const std::string & target2);
Function swap(std::string && target1, std::string && target2);

Function unset(const std::string & target);
Function unset(std::string && target);

// arithmetics
template<typename Left, typename Right = Left>
Function add(const std::string & target_left, const std::string & target_right) {return dfun(type_abuse::funs::add<Left, Right>(), target_left, target_right);}
template<typename Left, typename Right = Left>
Function add(const std::string & target_left, std::string && target_right) {return dfun(type_abuse::funs::add<Left, Right>(), target_left, std::move(target_right));}
template<typename Left, typename Right = Left>
Function add(std::string && target_left, const std::string & target_right) {return dfun(type_abuse::funs::add<Left, Right>(), std::move(target_left), target_right);}
template<typename Left, typename Right = Left>
Function add(std::string && target_left, std::string && target_right) {return dfun(type_abuse::funs::add<Left, Right>(), std::move(target_left), std::move(target_right));}
template<typename Left, typename Right>
Function add(const std::string & target, Right && i) {return dfun(type_abuse::funs::add<Left>(std::move(i)), target);}
template<typename Left, typename Right>
Function add(std::string && target, Right && i) {return dfun(type_abuse::funs::add<Left>(std::move(i)), std::move(target));}
template<typename Left, typename Right = Left>
Function div(const std::string & target_left, const std::string & target_right) {return dfun(type_abuse::funs::div<Left, Right>(), target_left, target_right);}
template<typename Left, typename Right = Left>
Function div(const std::string & target_left, std::string && target_right) {return dfun(type_abuse::funs::div<Left, Right>(), target_left, std::move(target_right));}
template<typename Left, typename Right = Left>
Function div(std::string && target_left, const std::string & target_right) {return dfun(type_abuse::funs::div<Left, Right>(), std::move(target_left), target_right);}
template<typename Left, typename Right = Left>
Function div(std::string && target_left, std::string && target_right) {return dfun(type_abuse::funs::div<Left, Right>(), std::move(target_left), std::move(target_right));}
template<typename Left, typename Right>
Function div(const std::string & target, Right && i) {return dfun(type_abuse::funs::div<Left>(std::move(i)), target);}
template<typename Left, typename Right>
Function div(std::string && target, Right && i) {return dfun(type_abuse::funs::div<Left>(std::move(i)), std::move(target));}
template<typename Left, typename Right = Left>
Function mod(const std::string & target_left, const std::string & target_right) {return dfun(type_abuse::funs::mod<Left, Right>(), target_left, target_right);}
template<typename Left, typename Right = Left>
Function mod(const std::string & target_left, std::string && target_right) {return dfun(type_abuse::funs::mod<Left, Right>(), target_left, std::move(target_right));}
template<typename Left, typename Right = Left>
Function mod(std::string && target_left, const std::string & target_right) {return dfun(type_abuse::funs::mod<Left, Right>(), std::move(target_left), target_right);}
template<typename Left, typename Right = Left>
Function mod(std::string && target_left, std::string && target_right) {return dfun(type_abuse::funs::mod<Left, Right>(), std::move(target_left), std::move(target_right));}
template<typename Left, typename Right>
Function mod(const std::string & target, Right && i) {return dfun(type_abuse::funs::mod<Left>(std::move(i)), target);}
template<typename Left, typename Right>
Function mod(std::string && target, Right && i) {return dfun(type_abuse::funs::mod<Left>(std::move(i)), std::move(target));}
template<typename Left, typename Right = Left>
Function mul(const std::string & target_left, const std::string & target_right) {return dfun(type_abuse::funs::mul<Left, Right>(), target_left, target_right);}
template<typename Left, typename Right = Left>
Function mul(const std::string & target_left, std::string && target_right) {return dfun(type_abuse::funs::mul<Left, Right>(), target_left, std::move(target_right));}
template<typename Left, typename Right = Left>
Function mul(std::string && target_left, const std::string & target_right) {return dfun(type_abuse::funs::mul<Left, Right>(), std::move(target_left), target_right);}
template<typename Left, typename Right = Left>
Function mul(std::string && target_left, std::string && target_right) {return dfun(type_abuse::funs::mul<Left, Right>(), std::move(target_left), std::move(target_right));}
template<typename Left, typename Right>
Function mul(const std::string & target, Right && i) {return dfun(type_abuse::funs::mul<Left>(std::move(i)), target);}
template<typename Left, typename Right>
Function mul(std::string && target, Right && i) {return dfun(type_abuse::funs::mul<Left>(std::move(i)), std::move(target));}
template<typename Left, typename Right = Left>
Function sub(const std::string & target_left, const std::string & target_right) {return dfun(type_abuse::funs::sub<Left, Right>(), target_left, target_right);}
template<typename Left, typename Right = Left>
Function sub(const std::string & target_left, std::string && target_right) {return dfun(type_abuse::funs::sub<Left, Right>(), target_left, std::move(target_right));}
template<typename Left, typename Right = Left>
Function sub(std::string && target_left, const std::string & target_right) {return dfun(type_abuse::funs::sub<Left, Right>(), std::move(target_left), target_right);}
template<typename Left, typename Right = Left>
Function sub(std::string && target_left, std::string && target_right) {return dfun(type_abuse::funs::sub<Left, Right>(), std::move(target_left), std::move(target_right));}
template<typename Left, typename Right>
Function sub(const std::string & target, Right && i) {return dfun(type_abuse::funs::sub<Left>(std::move(i)), target);}
template<typename Left, typename Right>
Function sub(std::string && target, Right && i) {return dfun(type_abuse::funs::sub<Left>(std::move(i)), std::move(target));}

// conversion
template<typename Int>
Function char_to_digit(const std::string & target) {return dfun(type_abuse::funs::char_to_digit<Int>(), target);}
template<typename Int>
Function char_to_digit(std::string && target) {return dfun(type_abuse::funs::char_to_digit<Int>(), std::move(target));}
Function char_to_string(const std::string & target);
Function char_to_string(std::string && target);
template<typename To, typename From>
Function convert(const std::string & target) {return dfun(type_abuse::funs::convert<To, From>(), target);}
template<typename To, typename From>
Function convert(std::string && target) {return dfun(type_abuse::funs::convert<To, From>(), std::move(target));}

} // namespace syntax
} // namespace dataset
} // namespace pm

#endif
