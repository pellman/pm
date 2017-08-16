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
#ifndef __DATASET_SYNTAX_INTERPRETER_HPP
#define __DATASET_SYNTAX_INTERPRETER_HPP

#include "dataset/function.hpp"
#include "dataset/set.hpp"
#include "dataset/syntax/function.hpp"
#include "dataset/syntax/set.hpp"

namespace pm {
namespace dataset {
namespace syntax {

dataset::Set interpret(const Set & set);
dataset::Function interpret(const Function & fun, const Set & set);
dataset::Function interpret(Function && fun, const Set & set);

} // namespace syntax
} // namespace dataset
} // namespace pm

#endif
