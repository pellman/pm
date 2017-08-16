/*
    This file is part of the pm library package.
    Copyright (C) 2017 Vladislav Podymov
    
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
#ifndef __DATASET_FUNCTION_HPP
#define __DATASET_FUNCTION_HPP

#include <type_abuse/cref.hpp>
#include "dataset/fbase.hpp"

namespace pm {
namespace dataset {

class Function
  : public FBase {
public:
  // DEFAULTS
  Function() = default;
  // CONSTRUCTORS
  inline Function(const type_abuse::CRef<FBase> & pf);
  inline Function(type_abuse::CRef<FBase> && pf);
  // PRESERVING METHODS
  inline void apply(const Set & ds) const override;

private:
  // FIELDS
  type_abuse::CRef<FBase> rf_;
};

extern const Function f_trivial;


// IMPLEMENTATION
Function::Function(const type_abuse::CRef<FBase> & pf)
  : rf_(pf) {}

Function::Function(type_abuse::CRef<FBase> && pf)
  : rf_(std::move(pf)) {}

void Function::apply(const Set & ds) const {
  if(rf_) {
    rf_->apply(ds);
  }
}

} // namespace dataset
} // namespace pm

#endif
