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

#include "pm/grammar/grammar.hpp"

namespace pm {
namespace grammar {

namespace {

// core
class Opt
  : public ActionInterface {
public:
  // DEFAULTS
  // Opt() deleted
  // CONSTRUCTORS
  Opt(size_t index);
  // PRESERVING METHODS
  bool gamatch(stream::Stream & s, const Grammar & g, const Context & gcontext) const override;
  
private:
  // FIELDS
  size_t index_;
};

// implementation
Opt::Opt(size_t index)
  : index_(index) {}

bool Opt::gamatch(stream::Stream & s, const Grammar & g, const Context & gcontext) const {
  g.action(index_).gamatch(s, g, gcontext);
  return true;
}

} // namespace

// interface
Action opt(size_t index) {return new Opt(index);}

} // namespace grammar
} // namespace pm
