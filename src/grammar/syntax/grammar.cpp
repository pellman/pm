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
#include "pm/grammar/syntax/grammar.hpp"

#include "pm/utils/container_functions.hpp"

namespace pm {
namespace grammar {
namespace syntax {

grammar::Grammar Grammar::interpret() const {
  InterpretInfo ii;
  return interpret(ii);
}

grammar::Grammar Grammar::interpret(InterpretInfo & ii) const {
  ii.actions.clear();
  ii.data.clear();
  grammar::Grammar g;
  for(const auto & p : actions_) {
    p.second.add_to(g, p.first, ii);
  }
  if(main_.nonempty() && utils::is_in(main_.val(), ii.actions)) {
    g.set_main(ii.actions.at(main_.val()));
  }
  if(main_data_.nonempty()) {
    g.set_main_data(ii.data.add(main_data_.val()));
  }
  if(skip_.nonempty()) {
    g.set_skip(skip_.val());
  }
  return g;
}

} // namespace syntax
} // namespace grammar
} // namespace pm
