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
#include "pm/grammar/actions.hpp"

#include <utility>
#include "pm/grammar/grammar.hpp"

namespace pm {
namespace grammar {

namespace {

// core
class Rule
  : public ActionInterface {
public:
  // DEFAULTS
  // Rule() deleted
  // CONSTRUCTORS
  Rule(const std::list<size_t> & indexes);
  Rule(std::list<size_t> && indexes);
  // PRESERVING METHODS
  bool gamatch_full(stream::Stream & s, const Grammar & g, const Context & gcontext) const override;
  
private:
  // FIELDS
  std::list<size_t> indexes_;
};

// implementation
Rule::Rule(const std::list<size_t> & indexes)
  : indexes_(indexes) {}

Rule::Rule(std::list<size_t> && indexes)
  : indexes_(std::move(indexes)) {}

bool Rule::gamatch_full(stream::Stream & s, const Grammar & g, const Context & gcontext) const {
  Context aux_context = gcontext;
  aux_context.castr.detach_unset(true);
  bool res = true;
  for(const auto & a : indexes_) {
    if(!g.action(a).gamatch_full(s, g, aux_context)) {
      res = false;
      break;
    }
  }
  if(res) {
    if(gcontext.castr.active()) {
      gcontext.str() += std::move(aux_context.str());
    }
  }
  else {
    s.unget(std::move(aux_context.str()));
  }
  return res;
}

} // namespace

// interface
Action rule(const std::list<size_t> & indexes) {return new Rule(indexes);}
Action rule(std::list<size_t> && indexes) {return new Rule(std::move(indexes));}

} // namespace grammar
} // namespace pm
