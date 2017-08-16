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
#ifndef __DATASET_FUNCTIONS_CREATOR_HPP
#define __DATASET_FUNCTIONS_CREATOR_HPP

#include <cstddef>
#include <utility>
#include <type_abuse/dfun.hpp>
#include "dataset/fbase.hpp"
#include "dataset/function.hpp"

namespace pm {
namespace dataset {

class Creator
  : public FBase,
    public FTarget {
public:
  // DEFAULTS
  // Creator() deleted
  // CONSTRUCTORS
  inline Creator(size_t t, const type_abuse::Creator & f);
  inline Creator(size_t t, type_abuse::Creator && f);
  // PRESERVING METHODS
  inline void apply(const Set & ds) const override;

private:
  // FIELDS
  type_abuse::Creator f_;
};

inline Function creator(size_t t, const type_abuse::Creator & f);
inline Function creator(size_t t, type_abuse::Creator && f);


// IMPLEMENTATION
Creator::Creator(size_t t, const type_abuse::Creator & f)
  : FTarget(t),
    f_(f) {}

Creator::Creator(size_t t, type_abuse::Creator && f)
  : FTarget(t),
    f_(std::move(f)) {}

void Creator::apply(const Set & ds) const {ds[t_].receive(f_());}

Function creator(size_t t, const type_abuse::Creator & f) {return type_abuse::CRef<FBase>::create<Creator>(t, f);}

Function creator(size_t t, type_abuse::Creator && f) {return type_abuse::CRef<FBase>::create<Creator>(t, std::move(f));}

} // namespace dataset
} // namespace pm

#endif
