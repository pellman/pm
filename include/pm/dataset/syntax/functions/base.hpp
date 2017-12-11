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
#ifndef __PM_DATASET_SYNTAX_FUNCTIONS_BASE_HPP
#define __PM_DATASET_SYNTAX_FUNCTIONS_BASE_HPP

#include <array>
#include <list>
#include <string>
#include <utility>
#include "pm/utils/index_sequence.hpp"
#include "pm/dataset/syntax/function.hpp"
#include "pm/dataset/syntax/set.hpp"

namespace pm {
namespace dataset {
namespace syntax {

Function comp(const std::list<Function> & fl);
Function comp(std::list<Function> && fl);
template<typename ... Args>
Function comp(Args && ... args);

Function dfun();
template<typename Fun, typename ... Names>
Function dfun(Fun && f, Names && ... names);

// implementation
template<typename ... Args>
Function comp(Args && ... args) {return comp(std::list<Function>{std::forward<Args>(args) ...});}

template<typename Fun, size_t size>
class DFun : public FunctionInterface {
public:
  template<typename FunArg, typename ... Names>
  DFun(FunArg && f, Names && ... names) : f_(std::forward<FunArg>(f)), names_{std::forward<Names>(names) ...} {}
  dataset::Function interpret(Set & s) const override {return interpret_template(utils::SeqGen<size>(), s);}
private:
  template<size_t ... indexes>
  dataset::Function interpret_template(utils::IndSeq<indexes ...>, Set & s) const {return dataset::dfun(f_, s.add(std::get<indexes>(names_)) ...);}
  Fun f_;
  std::array<std::string, size> names_;
};

template<typename Fun, typename ... Names>
Function dfun(Fun && f, Names && ... names) {return new DFun<Fun, sizeof...(Names)>(std::forward<Fun>(f), std::forward<Names>(names) ...);}

} // namespace syntax
} // namespace dataset
} // namespace pm

#endif
