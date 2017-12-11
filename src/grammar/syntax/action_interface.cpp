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
#include "pm/grammar/syntax/action_interface.hpp"

#include "pm/grammar/grammar.hpp"
#include "pm/grammar/syntax/interpret_info.hpp"

namespace pm {
namespace grammar {
namespace syntax {

size_t ActionInterface::add_to(grammar::Grammar & g, const std::string & name, InterpretInfo & ii) const {
  size_t res;
  auto it = ii.actions.find(name);
  if(it == ii.actions.end()) {
    res = ii.actions[name] = g.add();
  }
  else {
    res = it->second;
  }
  auto action = interpret(g, ii);
  g.action(res) = action;
  return res;
}

size_t ActionInterface::add_to(grammar::Grammar & g, std::string && name, InterpretInfo & ii) const {
  size_t res;
  auto it = ii.actions.find(name);
  if(it == ii.actions.end()) {
    res = ii.actions[std::move(name)] = g.add();
  }
  else {
    res = it->second;
  }
  auto action = interpret(g, ii);
  g.action(res) = action;
  return res;
}

size_t ActionInterface::add_to(grammar::Grammar & g, InterpretInfo & ii) const {
  size_t res = g.add();
  auto action = interpret(g, ii);
  g.action(res) = action;
  return res;
}

} // namespace syntax
} // namespace grammar
} // namespace pm
