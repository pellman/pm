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
#ifndef __PM_TYPE_ABUSE_MUTATORS_HPP
#define __PM_TYPE_ABUSE_MUTATORS_HPP

#include <cstddef>
#include <array>
#include <functional>
#include <type_traits>
#include <utility>
#include "pm/utils/index_sequence.hpp"
#include "pm/type_abuse/dptr.hpp"

namespace pm {
namespace type_abuse {

// TODO:
//   Much more elegant way to mutate function signatures is to use lambdas.
//   When this code was written, "must be" c++ standard was 11.
//   C++11 has no lambda captures with initialization (e.g. "[f = std::forward<Fun>(f)](...){...}").
//   It means that lambda usage may lead to excess copying.
//   Until c++14 becomes "must be", the redundancy is avoided with usage of functors.

template<size_t size, typename ... DPtrs>
class MutatorPart {
public:
  template<typename ... ArgDPtrs>
  MutatorPart(const std::function<void(DPtrs ...)> & f, ArgDPtrs && ... ptrs) : f_(f), ptrs_{std::forward<ArgDPtrs>(ptrs) ...} {}
  template<typename ... ArgDPtrs>
  MutatorPart(std::function<void(DPtrs ...)> && f, ArgDPtrs && ... ptrs) : f_(std::move(f)), ptrs_{std::forward<ArgDPtrs>(ptrs) ...} {}
  template<typename ... ArgDPtrs>
  void operator()(const ArgDPtrs & ... ptrs) const {call_template(utils::SeqGen<size>(), ptrs ...);}
private:
  template<size_t ... indexes, typename ... ArgDPtrs>
  void call_template(utils::IndSeq<indexes ...>, const ArgDPtrs & ... ptrs) const {f_(ptrs ..., std::get<indexes>(ptrs_) ...);}
  std::function<void(const DPtrs & ...)> f_;
  std::array<DPtr, size> ptrs_;
};

template<typename ... Args>
class MutatorRef {
public:
  template<typename ... DPtrs>
  void operator()(const DPtrs & ... ptrs) const {f(val<typename std::decay<Args>::type>(ptrs) ...);}
  std::function<void(Args ...)> f;
};

template<typename Ret, typename Arg, typename ... Args>
class MutatorRen {
public:
  template<typename ... DPtrs>
  void operator()(const DPtr & ptr_ret, const DPtrs & ... ptrs) const {ptr_ret.set<typename std::decay<Ret>::type>(f(ptr_ret.val<typename std::decay<Arg>::type>(), val<typename std::decay<Args>::type>(ptrs) ...));}
  std::function<Ret(Arg, Args ...)> f;
};

template<typename Ret, typename ... Args>
class MutatorRet {
public:
  template<typename ... DPtrs>
  void operator()(const DPtr & ptr_ret, const DPtrs & ... ptrs) const {ptr_ret.set<typename std::decay<Ret>::type>(f(val<typename std::decay<Args>::type>(ptrs) ...));}
  std::function<Ret(Args ...)> f;
};


template<typename ... DPtrs, typename ... ArgDPtrs>
MutatorPart<sizeof...(ArgDPtrs), DPtrs ...> mutator_part(const std::function<void(const DPtrs & ...)> & f, ArgDPtrs && ... ptrs) {return {f, std::forward<ArgDPtrs>(ptrs) ...};}
template<typename ... DPtrs, typename ... ArgDPtrs>
MutatorPart<sizeof...(ArgDPtrs), DPtrs ...> mutator_part(std::function<void(const DPtrs & ...)> && f, ArgDPtrs && ... ptrs) {return {std::move(f), std::forward<ArgDPtrs>(ptrs) ...};}

template<typename ... Args>
MutatorRef<Args ...> mutator_ref(const std::function<void(Args ...)> & f) {return {f};}
template<typename ... Args>
MutatorRef<Args ...> mutator_ref(std::function<void(Args ...)> && f) {return {std::move(f)};}

template<typename Ret, typename Arg, typename ... Args>
MutatorRen<Ret, Arg, Args ...> mutator_ren(const std::function<Ret(Arg, Args ...)> & f) {return {f};}
template<typename Ret, typename Arg, typename ... Args>
MutatorRen<Ret, Arg, Args ...> mutator_ren(std::function<Ret(Arg, Args ...)> && f) {return {std::move(f)};}

template<typename Ret, typename ... Args>
MutatorRet<Ret, Args ...> mutator_ret(const std::function<Ret(Args ...)> & f) {return {f};}
template<typename Ret, typename ... Args>
MutatorRet<Ret, Args ...> mutator_ret(std::function<Ret(Args ...)> && f) {return {std::move(f)};}

} // namespace type_abuse
} // namespace pm

#endif
