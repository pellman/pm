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
#ifndef __UTILS_OPTIONAL_HPP
#define __UTILS_OPTIONAL_HPP

#include <utility>

namespace pm {
namespace utils {

template<typename Value>
class Optional {
public:
  // DEFAULTS
  Optional();
  Optional(const Optional & opt);
  Optional(Optional && opt);
  Optional & operator =(const Optional & opt);
  Optional & operator =(Optional && opt);
  ~Optional();
  // CONSTRUCTORS
  Optional(const Value & value);
  Optional(Value && value);
  // ASSIGNMENTS
  Optional & operator =(const Value & value);
  Optional & operator =(Value && value);
  // ALTERING METHODS
  void unset();
  // ACCESS METHODS
  bool has_value() const;
  Value & value();
  const Value & value() const;

private:
  // METHODS
  void set_(const Value & val);
  void set_(Value && val);
  void unset_();

  // FIELDS
  bool has_value_;
  union {
    Value value_;
  };
};


// IMPLEMENTATION
template<typename Value>
Optional<Value>::Optional()
  : has_value_(false) {}

template<typename Value>
Optional<Value>::Optional(const Optional & opt)
  : has_value_(opt.has_value_) {
  if(opt.has_value_) set_(opt.value_);
}

template<typename Value>
Optional<Value>::Optional(Optional && opt)
  : has_value_(opt.has_value_) {
  if(opt.has_value_) set_(std::move(opt.value_));
}

template<typename Value>
Optional<Value> & Optional<Value>::operator =(const Optional & opt) {
  if(has_value_) {
    if(opt.has_value_) {
      value_ = opt.value_;
    }
    else {
      has_value_ = false;
      unset_();
    }
  }
  else {
    if(opt.has_value_) {
      has_value_ = true;
      set_(opt.value_);
    }
  }
  return *this;
}

template<typename Value>
Optional<Value> & Optional<Value>::operator =(Optional && opt) {
  if(has_value_) {
    if(opt.has_value_) {
      value_ = std::move(opt.value_);
    }
    else {
      has_value_ = false;
      unset_();
    }
  }
  else {
    if(opt.has_value_) {
      has_value_ = true;
      set_(std::move(opt.value_));
    }
  }
  return *this;
}

template<typename Value>
Optional<Value>::~Optional() {
  if(has_value_) {
    unset_();
  }
}

template<typename Value>
Optional<Value>::Optional(const Value & value)
  : has_value_(true),
    value_(value) {}

template<typename Value>
Optional<Value>::Optional(Value && value)
  : has_value_(true),
    value_(std::move(value)) {}

template<typename Value>
Optional<Value> & Optional<Value>::operator =(const Value & value) {
  if(has_value_) {
    value_ = value;
  }
  else {
    has_value_ = true;
    set_(value);
  }
  return *this;
}

template<typename Value>
Optional<Value> & Optional<Value>::operator =(Value && value) {
  if(has_value_) {
    value_ = std::move(value);
  }
  else {
    has_value_ = true;
    set_(std::move(value));
  }
  return *this;
}

template<typename Value>
void Optional<Value>::unset() {
  if(has_value_) {
    unset_();
  }
  has_value_ = false;
}

template<typename Value>
bool Optional<Value>::has_value() const {return has_value_;}

template<typename Value>
Value & Optional<Value>::value() {return value_;}

template<typename Value>
const Value & Optional<Value>::value() const {return value_;}

template<typename Value>
void Optional<Value>::set_(const Value & val) {new (&value_) Value(val);}

template<typename Value>
void Optional<Value>::set_(Value && val) {new (&value_) Value(std::move(val));}

template<typename Value>
void Optional<Value>::unset_() {value_.~Value();}

} // namespace utils
} // namespace pm

#endif
