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

namespace pm {
namespace grammar {

namespace {

// core
class Function
  : public ActionInterface {
public:
  // DEFAULTS
  // Function() deleted
  // CONSTRUCTORS
  Function(const dataset::Function & f);
  Function(dataset::Function && f);
  // PRESERVING METHODS
  bool gamatch(stream::Stream & s, const Grammar & g, const Context & gcontext) const override;
  
private:
  // FIELDS
  dataset::Function f_;
};

// core implementation
Function::Function(const dataset::Function & f)
  : f_(f) {}

Function::Function(dataset::Function && f)
  : f_(std::move(f)) {}

bool Function::gamatch(stream::Stream &, const Grammar &, const Context & gcontext) const {
  if(gcontext.data_flag()) {
    f_.apply(gcontext.dataset);
  }
  return true;
}

} // namespace

// interface
Action ac(const dataset::Function & f) {return new Function(f);}
Action ac(dataset::Function && f) {return new Function(std::move(f));}

} // namespace grammar
} // namespace pm
