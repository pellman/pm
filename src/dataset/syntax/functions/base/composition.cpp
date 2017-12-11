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
#include "pm/dataset/syntax/functions/base.hpp"

#include "pm/dataset/functions/base.hpp"

namespace pm {
namespace dataset {
namespace syntax {

namespace {

// core
class Composition
  : public FunctionInterface {
public:
  // DEFAULTS
  // Composition() deleted
  // CONSTRUCTORS
  Composition(const std::list<Function> & fl);
  Composition(std::list<Function> && fl);
  // PRESERVING METHODS
  dataset::Function interpret(Set & s) const override;
private:
  // FIELDS
  std::list<Function> fl_;
};

// core implementation
Composition::Composition(const std::list<Function> & fl)
  : fl_(fl) {}

Composition::Composition(std::list<Function> && fl)
  : fl_(std::move(fl)) {}

dataset::Function Composition::interpret(Set & s) const {
  std::list<dataset::Function> reslist;
  for(const auto & f : fl_) {
    reslist.push_back(f.interpret(s));
  }
  return dataset::comp(std::move(reslist));
}

} // namespace

// interface
Function comp(const std::list<Function> & fl) {return new Composition(fl);}
Function comp(std::list<Function> && fl) {return new Composition(std::move(fl));}

} // namespace syntax
} // namespace dataset
} // namespace pm
