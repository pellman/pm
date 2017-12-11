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
#include "pm/grammar/syntax/actions/base.hpp"

#include "pm/grammar/actions.hpp"
#include "pm/grammar/syntax/interpret_info.hpp"

namespace pm {
namespace grammar {
namespace syntax {

namespace {

// core
class IfFail
  : public ActionInterface {
public:
  // DEFAULTS
  // IfFail() deleted
  // CONSTRUCTORS
  IfFail(const Action & a, const dataset::syntax::Function & f);
  IfFail(const Action & a, dataset::syntax::Function && f);
  IfFail(Action && a, const dataset::syntax::Function & f);
  IfFail(Action && a, dataset::syntax::Function && f);
  // PRESERVING METHODS
  grammar::Action interpret(grammar::Grammar & g, InterpretInfo & ii) const override;
private:
  // FIELDS
  Action a_;
  dataset::syntax::Function f_;
};

// core implementation
IfFail::IfFail(const Action & a, const dataset::syntax::Function & f)
  : a_(a),
    f_(f) {}

IfFail::IfFail(const Action & a, dataset::syntax::Function && f)
  : a_(a),
    f_(std::move(f)) {}

IfFail::IfFail(Action && a, const dataset::syntax::Function & f)
  : a_(std::move(a)),
    f_(f) {}

IfFail::IfFail(Action && a, dataset::syntax::Function && f)
  : a_(std::move(a)),
    f_(std::move(f)) {}

grammar::Action IfFail::interpret(grammar::Grammar & g, InterpretInfo & ii) const {
  return grammar::ac(a_.add_to(g, ii), f_.interpret(ii.data));
}

} // namespace

// interface
Action ac(const Action & a, const dataset::syntax::Function & f) {return new IfFail(a, f);}
Action ac(const Action & a, dataset::syntax::Function && f) {return new IfFail(a, std::move(f));}
Action ac(Action && a, const dataset::syntax::Function & f) {return new IfFail(std::move(a), f);}
Action ac(Action && a, dataset::syntax::Function && f) {return new IfFail(std::move(a), std::move(f));}

} // namespace syntax
} // namespace grammar
} // namespace pm
