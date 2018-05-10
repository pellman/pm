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

template<typename T>
class Optional {
public:
  // DEFAULTS
  Optional();
  Optional(const Optional<T> & opt);
  Optional(Optional<T> && opt);
  Optional<T> & operator =(const Optional<T> & opt);
  Optional<T> & operator =(Optional<T> && opt);
  ~Optional();
  // CONSTRUCTORS
  Optional(const T & value);
  Optional(T && value);
  // ASSIGNMENTS
  Optional<T> & operator =(const T & value);
  Optional<T> & operator =(T && value);
  // ALTERING METHODS
  template<typename ... Args>
  void set(Args && ... args);
  void unset();
  // ACCESS METHODS
  bool empty() const;
  bool nonempty() const;
  T & val();
  const T & val() const;

private:
  // METHODS
  template<typename ... Args>
  void set_(Args && ... args);
  void unset_();

  // FIELDS
  bool has_value_;
  union {
    T value_;
  };
};


// implementation
template<typename T>
Optional<T>::Optional()
  : has_value_(false) {}

template<typename T>
Optional<T>::Optional(const Optional<T> & opt)
  : has_value_(opt.has_value_) {
  if(opt.has_value_) {
    set_(opt.value_);
  }
}

template<typename T>
Optional<T>::Optional(Optional<T> && opt)
  : has_value_(opt.has_value_) {
  if(opt.has_value_) {
    set_(std::move(opt.value_));
  }
}

template<typename T>
Optional<T> & Optional<T>::operator =(const Optional<T> & opt) {
  if(has_value_) {
    unset_();
  }
  has_value_ = opt.has_value_;
  if(opt.has_value_) {
    set_(opt.value_);
  }
  return *this;
}

template<typename T>
Optional<T> & Optional<T>::operator =(Optional<T> && opt) {
  if(has_value_) {
    unset_();
  }
  has_value_ = opt.has_value_;
  if(opt.has_value_) {
    set_(std::move(opt.value_));
  }
  return *this;
}

template<typename T>
Optional<T>::~Optional() {
  if(has_value_) {
    unset_();
  }
}

template<typename T>
Optional<T>::Optional(const T & value)
  : has_value_(true),
    value_(value) {}

template<typename T>
Optional<T>::Optional(T && value)
  : has_value_(true),
    value_(std::move(value)) {}

template<typename T>
Optional<T> & Optional<T>::operator =(const T & value) {
  if(has_value_) {
    unset_();
  }
  else {
    has_value_ = true;
  }
  set_(value);
  return *this;
}

template<typename T>
Optional<T> & Optional<T>::operator =(T && value) {
  if(has_value_) {
    unset_();
  }
  else {
    has_value_ = true;
  }
  set_(std::move(value));
  return *this;
}

template<typename T>
template<typename ... Args>
void Optional<T>::set(Args && ... args) {
  if(has_value_) {
    unset_();
  }
  else {
    has_value_ = true;
  }
  set_(std::forward<Args>(args) ...);
}

template<typename T>
void Optional<T>::unset() {
  if(has_value_) {
    unset_();
  }
  has_value_ = false;
}

template<typename T>
bool Optional<T>::empty() const {return !has_value_;}

template<typename T>
bool Optional<T>::nonempty() const {return has_value_;}

template<typename T>
T & Optional<T>::val() {return value_;}

template<typename T>
const T & Optional<T>::val() const {return value_;}

template<typename T>
template<typename ... Args>
void Optional<T>::set_(Args && ... args) {new (&value_) T(std::forward<Args>(args) ...);}

template<typename T>
void Optional<T>::unset_() {value_.~T();}

} // namespace utils
} // namespace pm

#endif
