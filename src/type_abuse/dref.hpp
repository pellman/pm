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
#ifndef __TYPE_ABUSE_DREF_HPP
#define __TYPE_ABUSE_DREF_HPP

#include <utility>
#include "type_abuse/dbase.hpp"
#include "type_abuse/ref.hpp"

namespace pm {
namespace type_abuse {

class DRef {
public:
  // DEFAULTS
  DRef() = default;
  // OPERATORS
  inline operator bool() const;
  // ALTERING METHODS
  inline void detach();
  inline void detach_receive(const DRef & ref);
  template<typename Value, typename ... Args>
  void detach_set(Args && ... args);
  inline void detach_unset();
  // PRESERVING METHODS
  // = alter pointed object =
  inline void receive(const DRef & ref) const;
  template<typename Value, typename ... Args>
  void set(Args && ... args) const;
  inline void swap(const DRef & ref) const;
  inline void unset() const;
  // = preserve pointed object =
  inline DRef clone() const;
  inline void send(const DRef & ref) const;
  // ACCESS METHODS
  inline bool empty() const;
  inline bool nonempty() const;
  template<typename Value>
  Value & val() const;
  // STATIC METHODS
  template<typename Value, typename ... Args>
  static DRef create(Args && ... args);

private:
  // CONSTRUCTORS
  inline DRef(const Ref<DBase> & ref);
  inline DRef(Ref<DBase> && ref);
  // FIELDS
  Ref<DBase> ref_;
};


// IMPLEMENTATION
DRef::operator bool() const {return nonempty();}

void DRef::detach() {ref_.detach();}

void DRef::detach_receive(const DRef & ref) {ref_.detach_receive(ref.ref_);}

template<typename Value, typename ... Args>
void DRef::detach_set(Args && ... args) {ref_.detach_set<DDeriv<Value>>(Value(std::forward<Args>(args) ...));}

void DRef::detach_unset() {ref_.detach_unset();}

void DRef::receive(const DRef & ref) const {ref_.receive(ref.ref_);}

template<typename Value, typename ... Args>
void DRef::set(Args && ... args) const {ref_.set<DDeriv<Value>>(Value(std::forward<Args>(args) ...));}

void DRef::swap(const DRef & ref) const {ref_.swap(ref.ref_);}

void DRef::unset() const {ref_.unset();}

DRef DRef::clone() const {return ref_.clone();}

void DRef::send(const DRef & ref) const {ref.ref_.receive(ref_);}

bool DRef::empty() const {return ref_.empty();}

bool DRef::nonempty() const {return ref_.nonempty();}

template<typename Value>
Value & DRef::val() const {return ref_.val<DDeriv<Value>>().value;}

template<typename Value, typename ... Args>
DRef DRef::create(Args && ... args) {return Ref<DBase>::create<DDeriv<Value>>(Value(std::forward<Args>(args)...));}

DRef::DRef(const Ref<DBase> & ref)
  : ref_(ref) {}

DRef::DRef(Ref<DBase> && ref)
  : ref_(std::move(ref)) {}

} // namespace type_abuse
} // namespace pm

#endif
