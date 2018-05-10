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
#ifndef __PM_DATASET_SET_HPP
#define __PM_DATASET_SET_HPP

#include <cstddef>
#include <initializer_list>
#include <utility>
#include <vector>
#include "pm/type_abuse/dptr.hpp"
#include "pm/type_abuse/sptr.hpp"

namespace pm {
namespace dataset {

class Set {
public:
  // ALTERING METHODS
  void detach();
  void detach_receive(const Set & set);
  inline void detach_unset();
  // PRESERVING METHODS
  // = alter data =
  void receive(const Set & set) const;
  inline void swap(const Set & set) const;
  inline void unset() const;
  // = preserve data =
  Set clone() const;
  inline void send(const Set & set) const;
  // ACCESS METHODS
  // = access =
  const type_abuse::DPtr & ptr(size_t i) const;
  template<typename T>
  T & data(size_t i) const;

private:
  // METHODS
  void detach_all_data_() const;
  void resize_(size_t size) const;
  // FIELDS
  type_abuse::SPtr<std::vector<type_abuse::DPtr>> ptr_;
};


// implementation
void Set::detach_unset() {ptr_.detach_unset();}

void Set::swap(const Set & set) const {ptr_.swap(set.ptr_);}

void Set::unset() const {ptr_.unset();}

void Set::send(const Set & set) const {set.receive(*this);}

template<typename T>
T & Set::data(size_t i) const {return ptr_.val().at(i).val<T>();}

} // namespace dataset
} // namespace pm

#endif
