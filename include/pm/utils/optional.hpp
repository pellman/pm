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
#ifndef __PM_UTILS_OPTIONAL_HPP
#define __PM_UTILS_OPTIONAL_HPP

#include <utility>

namespace pm {
namespace utils {

template<typename StoredType>
class Optional {
public:
  // DEFAULTS
  Optional();
  Optional(const Optional<StoredType> & opt);
  Optional(Optional<StoredType> && opt);
  Optional<StoredType> & operator =(const Optional<StoredType> & opt);
  Optional<StoredType> & operator =(Optional<StoredType> && opt);
  ~Optional();
  // CONSTRUCTORS
  Optional(const StoredType & value);
  Optional(StoredType && value);
  // ASSIGNMENTS
  Optional<StoredType> & operator =(const StoredType & value);
  Optional<StoredType> & operator =(StoredType && value);
  // ALTERING METHODS
  template<typename ... Args>
  void set(Args && ... args);
  void unset();
  // ACCESS METHODS
  bool empty() const;
  bool nonempty() const;
  StoredType & val();
  const StoredType & val() const;

private:
  // METHODS
  template<typename ... Args>
  void set_(Args && ... args);
  void unset_();

  // FIELDS
  bool has_value_;
  union {
    StoredType value_;
  };
};


// implementation
template<typename StoredType>
Optional<StoredType>::Optional()
  : has_value_(false) {}

template<typename StoredType>
Optional<StoredType>::Optional(const Optional<StoredType> & opt)
  : has_value_(opt.has_value_) {
  if(opt.has_value_) {
    set_(opt.value_);
  }
}

template<typename StoredType>
Optional<StoredType>::Optional(Optional<StoredType> && opt)
  : has_value_(opt.has_value_) {
  if(opt.has_value_) {
    set_(std::move(opt.value_));
  }
}

template<typename StoredType>
Optional<StoredType> & Optional<StoredType>::operator =(const Optional<StoredType> & opt) {
  if(has_value_) {
    unset_();
  }
  has_value_ = opt.has_value_;
  if(opt.has_value_) {
    set_(opt.value_);
  }
  return *this;
}

template<typename StoredType>
Optional<StoredType> & Optional<StoredType>::operator =(Optional<StoredType> && opt) {
  if(has_value_) {
    unset_();
  }
  has_value_ = opt.has_value_;
  if(opt.has_value_) {
    set_(std::move(opt.value_));
  }
  return *this;
}

template<typename StoredType>
Optional<StoredType>::~Optional() {
  if(has_value_) {
    unset_();
  }
}

template<typename StoredType>
Optional<StoredType>::Optional(const StoredType & value)
  : has_value_(true),
    value_(value) {}

template<typename StoredType>
Optional<StoredType>::Optional(StoredType && value)
  : has_value_(true),
    value_(std::move(value)) {}

template<typename StoredType>
Optional<StoredType> & Optional<StoredType>::operator =(const StoredType & value) {
  if(has_value_) {
    unset_();
  }
  else {
    has_value_ = true;
  }
  set_(value);
  return *this;
}

template<typename StoredType>
Optional<StoredType> & Optional<StoredType>::operator =(StoredType && value) {
  if(has_value_) {
    unset_();
  }
  else {
    has_value_ = true;
  }
  set_(std::move(value));
  return *this;
}

template<typename StoredType>
template<typename ... Args>
void Optional<StoredType>::set(Args && ... args) {
  if(has_value_) {
    unset_();
  }
  else {
    has_value_ = true;
  }
  set_(std::forward<Args>(args) ...);
}

template<typename StoredType>
void Optional<StoredType>::unset() {
  if(has_value_) {
    unset_();
  }
  has_value_ = false;
}

template<typename StoredType>
bool Optional<StoredType>::empty() const {return !has_value_;}

template<typename StoredType>
bool Optional<StoredType>::nonempty() const {return has_value_;}

template<typename StoredType>
StoredType & Optional<StoredType>::val() {return value_;}

template<typename StoredType>
const StoredType & Optional<StoredType>::val() const {return value_;}

template<typename StoredType>
template<typename ... Args>
void Optional<StoredType>::set_(Args && ... args) {new (&value_) StoredType(std::forward<Args>(args) ...);}

template<typename StoredType>
void Optional<StoredType>::unset_() {value_.~StoredType();}

} // namespace utils
} // namespace pm

#endif
