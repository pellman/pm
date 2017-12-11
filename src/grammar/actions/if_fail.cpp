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
class IfFail
  : public ActionInterface {
public:
  // DEFAULTS
  // IfFail() deleted
  // CONSTRUCTORS
  IfFail(size_t index, const dataset::Function & f_fail);
  IfFail(size_t index, dataset::Function && f_fail);
  // PRESERVING METHODS
  bool gamatch_full(stream::Stream & s, const Grammar & g, const Context & gcontext) const override;
  
private:
  // FIELDS
  size_t index_;
  dataset::Function f_fail_;
};

// core implementation
IfFail::IfFail(size_t index, const dataset::Function & f_fail)
  : index_(index),
    f_fail_(f_fail) {}

IfFail::IfFail(size_t index, dataset::Function && f_fail)
  : index_(index),
    f_fail_(std::move(f_fail)) {}

bool IfFail::gamatch_full(stream::Stream & s, const Grammar & g, const Context & gcontext) const {
  bool res = g.action(index_).gamatch_full(s, g, gcontext);
  if(!res && gcontext.cadataset.active()) {
    f_fail_.apply(gcontext.cadataset.cds);
  }
  return res;
}

} // namespace

// interface
Action ac(size_t index, const dataset::Function & f_fail) {return new IfFail(index, f_fail);}
Action ac(size_t index, dataset::Function && f_fail) {return new IfFail(index, std::move(f_fail));}

} // namespace grammar
} // namespace pm
