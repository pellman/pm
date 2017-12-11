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
#ifndef __PM_GRAMMAR_ACTION_INTERFACE_HPP
#define __PM_GRAMMAR_ACTION_INTERFACE_HPP

#include <string>
#include <sstream>
#include "pm/stream/stream.hpp"
#include "pm/grammar/context.hpp"

namespace pm {
namespace grammar {

class Grammar;

class ActionInterface {
public:
  virtual ~ActionInterface() {}
  inline virtual bool gamatch_full(stream::Stream & s, const Grammar & g, const Context & gcontext) const;
};


// implementation
bool ActionInterface::gamatch_full(stream::Stream &, const Grammar &, const Context &) const {return false;}


} // namespace grammar
} // namespace pm

#endif
