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

namespace pm {
namespace grammar {
namespace syntax {

namespace {

// core
class Opt
  : public ActionInterface {
public:
  // DEFAULTS
  // Opt() deleted
  // CONSTRUCTORS
  Opt(const Action & a);
  Opt(Action && a);
  // PRESERVING METHODS
  grammar::Action interpret(grammar::Grammar & g, InterpretInfo & ii) const override;
private:
  // FIELDS
  Action a_;
};

// core implementation
Opt::Opt(const Action & a)
  : a_(a) {}

Opt::Opt(Action && a)
  : a_(std::move(a)) {}

grammar::Action Opt::interpret(grammar::Grammar & g, InterpretInfo & ii) const {return grammar::opt(a_.add_to(g, ii));}

} // namespace

// interface
Action opt(const Action & a) {return new Opt(a);}
Action opt(Action && a) {return new Opt(std::move(a));}

} // namespace syntax
} // namespace grammar
} // namespace pm
