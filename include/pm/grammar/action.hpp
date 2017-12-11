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
#ifndef __PM_GRAMMAR_ACTION_HPP
#define __PM_GRAMMAR_ACTION_HPP

#include <utility>
#include "pm/type_abuse/sptr.hpp"
#include "pm/grammar/action_interface.hpp"

namespace pm {
namespace grammar {

class Action
  : public ActionInterface {
public:
  // DEFAULTS
  Action() = default;
  // CONSTRUCTORS
  inline Action(ActionInterface * ptr);
  inline Action(const type_abuse::SPtr<ActionInterface> & ptr);
  inline Action(type_abuse::SPtr<ActionInterface> && ptr);
  // PRESERVING METHODS
  inline bool gamatch_full(stream::Stream & s, const Grammar & g, const Context & gcontext) const override;
  // FIELDS
  type_abuse::SPtr<ActionInterface> ptr_;
};


// implementation
Action::Action(ActionInterface * ptr)
  : ptr_(ptr) {}

Action::Action(const type_abuse::SPtr<ActionInterface> & ptr)
  : ptr_(ptr) {}

Action::Action(type_abuse::SPtr<ActionInterface> && ptr)
  :ptr_(std::move(ptr)) {}

bool Action::gamatch_full(stream::Stream & s, const Grammar & g, const Context & gcontext) const {return ptr_->gamatch_full(s, g, gcontext);}

} // namespace grammar
} // namespace pm

#endif
