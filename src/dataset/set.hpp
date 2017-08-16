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
#ifndef __DATASET_SET_HPP
#define __DATASET_SET_HPP

#include <cstddef>
#include <initializer_list>
#include <utility>
#include <vector>
#include <type_abuse/dref.hpp>

namespace pm {
namespace dataset {

class Set {
public:
  // DEFAULTS
  // Set() deleted
  // CONSTRUCTORS
  inline Set(std::initializer_list<type_abuse::DRef> l);
  inline Set(const std::vector<type_abuse::DRef> & v);
  inline Set(std::vector<type_abuse::DRef> && v);
  Set(size_t size);
  // OPERATORS
  inline type_abuse::DRef & operator [](size_t i);
  inline const type_abuse::DRef & operator [](size_t i) const;
  // ALTERING METHODS
  void detach();
  void detach_receive(const Set & set); // принимается ровно столько элементов, сколько в v_
  void detach_unset();
  // PRESERVING METHODS
  // = alter data =
  void receive(const Set & set) const; // принимается ровно столько элементов, сколько в v_
  void unset() const;
  // = preserve data =
  Set clone() const;
  void send(const Set & set) const; // посылается ровно столько элементов, сколько в v_
  // ACCESS METHODS
  // = access =
  inline type_abuse::DRef & at(size_t i);
  inline const type_abuse::DRef & at(size_t i) const;
  inline size_t size() const;
  // = iteration =
  inline std::vector<type_abuse::DRef>::iterator begin();
  inline std::vector<type_abuse::DRef>::const_iterator begin() const;
  inline std::vector<type_abuse::DRef>::iterator end();
  inline std::vector<type_abuse::DRef>::const_iterator end() const;

private:
  // FIELDS
  std::vector<type_abuse::DRef> v_;
};


// IMPLEMENTATION
Set::Set(std::initializer_list<type_abuse::DRef> l)
  : v_(l) {}

Set::Set(const std::vector<type_abuse::DRef> & v)
  : v_(v) {}

Set::Set(std::vector<type_abuse::DRef> && v)
  : v_(std::move(v)) {}

type_abuse::DRef & Set::operator [](size_t i) {return v_[i];}

const type_abuse::DRef & Set::operator [](size_t i) const {return v_[i];}

type_abuse::DRef & Set::at(size_t i) {return v_.at(i);}

const type_abuse::DRef & Set::at(size_t i) const {return v_.at(i);}

size_t Set::size() const {return v_.size();}

std::vector<type_abuse::DRef>::iterator Set::begin() {return v_.begin();}

std::vector<type_abuse::DRef>::const_iterator Set::begin() const {return v_.begin();}

std::vector<type_abuse::DRef>::iterator Set::end() {return v_.end();}

std::vector<type_abuse::DRef>::const_iterator Set::end() const {return v_.end();}

} // namespace dataset
} // namespace pm

#endif
