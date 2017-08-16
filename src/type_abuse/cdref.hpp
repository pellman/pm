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
#ifndef __TYPE_ABUSE_CDREF_HPP
#define __TYPE_ABUSE_CDREF_HPP

#include <utility>
#include "type_abuse/cref.hpp"
#include "type_abuse/dbase.hpp"

namespace pm {
namespace type_abuse {

class CDRef {
public:
  // DEFAULTS
  CDRef() = default;
  // OPERATORS
  inline operator bool() const;
  // ALTERING METHODS
  inline void detach();
  inline void detach_receive(const CDRef & ref);
  template<typename Value, typename ... Args>
  void detach_set(Args && ... args);
  // PRESERVING METHODS
  inline CDRef clone() const;
  // ACCESS METHODS
  inline bool empty() const;
  inline bool nonempty() const;
  template <typename Value>
  Value & val() const;
  // STATIC METHODS
  template<typename Value, typename ... Args>
  static CDRef create(Args && ... args);

private:
  // CONSTRUCTORS
  inline CDRef(const CRef<DBase> & cref);
  inline CDRef(CRef<DBase> && cref);
  // FIELDS
  CRef<DBase> cref_;
};


// IMPLEMENTATION
CDRef::operator bool() const {return nonempty();}

void CDRef::detach() {cref_.detach();}

void CDRef::detach_receive(const CDRef & ref) {cref_.detach_receive(ref.cref_);}

template<typename Value, typename ... Args>
void CDRef::detach_set(Args && ... args) {cref_.detach_set<DDeriv<Value>>(Value(std::forward<Args>(args) ...));}

CDRef CDRef::clone() const {return cref_.clone();}

bool CDRef::empty() const {return cref_.empty();}

bool CDRef::nonempty() const {return cref_.nonempty();}

template <typename Value>
Value & CDRef::val() const {return cref_.val<DDeriv<Value>>().value;}

CDRef::CDRef(const CRef<DBase> & cref)
  : cref_(cref) {}

CDRef::CDRef(CRef<DBase> && cref)
  : cref_(std::move(cref)) {}

template<typename Value, typename ... Args>
CDRef CDRef::create(Args && ... args) {return CRef<DBase>::create<DDeriv<Value>>(Value(std::forward<Args>(args)...));}

} // namespace type_abuse
} // namespace pm

#endif
