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
#include "pm/grammar/grammar.hpp"

namespace pm {
namespace grammar {

size_t Grammar::add() {return add(Action());}

size_t Grammar::add(const Action & a) {
  size_t res = actions_.size();
  actions_.push_back(a);
  return res;
}

size_t Grammar::add(Action && a) {
  size_t res = actions_.size();
  actions_.push_back(std::move(a));
  return res;
}

bool Grammar::gmatch(std::istream & s, const Context & gcontext) const {
  stream::Stream str(s);
  return gmatch(str, gcontext);
}

bool Grammar::gmatch(const std::string & s, const Context & gcontext) const {
  std::stringstream str(s);
  return gmatch(str, gcontext);
}

bool Grammar::match_full(stream::Stream & s, const regexp::Context & context) const {
  Context gcontext{context.castr, {context.cadata.cact}};
  if(context.cadata.active()) {
    gcontext.data(main_data()).receive(context.data());
  }
  bool res = gmatch_full(s, gcontext);
  if(res && context.cadata.active()) {
    context.data().swap(gcontext.data(main_data()));
  }
  return res;
}

} // namespace grammar
} // namespace pm
