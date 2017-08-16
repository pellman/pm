/*
    This file is part of the pm library package.
    Copyright (C) 2017 Vladislav Podymov
    
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
#include "dataset/syntax/interpreter.hpp"

#include <utility>
#include "dataset/functions.hpp"

namespace pm {
namespace dataset {
namespace syntax {

dataset::Set interpret(const Set & set) {return set.size();}

dataset::Function interpret(const Function & fun, const Set & set) {
  switch(fun.type()) {
  case Function::APPLIER:
    return dataset::applier(
             set.index_of(fun.target()),
             set.index_of(fun.source()),
             fun.applier()
           );
  case Function::CLONER:
    return dataset::cloner(
             set.index_of(fun.target()),
             set.index_of(fun.source())
           );
  case Function::COMPOSITION: {
    std::list<dataset::Function> funclist;
    for(const auto & f : fun.function_list()) {
      funclist.push_back(interpret(f, set));
    }
    return dataset::composition(std::move(funclist));
  }
  case Function::CREATOR:
    return dataset::creator(
             set.index_of(fun.target()),
             fun.creator()
           );
  case Function::FLUSHER:
    return dataset::flusher(
             set.index_of(fun.target()),
             fun.data()
           );
  case Function::MODIFIER:
    return dataset::modifier(
             set.index_of(fun.target()),
             fun.modifier()
           );
  default:
    return f_trivial;
  }
}

dataset::Function interpret(Function && fun, const Set & set) {
  switch(fun.type()) {
  case Function::APPLIER:
    return dataset::applier(
             set.index_of(fun.target()),
             set.index_of(fun.source()),
             std::move(fun.applier())
           );
  case Function::CLONER:
    return dataset::cloner(
             set.index_of(fun.target()),
             set.index_of(fun.source())
           );
  case Function::COMPOSITION: {
    std::list<dataset::Function> funclist;
    for(const auto & f : fun.function_list()) {
      funclist.push_back(interpret(std::move(f), set));
    }
    return dataset::composition(std::move(funclist));
  }
  case Function::CREATOR:
    return dataset::creator(
             set.index_of(fun.target()),
             std::move(fun.creator())
           );
  case Function::FLUSHER:
    return dataset::flusher(
             set.index_of(fun.target()),
             std::move(fun.data())
           );
  case Function::MODIFIER:
    return dataset::modifier(
             set.index_of(fun.target()),
             std::move(fun.modifier())
           );
  case Function::TRIVIAL:
  default:
    return f_trivial;
  }
}

} // namespace syntax
} // namespace dataset
} // namespace pm
