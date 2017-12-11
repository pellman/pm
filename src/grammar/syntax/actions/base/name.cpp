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
#include "pm/grammar/grammar.hpp"
#include "pm/grammar/syntax/interpret_info.hpp"

namespace pm {
namespace grammar {
namespace syntax {

namespace {

// core
class Name
  : public ActionInterface {
public:
  // DEFAULTS
  // Name() deleted
  // CONSTRUCTORS
  Name(const std::string & n);
  Name(std::string && n);
  // PRESERVING METHODS
  grammar::Action interpret(grammar::Grammar & g, InterpretInfo & ii) const override;
private:
  // FIELDS
  std::string n_;
};

// core implementation
Name::Name(const std::string & n)
  : n_(n) {}

Name::Name(std::string && n)
  : n_(std::move(n)) {}

grammar::Action Name::interpret(grammar::Grammar & g, InterpretInfo & ii) const {
  size_t index;
  auto it = ii.actions.find(n_);
  if(it == ii.actions.end()) {
    index = ii.actions[n_] = g.add();
  }
  else {
    index = it->second;
  }
  return grammar::ac(index);
}

} // namespace

// interface
Action ac(const std::string & n) {return new Name(n);}
Action ac(std::string && n) {return new Name(std::move(n));}

} // namespace syntax
} // namespace grammar
} // namespace pm
