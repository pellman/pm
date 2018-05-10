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
class Alternative
  : public ActionInterface {
public:
  // DEFAULTS
  // Alternative() deleted
  // CONSTRUCTORS
  Alternative(const std::list<size_t> & indexes);
  Alternative(std::list<size_t> && indexes);
  // PRESERVING METHODS
  bool gamatch(stream::Stream & s, const Grammar & g, const Context & gcontext) const override;
  
private:
  // FIELDS
  std::list<size_t> indexes_;
};

// core implementation
Alternative::Alternative(const std::list<size_t> & indexes)
  : indexes_(indexes) {}

Alternative::Alternative(std::list<size_t> && indexes)
  : indexes_(std::move(indexes)) {}

bool Alternative::gamatch(stream::Stream & s, const Grammar & g, const Context & gcontext) const {
  for(const auto & a : indexes_) {
    if(g.action(a).gamatch(s, g, gcontext)) {
      return true;
    }
  }
  return false;
}

} // namespace

// interface
Action alt(const std::list<size_t> & indexes) {return new Alternative(indexes);}
Action alt(std::list<size_t> && indexes) {return new Alternative(std::move(indexes));}

} // namespace grammar
} // namespace pm
