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
#ifndef __DATASET_FUNCTIONS_APPLIER_HPP
#define __DATASET_FUNCTIONS_APPLIER_HPP

#include <cstddef>
#include <utility>
#include <type_abuse/dfun.hpp>
#include "dataset/fbase.hpp"
#include "dataset/function.hpp"

namespace pm {
namespace dataset {

class Applier
  : public FBase,
    public FTarget,
    public FSource {
public:
  // DEFAULTS
  // Applier() deleted
  // CONSTRUCTORS
  inline Applier(size_t t, size_t s, const type_abuse::Applier & f);
  inline Applier(size_t t, size_t s, type_abuse::Applier && f);
  // PRESERVING METHODS
  inline void apply(const Set & ds) const override;

private:
  // FIELDS
  type_abuse::Applier f_;
};

inline Function applier(size_t t, size_t s, const type_abuse::Applier & f);
inline Function applier(size_t t, size_t s, type_abuse::Applier && f);


// IMPLEMENTATION
Applier::Applier(size_t t, size_t s, const type_abuse::Applier & f)
  : FTarget(t),
    FSource(s),
    f_(f) {}

Applier::Applier(size_t t, size_t s, type_abuse::Applier && f)
  : FTarget(t),
    FSource(s),
    f_(std::move(f)) {}

void Applier::apply(const Set & ds) const {f_(ds[t_], ds[s_]);}

Function applier(size_t t, size_t s, const type_abuse::Applier & f) {return type_abuse::CRef<FBase>::create<Applier>(t, s, f);}

Function applier(size_t t, size_t s, type_abuse::Applier && f) {return type_abuse::CRef<FBase>::create<Applier>(t, s, std::move(f));}

} // namespace dataset
} // namespace pm

#endif
