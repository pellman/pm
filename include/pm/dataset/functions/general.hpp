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
#ifndef __PM_DATASET_FUNCTIONS_GENERAL_HPP
#define __PM_DATASET_FUNCTIONS_GENERAL_HPP

#include <cstddef>
#include <array>
#include <functional>
#include <utility>
#include "pm/type_abuse/mutators.hpp"
#include "pm/utils/index_sequence.hpp"
#include "pm/dataset/function.hpp"
#include "pm/dataset/set.hpp"

namespace pm {
namespace dataset {

template<typename Fun, size_t size>
class DFun : public FunctionInterface {
public:
  template<typename FunArg, typename ... Targets>
  DFun(FunArg && f, Targets ... targets) : f_(std::forward<FunArg>(f)), targets_{targets ...} {}
  void apply(const Set & ds) const override {apply_template(utils::SeqGen<size>(), ds);}
private:
  template<size_t ... indexes>
  void apply_template(utils::IndSeq<indexes ...>, const Set & ds) const {f_(ds.ptr(std::get<indexes>(targets_)) ...);}
  Fun f_;
  std::array<size_t, size> targets_;
};

Function dfun();
template<typename Fun, typename ... Targets>
Function dfun(Fun && f, Targets ... targets) {return new DFun<Fun, sizeof...(Targets)>(std::forward<Fun>(f), targets ...);}

template<typename ... Args, typename ... Targets>
Function dref(const std::function<void(Args ...)> & f, Targets ... targets) {return dfun(type_abuse::mutator_ref(f), targets ...);}
template<typename ... Args, typename ... Targets>
Function dref(std::function<void(Args ...)> && f, Targets ... targets) {return dfun(type_abuse::mutator_ref(std::move(f)), targets ...);}
template<typename Any, typename ... Args, typename ... Targets>
Function dgref(Any (*f)(Args ...), Targets ... targets) {return dref(std::function<void(Args ...)>(f), targets ...);}

template<typename Ret, typename ... Args, typename ... Targets>
Function dren(const std::function<Ret(Args ...)> & f, Targets ... targets) {return dfun(type_abuse::mutator_ren(f), targets ...);}
template<typename Ret, typename ... Args, typename ... Targets>
Function dren(std::function<Ret(Args ...)> && f, Targets ... targets) {return dfun(type_abuse::mutator_ren(std::move(f)), targets ...);}
template<typename Ret, typename ... Args, typename ... Targets>
Function dgren(Ret (*f)(Args ...), Targets ... targets) {return dren(std::function<Ret(Args ...)>(f), targets ...);}

template<typename Ret, typename ... Args, typename ... Targets>
Function dret(const std::function<Ret(Args ...)> & f, Targets ... targets) {return dfun(type_abuse::mutator_ret(f), targets ...);}
template<typename Ret, typename ... Args, typename ... Targets>
Function dret(std::function<Ret(Args ...)> && f, Targets ... targets) {return dfun(type_abuse::mutator_ret(std::move(f)), targets ...);}
template<typename Ret, typename ... Args, typename ... Targets>
Function dgret(Ret (*f)(Args ...), Targets ... targets) {return dret(std::function<Ret(Args ...)>(f), targets ...);}

} // namespace dataset
} // namespace pm

#endif
