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
#ifndef __PM_GRAMMAR_SYNTAX_ACTION_INTERFACE_HPP
#define __PM_GRAMMAR_SYNTAX_ACTION_INTERFACE_HPP

#include <cstddef>
#include <string>
#include "pm/grammar/action.hpp"
#include "pm/grammar/actions.hpp"

namespace pm {
namespace grammar {

class Grammar;

namespace syntax {

class InterpretInfo;

class ActionInterface {
public:
  virtual ~ActionInterface() {}
  size_t add_to(grammar::Grammar & g, const std::string & name, InterpretInfo & ii) const;
  size_t add_to(grammar::Grammar & g, std::string && name, InterpretInfo & ii) const;
  size_t add_to(grammar::Grammar & g, InterpretInfo & ii) const;
  inline virtual grammar::Action interpret(grammar::Grammar & g, InterpretInfo & ii) const;
};


// implementation
Action ActionInterface::interpret(Grammar &, InterpretInfo &) const {return grammar::ac_false();}

} // namespace syntax
} // namespace grammar
} // namespace pm

#endif
