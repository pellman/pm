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
class FailFunction
  : public ActionInterface {
public:
  // DEFAULTS
  // Function() deleted
  // CONSTRUCTORS
  FailFunction(size_t index, const dataset::Function & f);
  FailFunction(size_t index, dataset::Function && f);
  // PRESERVING METHODS
  bool gamatch(stream::Stream & s, const Grammar & g, const Context & gcontext) const override;
  
private:
  // FIELDS
  size_t index_;
  dataset::Function f_;
};

// core implementation
FailFunction::FailFunction(size_t index, const dataset::Function & f)
  : index_(index),
    f_(f) {}

FailFunction::FailFunction(size_t index, dataset::Function && f)
  : index_(index),
    f_(std::move(f)) {}

bool FailFunction::gamatch(stream::Stream & s, const Grammar & g, const Context & gcontext) const {
  if(!gcontext.data_flag()) {
    return g.action(index_).gamatch(s, g, gcontext);
  }
  bool res = g.action(index_).gamatch(s, g, gcontext);
  if(!res) {
    f_.apply(gcontext.dataset);
  }
  return res;
}

} // namespace

// interface
Action ac(size_t index, const dataset::Function & f) {return new FailFunction(index, f);}
Action ac(size_t index, dataset::Function && f) {return new FailFunction(index, std::move(f));}

} // namespace grammar
} // namespace pm
