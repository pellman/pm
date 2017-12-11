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
class Rule
  : public ActionInterface {
public:
  // DEFAULTS
  // Rule() deleted
  // CONSTRUCTORS
  Rule(const std::list<Action> & actions);
  Rule(std::list<Action> && actions);
  // PRESERVING METHODS
  grammar::Action interpret(grammar::Grammar & g, InterpretInfo & ii) const override;
private:
  // FIELDS
  std::list<Action> actions_;
};

// implementation
Rule::Rule(const std::list<Action> & actions)
  : actions_(actions) {}

Rule::Rule(std::list<Action> && actions)
  : actions_(std::move(actions)) {}

grammar::Action Rule::interpret(grammar::Grammar & g, InterpretInfo & ii) const {
  std::list<size_t> res_actions;
  for(const auto & a : actions_) {
    res_actions.push_back(a.add_to(g, ii));
  }
  return grammar::rule(std::move(res_actions));
}

} // namespace

// interface
Action rule(const std::list<Action> & actions) {return new Rule(actions);}
Action rule(std::list<Action> && actions) {return new Rule(std::move(actions));}

} // namespace syntax
} // namespace grammar
} // namespace pm
