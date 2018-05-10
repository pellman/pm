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
#include "pm/grammar/syntax/actions/alternative.hpp"

#include "pm/grammar/syntax/actions/redirect.hpp"
#include "pm/grammar/syntax/actions/function.hpp"
#include "pm/grammar/syntax/actions/regexp.hpp"
#include "pm/grammar/actions.hpp"

namespace pm {
namespace grammar {
namespace syntax {

namespace {

// core
class Alternative
  : public ActionInterface {
public:
  // DEFAULTS
  // Alternative() deleted
  // CONSTRUCTORS
  Alternative(const std::list<Action> & actions);
  Alternative(std::list<Action> && actions);
  // PRESERVING METHODS
  grammar::Action interpret(grammar::Grammar & g, InterpretInfo & ii) const override;
private:
  // FIELDS
  std::list<Action> actions_;
};

// core implementation
Alternative::Alternative(const std::list<Action> & actions)
  : actions_(actions) {}

Alternative::Alternative(std::list<Action> && actions)
  : actions_(std::move(actions)) {}

grammar::Action Alternative::interpret(grammar::Grammar & g, InterpretInfo & ii) const {
  std::list<size_t> res_actions;
  for(const auto & a : actions_) {
    res_actions.push_back(a.add_to(g, ii));
  }
  return grammar::alt(std::move(res_actions));
}

} // namespace

// interface
Action alt(const std::list<Action> & actions) {return new Alternative(actions);}
Action alt(std::list<Action> && actions) {return new Alternative(std::move(actions));}
Action operator |(const Action & a1, const Action & a2) {return alt(a1, a2);}
Action operator |(const Action & a1, Action && a2) {return alt(a1, std::move(a2));}
Action operator |(Action && a1, const Action & a2) {return alt(std::move(a1), a2);}
Action operator |(Action && a1, Action && a2) {return alt(std::move(a1), std::move(a2));}
Action operator |(const std::string & name, const Action & a) {return ac(name) | a;}
Action operator |(const std::string & name, Action && a) {return ac(name) | std::move(a);}
Action operator |(std::string && name, const Action & a) {return ac(std::move(name)) | a;}
Action operator |(std::string && name, Action && a) {return ac(std::move(name)) | std::move(a);}
Action operator |(const Action & a, const std::string & name) {return a | ac(name);}
Action operator |(const Action & a, std::string && name) {return a | ac(std::move(name));}
Action operator |(Action && a, const std::string & name) {return std::move(a) | ac(name);}
Action operator |(Action && a, std::string && name) {return std::move(a) | ac(std::move(name));}
Action operator |(const regexp::Regexp & r, const Action & a) {return ac(r) | a;}
Action operator |(const regexp::Regexp & r, Action && a) {return ac(r) | std::move(a);}
Action operator |(regexp::Regexp && r, const Action & a) {return ac(std::move(r)) | a;}
Action operator |(regexp::Regexp && r, Action && a) {return ac(std::move(r)) | std::move(a);}
Action operator |(const Action & a, const regexp::Regexp & r) {return a | ac(r);}
Action operator |(const Action & a, regexp::Regexp && r) {return a | ac(std::move(r));}
Action operator |(Action && a, const regexp::Regexp & r) {return std::move(a) | ac(r);}
Action operator |(Action && a, regexp::Regexp && r) {return std::move(a) | ac(std::move(r));}
Action operator |(const dataset::syntax::Function & f, const Action & a) {return ac(f) | a;}
Action operator |(const dataset::syntax::Function & f, Action && a) {return ac(f) | std::move(a);}
Action operator |(dataset::syntax::Function && f, const Action & a) {return ac(std::move(f)) | a;}
Action operator |(dataset::syntax::Function && f, Action && a) {return ac(std::move(f)) | std::move(a);}
Action operator |(const Action & a, const dataset::syntax::Function & f) {return a | ac(f);}
Action operator |(const Action & a, dataset::syntax::Function && f) {return a | ac(std::move(f));}
Action operator |(Action && a, const dataset::syntax::Function & f) {return std::move(a) | ac(f);}
Action operator |(Action && a, dataset::syntax::Function && f) {return std::move(a) | ac(std::move(f));}

} // namespace syntax
} // namespace grammar
} // namespace pm

namespace pm {
namespace dataset {
namespace syntax {

grammar::syntax::Action operator |(const std::string & name, const Function & f) {return grammar::syntax::ac(name) | grammar::syntax::ac(f);}
grammar::syntax::Action operator |(const std::string & name, Function && f) {return grammar::syntax::ac(name) | grammar::syntax::ac(std::move(f));}
grammar::syntax::Action operator |(std::string && name, const Function & f) {return grammar::syntax::ac(std::move(name)) | grammar::syntax::ac(f);}
grammar::syntax::Action operator |(std::string && name, Function && f) {return grammar::syntax::ac(std::move(name)) | grammar::syntax::ac(std::move(f));}
grammar::syntax::Action operator |(const Function & f, const std::string & name) {return grammar::syntax::ac(f) | grammar::syntax::ac(name);}
grammar::syntax::Action operator |(const Function & f, std::string && name) {return grammar::syntax::ac(f) | grammar::syntax::ac(std::move(name));}
grammar::syntax::Action operator |(Function && f, const std::string & name) {return grammar::syntax::ac(std::move(f)) | grammar::syntax::ac(name);}
grammar::syntax::Action operator |(Function && f, std::string && name) {return grammar::syntax::ac(std::move(f)) | grammar::syntax::ac(std::move(name));}
grammar::syntax::Action operator |(const regexp::Regexp & re, const Function & f) {return grammar::syntax::ac(re) | grammar::syntax::ac(f);}
grammar::syntax::Action operator |(const regexp::Regexp & re, Function && f) {return grammar::syntax::ac(re) | grammar::syntax::ac(std::move(f));}
grammar::syntax::Action operator |(regexp::Regexp && re, const Function & f) {return grammar::syntax::ac(std::move(re)) | grammar::syntax::ac(f);}
grammar::syntax::Action operator |(regexp::Regexp && re, Function && f) {return grammar::syntax::ac(std::move(re)) | grammar::syntax::ac(std::move(f));}
grammar::syntax::Action operator |(const Function & f, const regexp::Regexp & re) {return grammar::syntax::ac(f) | grammar::syntax::ac(re);}
grammar::syntax::Action operator |(const Function & f, regexp::Regexp && re) {return grammar::syntax::ac(f) | grammar::syntax::ac(std::move(re));}
grammar::syntax::Action operator |(Function && f, const regexp::Regexp & re) {return grammar::syntax::ac(std::move(f)) | grammar::syntax::ac(re);}
grammar::syntax::Action operator |(Function && f, regexp::Regexp && re) {return grammar::syntax::ac(std::move(f)) | grammar::syntax::ac(std::move(re));}

} // namespace syntax
} // namespace dataset
} // namespace pm
