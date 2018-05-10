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
#ifndef __PM_GRAMMAR_SYNTAX_ACTIONS_FUNCTION_HPP
#define __PM_GRAMMAR_SYNTAX_ACTIONS_FUNCTION_HPP

#include "pm/dataset/syntax/function.hpp"
#include "pm/grammar/syntax/action.hpp"

namespace pm {
namespace grammar {
namespace syntax {

Action ac(const dataset::syntax::Function & f);
Action ac(dataset::syntax::Function && f);

} // namespace syntax
} // namespace grammar
} // namespace pm

namespace pm {
namespace dataset {
namespace syntax {

grammar::syntax::Action operator +(const Function & f);
grammar::syntax::Action operator +(Function && f);

} // namespace syntax
} // namespace dataset
} // namespace pm

#endif
