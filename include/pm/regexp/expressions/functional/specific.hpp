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
#ifndef __PM_REGEXP_EXPRESSIONS_FUNCTIONAL_SPECIFIC_HPP
#define __PM_REGEXP_EXPRESSIONS_FUNCTIONAL_SPECIFIC_HPP

#include <utility>
#include "pm/type_abuse/funs.hpp"
#include "pm/regexp/expressions/functional/general.hpp"
#include "pm/regexp/regexp.hpp"

namespace pm {
namespace regexp {

// untyped data manipulation
Regexp cget();
Regexp sget();
template<typename NewStoredValue, typename ... Args>
Regexp cset(Args && ... args) {return mc(type_abuse::funs::set<NewStoredValue>(std::forward<Args>(args) ...));}
template<typename NewStoredValue, typename ... Args>
Regexp sset(Args && ... args) {return ms(type_abuse::funs::set<NewStoredValue>(std::forward<Args>(args) ...));}
Regexp swap();
Regexp cunset();
Regexp sunset();

// arithmetics
template<typename Left, typename Right = Left>
Regexp cadd() {return ac(type_abuse::funs::add<Left, Right>());}
template<typename Left, typename Right>
Regexp cadd(Right && i) {return mc(type_abuse::funs::add<Left>(std::forward<Right>(i)));}
template<typename Left, typename Right = Left>
Regexp cdiv() {return ac(type_abuse::funs::div<Left, Right>());}
template<typename Left, typename Right>
Regexp cdiv(Right && i) {return mc(type_abuse::funs::div<Left>(std::forward<Right>(i)));}
template<typename Left, typename Right = Left>
Regexp cmod() {return ac(type_abuse::funs::mod<Left, Right>());}
template<typename Left, typename Right>
Regexp cmod(Right && i) {return mc(type_abuse::funs::mod<Left>(std::forward<Right>(i)));}
template<typename Left, typename Right = Left>
Regexp cmul() {return ac(type_abuse::funs::mul<Left, Right>());}
template<typename Left, typename Right>
Regexp cmul(Right && i) {return mc(type_abuse::funs::mul<Left>(std::forward<Right>(i)));}
template<typename Left, typename Right = Left>
Regexp csub() {return ac(type_abuse::funs::sub<Left, Right>());}
template<typename Left, typename Right>
Regexp csub(Right && i) {return mc(type_abuse::funs::sub<Left>(std::forward<Right>(i)));}
template<typename Left, typename Right = Left>
Regexp sadd() {return as(type_abuse::funs::add<Left, Right>());}
template<typename Left, typename Right>
Regexp sadd(Right && i) {return ms(type_abuse::funs::add<Left>(std::forward<Right>(i)));}
template<typename Left, typename Right = Left>
Regexp sdiv() {return as(type_abuse::funs::div<Left, Right>());}
template<typename Left, typename Right>
Regexp sdiv(Right && i) {return ms(type_abuse::funs::div<Left>(std::forward<Right>(i)));}
template<typename Left, typename Right = Left>
Regexp smod() {return as(type_abuse::funs::mod<Left, Right>());}
template<typename Left, typename Right>
Regexp smod(Right && i) {return ms(type_abuse::funs::mod<Left>(std::forward<Right>(i)));}
template<typename Left, typename Right = Left>
Regexp smul() {return as(type_abuse::funs::mul<Left, Right>());}
template<typename Left, typename Right>
Regexp smul(Right && i) {return ms(type_abuse::funs::mul<Left>(std::forward<Right>(i)));}
template<typename Left, typename Right = Left>
Regexp ssub() {return as(type_abuse::funs::sub<Left, Right>());}
template<typename Left, typename Right>
Regexp ssub(Right && i) {return ms(type_abuse::funs::sub<Left>(std::forward<Right>(i)));}

// conversion
template<typename Int>
Regexp cchar_to_digit() {return mc(type_abuse::funs::char_to_digit<Int>());}
Regexp cchar_to_string();
template<typename To, typename From>
Regexp cconvert() {return mc(type_abuse::funs::convert<To, From>());}
template<typename Int>
Regexp schar_to_digit() {return ms(type_abuse::funs::char_to_digit<Int>());}
Regexp schar_to_string();
template<typename To, typename From>
Regexp sconvert() {return ms(type_abuse::funs::convert<To, From>());}

} // namespace regexp
} // namespace pm

#endif
