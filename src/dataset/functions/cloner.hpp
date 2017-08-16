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
#ifndef __DATASET_FUNCTIONS_CLONER_HPP
#define __DATASET_FUNCTIONS_CLONER_HPP

#include <cstddef>
#include "dataset/fbase.hpp"
#include "dataset/function.hpp"

namespace pm {
namespace dataset {

class Cloner
  : public FBase,
    public FTarget,
    public FSource {
public:
  // DEFAULTS
  // Cloner() deleted
  // CONSTRUCTORS
  inline Cloner(size_t t, size_t s);
  // PRESERVING METHODS
  inline void apply(const Set & ds) const override;
};

inline Function cloner(size_t t, size_t s);


// IMPLEMENTATION
Cloner::Cloner(size_t t, size_t s)
  : FTarget(t),
    FSource(s) {}

void Cloner::apply(const Set & ds) const {ds[t_].receive(ds[s_]);}

Function cloner(size_t t, size_t s) {return type_abuse::CRef<FBase>::create<Cloner>(t, s);}

} // namespace dataset
} // namespace pm

#endif
