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
#ifndef __PM_DATASET_SYNTAX_FUNCTIONS_GENERAL_HPP
#define __PM_DATASET_SYNTAX_FUNCTIONS_GENERAL_HPP

#include <cstddef>
#include <array>
#include <string>
#include <utility>
#include "pm/type_abuse/mutators.hpp"
#include "pm/utils/index_sequence.hpp"
#include "pm/dataset/syntax/function.hpp"
#include "pm/dataset/syntax/set.hpp"

namespace pm {
namespace dataset {
namespace syntax {

template<typename Fun, size_t size>
class DFun : public FunctionInterface {
public:
  template<typename FunArg, typename ... Names>
  DFun(FunArg && f, Names && ... names) : f_(std::forward<FunArg>(f)), names_{std::forward<Names>(names) ...} {}
  dataset::Function interpret(Set & s) const override {return interpret_template(utils::SeqGen<size>(), s);}
private:
  template<size_t ... indexes>
  dataset::Function interpret_template(utils::IndSeq<indexes ...>, Set & s) const {return dataset::dfun(f_, s.insert(std::get<indexes>(names_)) ...);}
  Fun f_;
  std::array<std::string, size> names_;
};

Function dfun();
template<typename Fun, typename ... Names>
Function dfun(Fun && f, Names && ... names) {return new DFun<Fun, sizeof...(Names)>(std::forward<Fun>(f), std::forward<Names>(names) ...);}

template<typename ... Args, typename ... Names>
Function dref(const std::function<void(Args ...)> & f, Names && ... names) {return dfun(type_abuse::mutator_ref(f), std::forward<Names>(names) ...);}
template<typename ... Args, typename ... Names>
Function dref(std::function<void(Args ...)> && f, Names && ... names) {return dfun(type_abuse::mutator_ref(std::move(f)), std::forward<Names>(names) ...);}
template<typename Any, typename ... Args, typename ... Names>
Function dgref(Any (*f)(Args ...), Names && ... names) {return dref(std::function<void(Args ...)>(f), std::forward<Names>(names) ...);}

template<typename Ret, typename ... Args, typename ... Names>
Function dren(const std::function<Ret(Args ...)> & f, Names && ... names) {return dfun(type_abuse::mutator_ren(f), std::forward<Names>(names) ...);}
template<typename Ret, typename ... Args, typename ... Names>
Function dren(std::function<Ret(Args ...)> && f, Names && ... names) {return dfun(type_abuse::mutator_ren(std::move(f)), std::forward<Names>(names) ...);}
template<typename Ret, typename ... Args, typename ... Names>
Function dgren(Ret (*f)(Args ...), Names && ... names) {return dren(std::function<Ret(Args ...)>(f), std::forward<Names>(names) ...);}

template<typename Ret, typename ... Args, typename ... Names>
Function dret(const std::function<Ret(Args ...)> & f, Names && ... names) {return dfun(type_abuse::mutator_ret(f), std::forward<Names>(names) ...);}
template<typename Ret, typename ... Args, typename ... Names>
Function dret(std::function<Ret(Args ...)> && f, Names && ... names) {return dfun(type_abuse::mutator_ret(std::move(f)), std::forward<Names>(names) ...);}
template<typename Ret, typename ... Args, typename ... Names>
Function dgret(Ret (*f)(Args ...), Names && ... names) {return dret(std::function<Ret(Args ...)>(f), std::forward<Names>(names) ...);}

} // namespace syntax
} // namespace dataset
} // namespace pm

#endif
