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
#include "dataset/syntax/set.hpp"

namespace pm {
namespace dataset {
namespace syntax {

void Set::add(const Function & fun) {
  if(fun.has_target()) {
    add(fun.target());
  }
  if(fun.has_source()) {
    add(fun.source());
  }
  if(fun.has_function_list()) {
    for(const auto & f : fun.function_list()) {
      add(f);
    }
  }
}

void Set::add(Function && fun) {
  if(fun.has_target()) {
    add(std::move(fun.target()));
  }
  if(fun.has_source()) {
    add(std::move(fun.source()));
  }
  if(fun.has_function_list()) {
    for(const auto & f : fun.function_list()) {
      add(std::move(f));
    }
  }
}

} // namespace syntax
} // namespace dataset
} // namespace pm
