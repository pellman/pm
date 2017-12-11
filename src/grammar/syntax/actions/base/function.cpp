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
class Function
  : public ActionInterface {
public:
  // DEFAULTS
  // Function() deleted
  // CONSTRUCTORS
  Function(const dataset::syntax::Function & f);
  Function(dataset::syntax::Function && f);
  // PRESERVING METHODS
  grammar::Action interpret(grammar::Grammar & g, InterpretInfo & ii) const override;
private:
  // FIELDS
  dataset::syntax::Function f_;
};

// core implementation
Function::Function(const dataset::syntax::Function & f)
  : f_(f) {}

Function::Function(dataset::syntax::Function && f)
  : f_(std::move(f)) {}

grammar::Action Function::interpret(grammar::Grammar &, InterpretInfo & ii) const {
  return grammar::ac(f_.interpret(ii.data));
}

} // namespace

// interface
Action ac(const dataset::syntax::Function & f) {return new Function(f);}
Action ac(dataset::syntax::Function && f) {return new Function(std::move(f));}

} // namespace syntax
} // namespace grammar
} // namespace pm
