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
#ifndef __DATASET_FBASE_HPP
#define __DATASET_FBASE_HPP

#include <cstddef>
#include "dataset/set.hpp"

namespace pm {
namespace dataset {

class FBase {
public:
  virtual ~FBase() {}
  virtual void apply(const Set &) const {}
};

// NOTE: never use it as base pointer class, as its destructor is not virtual
class FTarget {
public:
  FTarget(size_t t) : t_(t) {}
  void set_target(size_t t) {t_ = t;}
  size_t target() const {return t_;}

protected:
  size_t t_;
};

// NOTE: never use it as base pointer class, as its destructor is not virtual
class FSource {
public:
  FSource(size_t s) : s_(s) {}
  void set_source(size_t s) {s_ = s;}
  size_t source() const {return s_;}

protected:
  size_t s_;
};

} // namespace dataset
} // namespace pm

#endif
