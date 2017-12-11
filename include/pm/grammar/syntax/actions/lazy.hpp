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
#ifndef __PM_GRAMMAR_SYNTAX_ACTIONS_LAZY_HPP
#define __PM_GRAMMAR_SYNTAX_ACTIONS_LAZY_HPP

#include <string>
#include "pm/dataset/syntax/function.hpp"
#include "pm/regexp/regexp.hpp"
#include "pm/grammar/syntax/action.hpp"

namespace pm {
namespace grammar {
namespace syntax {

// string -> ac(string)
Action operator |(const std::string & name, const Action & a);
Action operator |(const std::string & name, Action && a);
Action operator |(std::string && name, const Action & a);
Action operator |(std::string && name, Action && a);
Action operator |(const Action & a, const std::string & name);
Action operator |(const Action & a, std::string && name);
Action operator |(Action && a, const std::string & name);
Action operator |(Action && a, std::string && name);
Action operator &(const std::string & name, const Action & a);
Action operator &(const std::string & name, Action && a);
Action operator &(std::string && name, const Action & a);
Action operator &(std::string && name, Action && a);
Action operator &(const Action & a, const std::string & name);
Action operator &(const Action & a, std::string && name);
Action operator &(Action && a, const std::string & name);
Action operator &(Action && a, std::string && name);

// regexp -> ac(regexp)
Action operator |(const regexp::Regexp & r, const Action & a);
Action operator |(const regexp::Regexp & r, Action && a);
Action operator |(regexp::Regexp && r, const Action & a);
Action operator |(regexp::Regexp && r, Action && a);
Action operator |(const Action & a, const regexp::Regexp & r);
Action operator |(const Action & a, regexp::Regexp && r);
Action operator |(Action && a, const regexp::Regexp & r);
Action operator |(Action && a, regexp::Regexp && r);
Action operator &(const regexp::Regexp & r, const Action & a);
Action operator &(const regexp::Regexp & r, Action && a);
Action operator &(regexp::Regexp && r, const Action & a);
Action operator &(regexp::Regexp && r, Action && a);
Action operator &(const Action & a, const regexp::Regexp & r);
Action operator &(const Action & a, regexp::Regexp && r);
Action operator &(Action && a, const regexp::Regexp & r);
Action operator &(Action && a, regexp::Regexp && r);

// dataset function -> ac(function)
Action operator |(const dataset::syntax::Function & f, const Action & a);
Action operator |(const dataset::syntax::Function & f, Action && a);
Action operator |(dataset::syntax::Function && f, const Action & a);
Action operator |(dataset::syntax::Function && f, Action && a);
Action operator |(const Action & a, const dataset::syntax::Function & f);
Action operator |(const Action & a, dataset::syntax::Function && f);
Action operator |(Action && a, const dataset::syntax::Function & f);
Action operator |(Action && a, dataset::syntax::Function && f);
Action operator &(const dataset::syntax::Function & f, const Action & a);
Action operator &(const dataset::syntax::Function & f, Action && a);
Action operator &(dataset::syntax::Function && f, const Action & a);
Action operator &(dataset::syntax::Function && f, Action && a);
Action operator &(const Action & a, const dataset::syntax::Function & f);
Action operator &(const Action & a, dataset::syntax::Function && f);
Action operator &(Action && a, const dataset::syntax::Function & f);
Action operator &(Action && a, dataset::syntax::Function && f);

} // namespace syntax
} // namespace grammar

namespace dataset {
namespace syntax {

// string -> ac(string), dataset function -> ac(function)
grammar::syntax::Action operator |(const std::string & name, const Function & f);
grammar::syntax::Action operator |(const std::string & name, Function && f);
grammar::syntax::Action operator |(std::string && name, const Function & f);
grammar::syntax::Action operator |(std::string && name, Function && f);
grammar::syntax::Action operator |(const Function & f, const std::string & name);
grammar::syntax::Action operator |(const Function & f, std::string && name);
grammar::syntax::Action operator |(Function && f, const std::string & name);
grammar::syntax::Action operator |(Function && f, std::string && name);
grammar::syntax::Action operator &(const std::string & name, const Function & f);
grammar::syntax::Action operator &(const std::string & name, Function && f);
grammar::syntax::Action operator &(std::string && name, const Function & f);
grammar::syntax::Action operator &(std::string && name, Function && f);
grammar::syntax::Action operator &(const Function & f, const std::string & name);
grammar::syntax::Action operator &(const Function & f, std::string && name);
grammar::syntax::Action operator &(Function && f, const std::string & name);
grammar::syntax::Action operator &(Function && f, std::string && name);

// regexp -> ac(regexp), dataset function -> ac(function)
grammar::syntax::Action operator |(const regexp::Regexp & re, const Function & f);
grammar::syntax::Action operator |(const regexp::Regexp & re, Function && f);
grammar::syntax::Action operator |(regexp::Regexp && re, const Function & f);
grammar::syntax::Action operator |(regexp::Regexp && re, Function && f);
grammar::syntax::Action operator |(const Function & f, const regexp::Regexp & re);
grammar::syntax::Action operator |(const Function & f, regexp::Regexp && re);
grammar::syntax::Action operator |(Function && f, const regexp::Regexp & re);
grammar::syntax::Action operator |(Function && f, regexp::Regexp && re);
grammar::syntax::Action operator &(const regexp::Regexp & re, const Function & f);
grammar::syntax::Action operator &(const regexp::Regexp & re, Function && f);
grammar::syntax::Action operator &(regexp::Regexp && re, const Function & f);
grammar::syntax::Action operator &(regexp::Regexp && re, Function && f);
grammar::syntax::Action operator &(const Function & f, const regexp::Regexp & re);
grammar::syntax::Action operator &(const Function & f, regexp::Regexp && re);
grammar::syntax::Action operator &(Function && f, const regexp::Regexp & re);
grammar::syntax::Action operator &(Function && f, regexp::Regexp && re);

// fail function
grammar::syntax::Action operator -(const std::string & name, const Function & f_fail);
grammar::syntax::Action operator -(const std::string & name, Function && f_fail);
grammar::syntax::Action operator -(std::string && name, const Function & f_fail);
grammar::syntax::Action operator -(std::string && name, Function && f_fail);
grammar::syntax::Action operator -(const regexp::Regexp & r, const Function & f_fail);
grammar::syntax::Action operator -(const regexp::Regexp & r, Function && f_fail);
grammar::syntax::Action operator -(regexp::Regexp && r, const Function & f_fail);
grammar::syntax::Action operator -(regexp::Regexp && r, Function && f_fail);

} // namespace syntax
} // namespace dataset
} // namespace pm

#endif
