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
#ifndef __PM_GRAMMAR_SYNTAX_ACTIONS_OPERATORS_HPP
#define __PM_GRAMMAR_SYNTAX_ACTIONS_OPERATORS_HPP

#include "pm/dataset/syntax/function.hpp"
#include "pm/regexp/regexp.hpp"
#include "pm/grammar/syntax/action.hpp"

namespace pm {
namespace grammar {
namespace syntax {

// alternative
Action operator |(const Action & a1, const Action & a2);
Action operator |(const Action & a1, Action && a2);
Action operator |(Action && a1, const Action & a2);
Action operator |(Action && a1, Action && a2);

// rule
Action operator &(const Action & a1, const Action & a2);
Action operator &(const Action & a1, Action && a2);
Action operator &(Action && a1, const Action & a2);
Action operator &(Action && a1, Action && a2);

// star
Action operator *(const Action & a);
Action operator *(Action && a);

// opt
Action operator !(const Action & a);
Action operator !(Action && a);

// fail-function
Action operator -(const Action & a, const dataset::syntax::Function & f_fail);
Action operator -(const Action & a, dataset::syntax::Function && f_fail);
Action operator -(Action && a, const dataset::syntax::Function & f_fail);
Action operator -(Action && a, dataset::syntax::Function && f_fail);

} // namespace syntax
} // namespace grammar

namespace dataset {
namespace syntax {

// function
grammar::syntax::Action operator +(const Function & f);
grammar::syntax::Action operator +(Function && f);

} // namespace syntax
} // namespace dataset

namespace regexp {

// regexp+data
grammar::syntax::Action operator >>(const Regexp & r, const std::string & data_name);
grammar::syntax::Action operator >>(const Regexp & r, std::string && data_name);
grammar::syntax::Action operator >>(Regexp && r, const std::string & data_name);
grammar::syntax::Action operator >>(Regexp && r, std::string && data_name);

} // namespace regexp
} // namespace pm

#endif
