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
#include "pm/grammar/syntax/actions/operators.hpp"

#include "pm/grammar/syntax/actions/base.hpp"

namespace pm {
namespace grammar {
namespace syntax {

// alternative
Action operator |(const Action & a1, const Action & a2) {return alt(a1, a2);}
Action operator |(const Action & a1, Action && a2) {return alt(a1, std::move(a2));}
Action operator |(Action && a1, const Action & a2) {return alt(std::move(a1), a2);}
Action operator |(Action && a1, Action && a2) {return alt(std::move(a1), std::move(a2));}

// rule
Action operator &(const Action & a1, const Action & a2) {return rule(a1, a2);}
Action operator &(const Action & a1, Action && a2) {return rule(a1, std::move(a2));}
Action operator &(Action && a1, const Action & a2) {return rule(std::move(a1), a2);}
Action operator &(Action && a1, Action && a2) {return rule(std::move(a1), std::move(a2));}

// star
Action operator *(const Action & a) {return star(a);}
Action operator *(Action && a) {return star(std::move(a));}

// opt
Action operator !(const Action & a) {return opt(a);}
Action operator !(Action && a) {return opt(std::move(a));}

// fail-function
Action operator -(const Action & a, const dataset::syntax::Function & f_fail) {return ac(a, f_fail);}
Action operator -(const Action & a, dataset::syntax::Function && f_fail) {return ac(a, std::move(f_fail));}
Action operator -(Action && a, const dataset::syntax::Function & f_fail) {return ac(std::move(a), f_fail);}
Action operator -(Action && a, dataset::syntax::Function && f_fail) {return ac(std::move(a), std::move(f_fail));}

} // namespace syntax
} // namespace grammar

namespace dataset {
namespace syntax {

// function
grammar::syntax::Action operator +(const Function & f) {return grammar::syntax::ac(f);}
grammar::syntax::Action operator +(Function && f) {return grammar::syntax::ac(std::move(f));}

} // namespace syntax
} // namespace dataset

namespace regexp {

// regexp+data
grammar::syntax::Action operator >>(const Regexp & r, const std::string & data_name) {return grammar::syntax::ac(r, data_name);}
grammar::syntax::Action operator >>(const Regexp & r, std::string && data_name) {return grammar::syntax::ac(r, std::move(data_name));}
grammar::syntax::Action operator >>(Regexp && r, const std::string & data_name) {return grammar::syntax::ac(std::move(r), data_name);}
grammar::syntax::Action operator >>(Regexp && r, std::string && data_name) {return grammar::syntax::ac(std::move(r), std::move(data_name));}

} // namespace regexp
} // namespace pm
