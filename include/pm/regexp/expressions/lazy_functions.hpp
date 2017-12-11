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
#ifndef __PM_REGEXP_EXPRESSIONS_LAZY_FUNCTIONS_HPP
#define __PM_REGEXP_EXPRESSIONS_LAZY_FUNCTIONS_HPP

#include <utility>
#include "pm/type_abuse/funs.hpp"
#include "pm/regexp/expressions/functions.hpp"
#include "pm/regexp/regexp.hpp"

namespace pm {
namespace regexp {

// typed function object wrappers
template<typename Arg1, typename Arg2, typename Fun>
Regexp acref(Fun && f);
template<typename Ret, typename Arg1, typename Arg2, typename Fun>
Regexp acren(Fun && f);
template<typename Ret, typename Arg, typename Fun>
Regexp acret(Fun && f);
template<typename Arg1, typename Arg2, typename Fun>
Regexp asref(Fun && f);
template<typename Ret, typename Arg1, typename Arg2, typename Fun>
Regexp asren(Fun && f);
template<typename Ret, typename Arg, typename Fun>
Regexp asret(Fun && f);
template<typename Arg, typename Fun>
Regexp mcref(Fun && f);
template<typename Ret, typename Arg, typename Fun>
Regexp mcren(Fun && f);
template<typename Ret, typename Fun>
Regexp mcret(Fun && f);
template<typename Arg, typename Fun>
Regexp msref(Fun && f);
template<typename Ret, typename Arg, typename Fun>
Regexp msren(Fun && f);
template<typename Ret, typename Fun>
Regexp msret(Fun && f);

// typed global function wrappers
template<typename AnyRet, typename Arg1, typename Arg2>
Regexp cref(AnyRet (*f)(Arg1, Arg2));
template<typename AnyRet, typename Arg>
Regexp cref(AnyRet (*f)(Arg));
template<typename Ret, typename Arg1, typename Arg2>
Regexp cren(Ret (*f)(Arg1, Arg2));
template<typename Ret, typename Arg>
Regexp cren(Ret (*f)(Arg));
template<typename Ret, typename Arg>
Regexp cret(Ret (*f)(Arg));
template<typename Ret>
Regexp cret(Ret (*f)());
template<typename AnyRet, typename Arg1, typename Arg2>
Regexp sref(AnyRet (*f)(Arg1, Arg2));
template<typename AnyRet, typename Arg>
Regexp sref(AnyRet (*f)(Arg));
template<typename Ret, typename Arg1, typename Arg2>
Regexp sren(Ret (*f)(Arg1, Arg2));
template<typename Ret, typename Arg>
Regexp sren(Ret (*f)(Arg));
template<typename Ret, typename Arg>
Regexp sret(Ret (*f)(Arg));
template<typename Ret>
Regexp sret(Ret (*f)());


// implementation
template<typename Arg1, typename Arg2, typename Fun>
Regexp acref(Fun && f) {return ac(type_abuse::funs::bref<Arg1, Arg2>(std::forward<Fun>(f)));}
template<typename Ret, typename Arg1, typename Arg2, typename Fun>
Regexp acren(Fun && f) {return ac(type_abuse::funs::bren<Ret, Arg1, Arg2>(std::forward<Fun>(f)));}
template<typename Ret, typename Arg, typename Fun>
Regexp acret(Fun && f) {return ac(type_abuse::funs::bret<Ret, Arg>(std::forward<Fun>(f)));}
template<typename Arg1, typename Arg2, typename Fun>
Regexp asref(Fun && f) {return as(type_abuse::funs::bref<Arg1, Arg2>(std::forward<Fun>(f)));}
template<typename Ret, typename Arg1, typename Arg2, typename Fun>
Regexp asren(Fun && f) {return as(type_abuse::funs::bren<Ret, Arg1, Arg2>(std::forward<Fun>(f)));}
template<typename Ret, typename Arg, typename Fun>
Regexp asret(Fun && f) {return as(type_abuse::funs::bret<Ret, Arg>(std::forward<Fun>(f)));}
template<typename Arg, typename Fun>
Regexp mcref(Fun && f) {return mc(type_abuse::funs::uref<Arg>(std::forward<Fun>(f)));}
template<typename Ret, typename Arg, typename Fun>
Regexp mcren(Fun && f) {return mc(type_abuse::funs::uren<Ret, Arg>(std::forward<Fun>(f)));}
template<typename Ret, typename Fun>
Regexp mcret(Fun && f) {return mc(type_abuse::funs::uret<Ret>(std::forward<Fun>(f)));}
template<typename Arg, typename Fun>
Regexp msref(Fun && f) {return ms(type_abuse::funs::uref<Arg>(std::forward<Fun>(f)));}
template<typename Ret, typename Arg, typename Fun>
Regexp msren(Fun && f) {return ms(type_abuse::funs::uren<Ret, Arg>(std::forward<Fun>(f)));}
template<typename Ret, typename Fun>
Regexp msret(Fun && f) {return ms(type_abuse::funs::uret<Ret>(std::forward<Fun>(f)));}

template<typename AnyRet, typename Arg1, typename Arg2>
Regexp cref(AnyRet (*f)(Arg1, Arg2)) {return acref<Arg1, Arg2>(f);}
template<typename AnyRet, typename Arg>
Regexp cref(AnyRet (*f)(Arg)) {return mcref<Arg>(f);}
template<typename Ret, typename Arg1, typename Arg2>
Regexp cren(Ret (*f)(Arg1, Arg2)) {return acren<Ret, Arg1, Arg2>(f);}
template<typename Ret, typename Arg>
Regexp cren(Ret (*f)(Arg)) {return mcren<Ret, Arg>(f);}
template<typename Ret, typename Arg>
Regexp cret(Ret (*f)(Arg)) {return acret<Ret, Arg>(f);}
template<typename Ret>
Regexp cret(Ret (*f)()) {return mcret<Ret>(f);}
template<typename AnyRet, typename Arg1, typename Arg2>
Regexp sref(AnyRet (*f)(Arg1, Arg2)) {return asref<Arg1, Arg2>(f);}
template<typename AnyRet, typename Arg>
Regexp sref(AnyRet (*f)(Arg)) {return msref<Arg>(f);}
template<typename Ret, typename Arg1, typename Arg2>
Regexp sren(Ret (*f)(Arg1, Arg2)) {return asren<Ret, Arg1, Arg2>(f);}
template<typename Ret, typename Arg>
Regexp sren(Ret (*f)(Arg)) {return msren<Ret, Arg>(f);}
template<typename Ret, typename Arg>
Regexp sret(Ret (*f)(Arg)) {return asret<Ret, Arg>(f);}
template<typename Ret>
Regexp sret(Ret (*f)()) {return msret<Ret>(f);}

} // namespace regexp
} // namespace pm

#endif
