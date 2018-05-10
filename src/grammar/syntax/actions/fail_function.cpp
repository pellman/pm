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
#include "pm/grammar/syntax/actions/fail_function.hpp"

#include "pm/grammar/actions.hpp"
#include "pm/grammar/syntax/actions/redirect.hpp"
#include "pm/grammar/syntax/actions/regexp.hpp"
#include "pm/grammar/syntax/interpret_info.hpp"

namespace pm {
namespace grammar {
namespace syntax {

namespace {

// core
class FailFunction
  : public ActionInterface {
public:
  // DEFAULTS
  // Function() deleted
  // CONSTRUCTORS
  FailFunction(const Action & a, const dataset::syntax::Function & f);
  FailFunction(const Action & a, dataset::syntax::Function && f);
  FailFunction(Action && a, const dataset::syntax::Function & f);
  FailFunction(Action && a, dataset::syntax::Function && f);
  // PRESERVING METHODS
  grammar::Action interpret(grammar::Grammar & g, InterpretInfo & ii) const override;
private:
  // FIELDS
  Action a_;
  dataset::syntax::Function f_;
};

// core implementation
FailFunction::FailFunction(const Action & a, const dataset::syntax::Function & f)
  : a_(a),
    f_(f) {}

FailFunction::FailFunction(const Action & a, dataset::syntax::Function && f)
  : a_(a),
    f_(std::move(f)) {}

FailFunction::FailFunction(Action && a, const dataset::syntax::Function & f)
  : a_(std::move(a)),
    f_(f) {}

FailFunction::FailFunction(Action && a, dataset::syntax::Function && f)
  : a_(std::move(a)),
    f_(std::move(f)) {}

grammar::Action FailFunction::interpret(grammar::Grammar & g, InterpretInfo & ii) const {
  return grammar::ac(a_.add_to(g, ii), f_.interpret(ii.data));
}

} // namespace

// interface
Action ac(const Action & a, const dataset::syntax::Function & f) {return new FailFunction(a, f);}
Action ac(const Action & a, dataset::syntax::Function && f) {return new FailFunction(a, std::move(f));}
Action ac(Action && a, const dataset::syntax::Function & f) {return new FailFunction(std::move(a), f);}
Action ac(Action && a, dataset::syntax::Function && f) {return new FailFunction(std::move(a), std::move(f));}
Action operator -(const Action & a, const dataset::syntax::Function & f) {return ac(a, f);}
Action operator -(const Action & a, dataset::syntax::Function && f) {return ac(a, std::move(f));}
Action operator -(Action && a, const dataset::syntax::Function & f) {return ac(std::move(a), f);}
Action operator -(Action && a, dataset::syntax::Function && f) {return ac(std::move(a), std::move(f));}

} // namespace syntax
} // namespace grammar
} // namespace pm

namespace pm {
namespace dataset {
namespace syntax {

grammar::syntax::Action operator -(const std::string & a, const Function & f) {return grammar::syntax::ac(a) - f;}
grammar::syntax::Action operator -(const std::string & a, Function && f) {return grammar::syntax::ac(a) - std::move(f);}
grammar::syntax::Action operator -(std::string && a, const Function & f) {return grammar::syntax::ac(std::move(a)) - f;}
grammar::syntax::Action operator -(std::string && a, Function && f) {return grammar::syntax::ac(std::move(a)) - std::move(f);}
grammar::syntax::Action operator -(const regexp::Regexp & a, const Function & f) {return grammar::syntax::ac(a) - f;}
grammar::syntax::Action operator -(const regexp::Regexp & a, Function && f) {return grammar::syntax::ac(a) - std::move(f);}
grammar::syntax::Action operator -(regexp::Regexp && a, const Function & f) {return grammar::syntax::ac(std::move(a)) - f;}
grammar::syntax::Action operator -(regexp::Regexp && a, Function && f) {return grammar::syntax::ac(std::move(a)) - std::move(f);}

} // namespace syntax
} // namespace dataset
} // namespace pm
