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
#include "pm/grammar/syntax/actions/lazy.hpp"

#include "pm/grammar/syntax/actions/base.hpp"
#include "pm/grammar/syntax/actions/operators.hpp"

namespace pm {
namespace grammar {
namespace syntax {

// string -> name(string)
Action operator |(const std::string & name, const Action & a) {return ac(name) | a;}
Action operator |(const std::string & name, Action && a) {return ac(name) | std::move(a);}
Action operator |(std::string && name, const Action & a) {return ac(std::move(name)) | a;}
Action operator |(std::string && name, Action && a) {return ac(std::move(name)) | std::move(a);}
Action operator |(const Action & a, const std::string & name) {return a | ac(name);}
Action operator |(const Action & a, std::string && name) {return a | ac(std::move(name));}
Action operator |(Action && a, const std::string & name) {return std::move(a) | ac(name);}
Action operator |(Action && a, std::string && name) {return std::move(a) | ac(std::move(name));}
Action operator &(const std::string & name, const Action & a) {return ac(name) & a;}
Action operator &(const std::string & name, Action && a) {return ac(name) & std::move(a);}
Action operator &(std::string && name, const Action & a) {return ac(std::move(name)) & a;}
Action operator &(std::string && name, Action && a) {return ac(std::move(name)) & std::move(a);}
Action operator &(const Action & a, const std::string & name) {return a & ac(name);}
Action operator &(const Action & a, std::string && name) {return a & ac(std::move(name));}
Action operator &(Action && a, const std::string & name) {return std::move(a) & ac(name);}
Action operator &(Action && a, std::string && name) {return std::move(a) & ac(std::move(name));}

// regexp -> re(regexp)
Action operator |(const regexp::Regexp & r, const Action & a) {return ac(r) | a;}
Action operator |(const regexp::Regexp & r, Action && a) {return ac(r) | std::move(a);}
Action operator |(regexp::Regexp && r, const Action & a) {return ac(std::move(r)) | a;}
Action operator |(regexp::Regexp && r, Action && a) {return ac(std::move(r)) | std::move(a);}
Action operator |(const Action & a, const regexp::Regexp & r) {return a | ac(r);}
Action operator |(const Action & a, regexp::Regexp && r) {return a | ac(std::move(r));}
Action operator |(Action && a, const regexp::Regexp & r) {return std::move(a) | ac(r);}
Action operator |(Action && a, regexp::Regexp && r) {return std::move(a) | ac(std::move(r));}
Action operator &(const regexp::Regexp & r, const Action & a) {return ac(r) & a;}
Action operator &(const regexp::Regexp & r, Action && a) {return ac(r) & std::move(a);}
Action operator &(regexp::Regexp && r, const Action & a) {return ac(std::move(r)) & a;}
Action operator &(regexp::Regexp && r, Action && a) {return ac(std::move(r)) & std::move(a);}
Action operator &(const Action & a, const regexp::Regexp & r) {return a & ac(r);}
Action operator &(const Action & a, regexp::Regexp && r) {return a & ac(std::move(r));}
Action operator &(Action && a, const regexp::Regexp & r) {return std::move(a) & ac(r);}
Action operator &(Action && a, regexp::Regexp && r) {return std::move(a) & ac(std::move(r));}

// dataset function -> action - function
Action operator |(const dataset::syntax::Function & f, const Action & a) {return ac(f) | a;}
Action operator |(const dataset::syntax::Function & f, Action && a) {return ac(f) | std::move(a);}
Action operator |(dataset::syntax::Function && f, const Action & a) {return ac(std::move(f)) | a;}
Action operator |(dataset::syntax::Function && f, Action && a) {return ac(std::move(f)) | std::move(a);}
Action operator |(const Action & a, const dataset::syntax::Function & f) {return a | ac(f);}
Action operator |(const Action & a, dataset::syntax::Function && f) {return a | ac(std::move(f));}
Action operator |(Action && a, const dataset::syntax::Function & f) {return std::move(a) | ac(f);}
Action operator |(Action && a, dataset::syntax::Function && f) {return std::move(a) | ac(std::move(f));}
Action operator &(const dataset::syntax::Function & f, const Action & a) {return ac(f) & a;}
Action operator &(const dataset::syntax::Function & f, Action && a) {return ac(f) & std::move(a);}
Action operator &(dataset::syntax::Function && f, const Action & a) {return ac(std::move(f)) & a;}
Action operator &(dataset::syntax::Function && f, Action && a) {return ac(std::move(f)) & std::move(a);}
Action operator &(const Action & a, const dataset::syntax::Function & f) {return a & ac(f);}
Action operator &(const Action & a, dataset::syntax::Function && f) {return a & ac(std::move(f));}
Action operator &(Action && a, const dataset::syntax::Function & f) {return std::move(a) & ac(f);}
Action operator &(Action && a, dataset::syntax::Function && f) {return std::move(a) & ac(std::move(f));}

} // namespace syntax
} // namespace grammar

namespace dataset {
namespace syntax {

// string -> ac(string), dataset function -> ac(function)
grammar::syntax::Action operator |(const std::string & name, const Function & f) {return grammar::syntax::ac(name) | grammar::syntax::ac(f);}
grammar::syntax::Action operator |(const std::string & name, Function && f) {return grammar::syntax::ac(name) | grammar::syntax::ac(std::move(f));}
grammar::syntax::Action operator |(std::string && name, const Function & f) {return grammar::syntax::ac(std::move(name)) | grammar::syntax::ac(f);}
grammar::syntax::Action operator |(std::string && name, Function && f) {return grammar::syntax::ac(std::move(name)) | grammar::syntax::ac(std::move(f));}
grammar::syntax::Action operator |(const Function & f, const std::string & name) {return grammar::syntax::ac(f) | grammar::syntax::ac(name);}
grammar::syntax::Action operator |(const Function & f, std::string && name) {return grammar::syntax::ac(f) | grammar::syntax::ac(std::move(name));}
grammar::syntax::Action operator |(Function && f, const std::string & name) {return grammar::syntax::ac(std::move(f)) | grammar::syntax::ac(name);}
grammar::syntax::Action operator |(Function && f, std::string && name) {return grammar::syntax::ac(std::move(f)) | grammar::syntax::ac(std::move(name));}
grammar::syntax::Action operator &(const std::string & name, const Function & f) {return grammar::syntax::ac(name) & grammar::syntax::ac(f);}
grammar::syntax::Action operator &(const std::string & name, Function && f) {return grammar::syntax::ac(name) & grammar::syntax::ac(std::move(f));}
grammar::syntax::Action operator &(std::string && name, const Function & f) {return grammar::syntax::ac(std::move(name)) & grammar::syntax::ac(f);}
grammar::syntax::Action operator &(std::string && name, Function && f) {return grammar::syntax::ac(std::move(name)) & grammar::syntax::ac(std::move(f));}
grammar::syntax::Action operator &(const Function & f, const std::string & name) {return grammar::syntax::ac(f) & grammar::syntax::ac(name);}
grammar::syntax::Action operator &(const Function & f, std::string && name) {return grammar::syntax::ac(f) & grammar::syntax::ac(std::move(name));}
grammar::syntax::Action operator &(Function && f, const std::string & name) {return grammar::syntax::ac(std::move(f)) & grammar::syntax::ac(name);}
grammar::syntax::Action operator &(Function && f, std::string && name) {return grammar::syntax::ac(std::move(f)) & grammar::syntax::ac(std::move(name));}

// regexp -> grammar::syntax::ac(regexp), dataset function -> grammar::syntax::ac(function)
grammar::syntax::Action operator |(const regexp::Regexp & re, const Function & f) {return grammar::syntax::ac(re) | grammar::syntax::ac(f);}
grammar::syntax::Action operator |(const regexp::Regexp & re, Function && f) {return grammar::syntax::ac(re) | grammar::syntax::ac(std::move(f));}
grammar::syntax::Action operator |(regexp::Regexp && re, const Function & f) {return grammar::syntax::ac(std::move(re)) | grammar::syntax::ac(f);}
grammar::syntax::Action operator |(regexp::Regexp && re, Function && f) {return grammar::syntax::ac(std::move(re)) | grammar::syntax::ac(std::move(f));}
grammar::syntax::Action operator |(const Function & f, const regexp::Regexp & re) {return grammar::syntax::ac(f) | grammar::syntax::ac(re);}
grammar::syntax::Action operator |(const Function & f, regexp::Regexp && re) {return grammar::syntax::ac(f) | grammar::syntax::ac(std::move(re));}
grammar::syntax::Action operator |(Function && f, const regexp::Regexp & re) {return grammar::syntax::ac(std::move(f)) | grammar::syntax::ac(re);}
grammar::syntax::Action operator |(Function && f, regexp::Regexp && re) {return grammar::syntax::ac(std::move(f)) | grammar::syntax::ac(std::move(re));}
grammar::syntax::Action operator &(const regexp::Regexp & re, const Function & f) {return grammar::syntax::ac(re) & grammar::syntax::ac(f);}
grammar::syntax::Action operator &(const regexp::Regexp & re, Function && f) {return grammar::syntax::ac(re) & grammar::syntax::ac(std::move(f));}
grammar::syntax::Action operator &(regexp::Regexp && re, const Function & f) {return grammar::syntax::ac(std::move(re)) & grammar::syntax::ac(f);}
grammar::syntax::Action operator &(regexp::Regexp && re, Function && f) {return grammar::syntax::ac(std::move(re)) & grammar::syntax::ac(std::move(f));}
grammar::syntax::Action operator &(const Function & f, const regexp::Regexp & re) {return grammar::syntax::ac(f) & grammar::syntax::ac(re);}
grammar::syntax::Action operator &(const Function & f, regexp::Regexp && re) {return grammar::syntax::ac(f) & grammar::syntax::ac(std::move(re));}
grammar::syntax::Action operator &(Function && f, const regexp::Regexp & re) {return grammar::syntax::ac(std::move(f)) & grammar::syntax::ac(re);}
grammar::syntax::Action operator &(Function && f, regexp::Regexp && re) {return grammar::syntax::ac(std::move(f)) & grammar::syntax::ac(std::move(re));}

// fail function
grammar::syntax::Action operator -(const std::string & name, const Function & f_fail) {return grammar::syntax::ac(grammar::syntax::ac(name), f_fail);}
grammar::syntax::Action operator -(const std::string & name, Function && f_fail) {return grammar::syntax::ac(grammar::syntax::ac(name), std::move(f_fail));}
grammar::syntax::Action operator -(std::string && name, const Function & f_fail) {return grammar::syntax::ac(grammar::syntax::ac(std::move(name)), f_fail);}
grammar::syntax::Action operator -(std::string && name, Function && f_fail) {return grammar::syntax::ac(grammar::syntax::ac(std::move(name)), std::move(f_fail));}
grammar::syntax::Action operator -(const regexp::Regexp & r, const Function & f_fail) {return grammar::syntax::ac(grammar::syntax::ac(r), f_fail);}
grammar::syntax::Action operator -(const regexp::Regexp & r, Function && f_fail) {return grammar::syntax::ac(grammar::syntax::ac(r), std::move(f_fail));}
grammar::syntax::Action operator -(regexp::Regexp && r, const Function & f_fail) {return grammar::syntax::ac(grammar::syntax::ac(std::move(r)), f_fail);}
grammar::syntax::Action operator -(regexp::Regexp && r, Function && f_fail) {return grammar::syntax::ac(grammar::syntax::ac(std::move(r)), std::move(f_fail));}

} // namespace syntax
} // namespace dataset

} // namespace pm
