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
#ifndef __DATASET_SYNTAX_SET_HPP
#define __DATASET_SYNTAX_SET_HPP

#include <cstddef>
#include <string>
#include <utility>
#include <utils/numeration.hpp>
#include "dataset/syntax/function.hpp"

namespace pm {
namespace dataset {
namespace syntax {

class Set {
public:
  // ALTERING METHODS
  inline size_t add(const std::string & name);
  inline size_t add(std::string && name);
  void add(const Function & fun);
  void add(Function && fun);
  inline void clear();
  // ACCESS METHODS
  inline bool has_name(const std::string & name) const;
  inline size_t index_of(const std::string & name) const;
  inline const utils::Numeration<std::string> & names() const;
  inline size_t size() const;

private:
  // FIELDS
  utils::Numeration<std::string> names_;
};


// IMPLEMENTATION
size_t Set::add(const std::string & name) {return names_.add(name);}

size_t Set::add(std::string && name) {return names_.add(std::move(name));}

void Set::clear() {names_.clear();}

bool Set::has_name(const std::string & name) const {return names_.has(name);}

size_t Set::index_of(const std::string & name) const {return names_.index_of(name);}

const utils::Numeration<std::string> & Set::names() const {return names_;}

size_t Set::size() const {return names_.size();}

} // namespace syntax
} // namespace dataset
} // namespace pm

#endif
