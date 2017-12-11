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
#ifndef __PM_TYPE_ABUSE_FUNCTIONS_HPP
#define __PM_TYPE_ABUSE_FUNCTIONS_HPP

#include <utility>
#include "pm/type_abuse/dptr.hpp"

namespace pm {
namespace type_abuse {

// untyped functions
void clone(const DPtr & ptr1, const DPtr & ptr2);
void swap(const DPtr & ptr1, const DPtr & ptr2);
void unset(const DPtr & ptr);

// arithmetic
template<typename Left, typename Right = Left>
void add(const DPtr & ptr1, const DPtr & ptr2) {ptr1.val<Left>() += ptr2.val<Right>();}
template<typename Left, typename Right = Left>
void div(const DPtr & ptr1, const DPtr & ptr2) {ptr1.val<Left>() /= ptr2.val<Right>();}
template<typename Left, typename Right = Left>
void mod(const DPtr & ptr1, const DPtr & ptr2) {ptr1.val<Left>() %= ptr2.val<Right>();}
template<typename Left, typename Right = Left>
void mul(const DPtr & ptr1, const DPtr & ptr2) {ptr1.val<Left>() *= ptr2.val<Right>();}
template<typename Left, typename Right = Left>
void sub(const DPtr & ptr1, const DPtr & ptr2) {ptr1.val<Left>() -= ptr2.val<Right>();}

// conversion
template<typename To, typename From>
void convert(const DPtr & ptr) {ptr.set<To>(std::move(ptr.val<From>()));}
template<typename Int>
void char_to_digit(const DPtr & ptr) {ptr.set<Int>(ptr.val<char>() - '0');}
void char_to_string(const DPtr & ptr);

} // namespace type_abuse
} // namespace pm

#endif
