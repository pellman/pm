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
#ifndef __DATASET_FUNCTIONS_COMPOSITION_HPP
#define __DATASET_FUNCTIONS_COMPOSITION_HPP

#include <list>
#include <utility>
#include "dataset/fbase.hpp"
#include "dataset/function.hpp"

namespace pm {
namespace dataset {

class Composition
  : public FBase {
public:
  // DEFAULTS
  Composition() = default;
  // CONSTRUCTORS
  inline Composition(const std::list<Function> & funcs);
  inline Composition(std::list<Function> && funcs);
  // PRESERVING METHODS
  void apply(const Set & ds) const override;

private:
  // FIELDS
  std::list<Function> funcs_;
};

inline Function composition(const std::list<Function> & funcs);
inline Function composition(std::list<Function> && funcs);


// IMPLEMENTATION
Composition::Composition(const std::list<Function> & funcs)
  : funcs_(funcs) {}

Composition::Composition(std::list<Function> && funcs)
  : funcs_(std::move(funcs)) {}

Function composition(const std::list<Function> & funcs) {return type_abuse::CRef<FBase>::create<Composition>(funcs);}

Function composition(std::list<Function> && funcs) {return type_abuse::CRef<FBase>::create<Composition>(std::move(funcs));}

} // namespace dataset
} // namespace pm

#endif
