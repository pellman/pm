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
#ifndef __DATASET_FUNCTIONS_MODIFIER_HPP
#define __DATASET_FUNCTIONS_MODIFIER_HPP

#include <cstddef>
#include <utility>
#include <type_abuse/dfun.hpp>
#include "dataset/fbase.hpp"
#include "dataset/function.hpp"

namespace pm {
namespace dataset {

class Modifier
  : public FBase,
    public FTarget {
public:
  // DEFAULTS
  // Modifier() deleted
  // CONSTRUCTORS
  inline Modifier(size_t t, const type_abuse::Modifier & f);
  inline Modifier(size_t t, type_abuse::Modifier && f);
  // PRESERVING METHODS
  inline void apply(const Set & ds) const override;

private:
  // FIELDS
  type_abuse::Modifier f_;
};

inline Function modifier(size_t t, const type_abuse::Modifier & f);
inline Function modifier(size_t t, type_abuse::Modifier && f);


// IMPLEMENTATION
Modifier::Modifier(size_t t, const type_abuse::Modifier & f)
  : FTarget(t),
    f_(f) {}

Modifier::Modifier(size_t t, type_abuse::Modifier && f)
  : FTarget(t),
    f_(std::move(f)) {}

void Modifier::apply(const Set & ds) const {f_(ds[t_]);}

Function modifier(size_t t, const type_abuse::Modifier & f) {return type_abuse::CRef<FBase>::create<Modifier>(t, f);}

Function modifier(size_t t, type_abuse::Modifier && f) {return type_abuse::CRef<FBase>::create<Modifier>(t, std::move(f));}

} // namespace dataset
} // namespace pm

#endif
