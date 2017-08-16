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
#ifndef __DATASET_FUNCTIONS_FLUSHER_HPP
#define __DATASET_FUNCTIONS_FLUSHER_HPP

#include <cstddef>
#include <utility>
#include <type_abuse/dref.hpp>
#include "dataset/fbase.hpp"
#include "dataset/function.hpp"

namespace pm {
namespace dataset {

class Flusher
  : public FBase,
    public FTarget {
public:
  // DEFAULTS
  // Flusher() deleted
  // CONSTRUCTORS
  inline Flusher(size_t t, const type_abuse::DRef & d);
  inline Flusher(size_t t, type_abuse::DRef && d);
  // PRESERVING METHODS
  inline void apply(const Set & ds) const override;

private:
  // FIELDS
  type_abuse::DRef d_;
};

inline Function flusher(size_t t, const type_abuse::DRef & d);
inline Function flusher(size_t t, type_abuse::DRef && d);


// IMPLEMENTATION
Flusher::Flusher(size_t t, const type_abuse::DRef & d)
  : FTarget(t),
    d_(d) {}

Flusher::Flusher(size_t t, type_abuse::DRef && d)
  : FTarget(t),
    d_(std::move(d)) {}

void Flusher::apply(const Set & ds) const {ds[t_].receive(d_);}

Function flusher(size_t t, const type_abuse::DRef & d) {return type_abuse::CRef<FBase>::create<Flusher>(t, d);}

Function flusher(size_t t, type_abuse::DRef && d) {return type_abuse::CRef<FBase>::create<Flusher>(t, std::move(d));}

} // namespace dataset
} // namespace pm

#endif
