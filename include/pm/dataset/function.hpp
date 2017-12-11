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
#ifndef __PM_DATASET_FUNCTION_HPP
#define __PM_DATASET_FUNCTION_HPP

#include <utility>
#include "pm/type_abuse/sptr.hpp"
#include "pm/dataset/function_interface.hpp"

namespace pm {
namespace dataset {

class Function
  : public FunctionInterface {
public:
  // DEFAULTS
  Function() = default;
  // CONSTRUCTORS
  inline Function(FunctionInterface * ptr);
  inline Function(const type_abuse::SPtr<FunctionInterface> & ptr);
  inline Function(type_abuse::SPtr<FunctionInterface> && ptr);
  // PRESERVING METHODS
  inline void apply(const Set & ds) const override;

private:
  // FIELDS
  type_abuse::SPtr<FunctionInterface> ptr_;
};


// implementation
Function::Function(FunctionInterface * ptr)
  : ptr_(ptr) {}

Function::Function(const type_abuse::SPtr<FunctionInterface> & ptr)
  : ptr_(ptr) {}

Function::Function(type_abuse::SPtr<FunctionInterface> && ptr)
  : ptr_(std::move(ptr)) {}

void Function::apply(const Set & ds) const {ptr_->apply(ds);}

} // namespace dataset
} // namespace pm

#endif
