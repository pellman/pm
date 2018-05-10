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
#include "pm/dataset/functions/composition.hpp"

#include <utility>

namespace pm {
namespace dataset {

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
  void apply(const Set & s) const override;
private:
  // FIELDS
  std::list<Function> fl_;
};

// core implementation
Composition::Composition(const std::list<Function> & fl)
  : fl_(fl) {}

Composition::Composition(std::list<Function> && fl)
  : fl_(std::move(fl)) {}

void Composition::apply(const Set & s) const {
  for(const auto & f : fl_) {
    f.apply(s);
  }
}

} // namespace

// interface
Function comp(const std::list<Function> & fl) {return new Composition(fl);}
Function comp(std::list<Function> && fl) {return new Composition(std::move(fl));}
Function operator *(const Function & f1, const Function & f2) {return comp(f1, f2);}
Function operator *(const Function & f1, Function && f2) {return comp(f1, std::move(f2));}
Function operator *(Function && f1, const Function & f2) {return comp(std::move(f1), f2);}
Function operator *(Function && f1, Function && f2) {return comp(std::move(f1), std::move(f2));}

} // namespace dataset
} // namespace pm
