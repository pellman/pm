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
#ifndef __PM_DATASET_FUNCTIONS_SPECIFIC_HPP
#define __PM_DATASET_FUNCTIONS_SPECIFIC_HPP

#include <cstddef>
#include <utility>
#include "pm/type_abuse/funs.hpp"
#include "pm/dataset/function.hpp"
#include "pm/dataset/functions/general.hpp"

namespace pm {
namespace dataset {

// untyped functions
Function clone(size_t target, size_t source);
template<typename T, typename ... Args>
Function set(size_t target, Args && ... args) {return dfun(type_abuse::funs::set<T>(std::forward<Args>(args) ...), target);}
Function swap(size_t target1, size_t target2);
Function unset(size_t target);

// arithmetics
template<typename Left, typename Right = Left>
Function add(size_t target_left, size_t target_right) {return dfun(type_abuse::funs::add<Left, Right>(), target_left, target_right);}
template<typename Left, typename Right>
Function add(size_t target, Right && i) {return dfun(type_abuse::funs::add<Left>(std::forward<Right>(i)), target);}
template<typename Left, typename Right = Left>
Function div(size_t target_left, size_t target_right) {return dfun(type_abuse::funs::div<Left, Right>(), target_left, target_right);}
template<typename Left, typename Right>
Function div(size_t target, Right && i) {return dfun(type_abuse::funs::div<Left>(std::forward<Right>(i)), target);}
template<typename Left, typename Right = Left>
Function mod(size_t target_left, size_t target_right) {return dfun(type_abuse::funs::mod<Left, Right>(), target_left, target_right);}
template<typename Left, typename Right>
Function mod(size_t target, Right && i) {return dfun(type_abuse::funs::mod<Left>(std::forward<Right>(i)), target);}
template<typename Left, typename Right = Left>
Function mul(size_t target_left, size_t target_right) {return dfun(type_abuse::funs::mul<Left, Right>(), target_left, target_right);}
template<typename Left, typename Right>
Function mul(size_t target, Right && i) {return dfun(type_abuse::funs::mul<Left>(std::forward<Right>(i)), target);}
template<typename Left, typename Right = Left>
Function sub(size_t target_left, size_t target_right) {return dfun(type_abuse::funs::sub<Left, Right>(), target_left, target_right);}
template<typename Left, typename Right>
Function sub(size_t target, Right && i) {return dfun(type_abuse::funs::sub<Left>(std::forward<Right>(i)), target);}

// conversion
template<typename Int>
Function char_to_digit(size_t target) {return dfun(type_abuse::funs::char_to_digit<Int>(), target);}
Function char_to_string(size_t target);
template<typename To, typename From>
Function convert(size_t target) {return dfun(type_abuse::funs::convert<To, From>(), target);}

} // namespace dataset
} // namespace pm

#endif
