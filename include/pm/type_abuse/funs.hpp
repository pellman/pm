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
#ifndef __PM_TYPE_ABUSE_FUNS_HPP
#define __PM_TYPE_ABUSE_FUNS_HPP

#include <functional>
#include "pm/type_abuse/dptr.hpp"
#include "pm/type_abuse/functions.hpp"
#include "pm/type_abuse/mutators.hpp"

namespace pm {
namespace type_abuse {

typedef std::function<void(const DPtr &, const DPtr &)> BinFun;
typedef std::function<void(const DPtr &)> UnFun;

namespace funs {

// untyped funs
BinFun clone();
BinFun swap();
UnFun unset();
template<typename DataType, typename ... Args>
UnFun set(Args && ... args) {return mutator_part(type_abuse::funs::clone(), make_dptr<DataType>(std::forward<Args>(args) ...));}

// arithmetic
template<typename Left, typename Right = Left>
BinFun add() {return type_abuse::add<Left, Right>;}
template<typename Left, typename Right>
UnFun add(Right && i) {return mutator_part(type_abuse::funs::add<Left, Right>(), make_dptr<Right>(std::forward<Right>(i)));}
template<typename Left, typename Right = Left>
BinFun div() {return type_abuse::div<Left, Right>;}
template<typename Left, typename Right>
UnFun div(Right && i) {return mutator_part(type_abuse::funs::div<Left, Right>(), make_dptr<Right>(std::forward<Right>(i)));}
template<typename Left, typename Right = Left>
BinFun mod() {return type_abuse::mod<Left, Right>;}
template<typename Left, typename Right>
UnFun mod(Right && i) {return mutator_part(type_abuse::funs::mod<Left, Right>(), make_dptr<Right>(std::forward<Right>(i)));}
template<typename Left, typename Right = Left>
BinFun mul() {return type_abuse::mul<Left, Right>;}
template<typename Left, typename Right>
UnFun mul(Right && i) {return mutator_part(type_abuse::funs::mul<Left, Right>(), make_dptr<Right>(std::forward<Right>(i)));}
template<typename Left, typename Right = Left>
BinFun sub() {return type_abuse::sub<Left, Right>;}
template<typename Left, typename Right>
UnFun sub(Right && i) {return mutator_part(type_abuse::funs::sub<Left, Right>(), make_dptr<Right>(std::forward<Right>(i)));}

// conversion
template<typename To, typename From>
UnFun convert() {return type_abuse::convert<To, From>;}
template<typename Int>
UnFun char_to_digit() {return type_abuse::char_to_digit<Int>;}
UnFun char_to_string();

// typed function object wrappers
template<typename Arg1, typename Arg2>
BinFun bref(const std::function<void(Arg1, Arg2)> & f) {return mutator_ref(f);}
template<typename Arg1, typename Arg2>
BinFun bref(std::function<void(Arg1, Arg2)> && f) {return mutator_ref(std::move(f));}
template<typename Ret, typename Arg1, typename Arg2>
BinFun bren(const std::function<Ret(Arg1, Arg2)> & f) {return mutator_ren(f);}
template<typename Ret, typename Arg1, typename Arg2>
BinFun bren(std::function<Ret(Arg1, Arg2)> && f) {return mutator_ren(std::move(f));}
template<typename Ret, typename Arg>
BinFun bret(const std::function<Ret(Arg)> & f) {return mutator_ret(f);}
template<typename Ret, typename Arg>
BinFun bret(std::function<Ret(Arg)> && f) {return mutator_ret(std::move(f));}
template<typename Arg>
UnFun uref(const std::function<void(Arg)> & f) {return mutator_ref(f);}
template<typename Arg>
UnFun uref(std::function<void(Arg)> && f) {return mutator_ref(std::move(f));}
template<typename Ret, typename Arg>
UnFun uren(const std::function<Ret(Arg)> & f) {return mutator_ren(f);}
template<typename Ret, typename Arg>
UnFun uren(std::function<Ret(Arg)> && f) {return mutator_ren(std::move(f));}
template<typename Ret>
UnFun uret(const std::function<Ret()> & f) {return mutator_ret(f);}
template<typename Ret>
UnFun uret(std::function<Ret()> && f) {return mutator_ret(std::move(f));}

// typed global function wrappers
template<typename AnyRet, typename Arg1, typename Arg2>
BinFun ref(AnyRet (*f)(Arg1, Arg2)) {return bref<Arg1, Arg2>(f);}
template<typename AnyRet, typename Arg>
UnFun ref(AnyRet (*f)(Arg)) {return uref<Arg>(f);}
template<typename Ret, typename Arg1, typename Arg2>
BinFun ren(Ret (*f)(Arg1, Arg2)) {return bren<Ret, Arg1, Arg2>(f);}
template<typename Ret, typename Arg>
UnFun ren(Ret (*f)(Arg)) {return uren<Ret, Arg>(f);}
template<typename Ret, typename Arg>
BinFun ret(Ret (*f)(Arg)) {return bret<Ret, Arg>(f);}
template<typename Ret>
UnFun ret(Ret (*f)()) {return uret<Ret>(f);}

} // namespace funs
} // namespace type_abuse
} // namespace pm

#endif
