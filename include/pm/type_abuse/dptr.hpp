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
#ifndef __PM_TYPE_ABUSE_DPTR_HPP
#define __PM_TYPE_ABUSE_DPTR_HPP

#include <utility>
#include "pm/type_abuse/dbase.hpp"
#include "pm/type_abuse/ptr.hpp"

namespace pm {
namespace type_abuse {

class DPtr {
public:
  // DEFAULTS
  DPtr() = default;
  // OPERATORS
  inline operator bool() const;
  // ALTERING METHODS
  inline void detach();
  inline void detach_receive(const DPtr & ptr);
  template<typename NewStoredType, typename ... Args>
  void detach_set(Args && ... args);
  inline void detach_unset();
  // PRESERVING METHODS
  // = alter pointed object =
  inline void receive(const DPtr & ptr) const;
  template<typename NewStoredType, typename ... Args>
  void set(Args && ... args) const;
  inline void swap(const DPtr & ptr) const;
  inline void unset() const;
  // = preserve pointed object =
  inline DPtr clone() const;
  inline void send(const DPtr & ptr) const;
  // ACCESS METHODS
  inline bool empty() const;
  inline bool nonempty() const;
  template<typename StoredType>
  StoredType & val() const;
  
private:
  // CONSTRUCTORS
  inline DPtr(const Ptr<DBase> & ptr);
  inline DPtr(Ptr<DBase> && ptr);
  // FIELDS
  Ptr<DBase> ptr_;
  // FRIENDS
  template<typename StoredType, typename ... Args>
  friend DPtr make_dptr(Args && ... args);
};

template<typename StoredType, typename ... Args>
DPtr make_dptr(Args && ... args);

template<typename StoredType>
StoredType & val(const DPtr & ptr);


// implementation
DPtr::operator bool() const {return nonempty();}

void DPtr::detach() {ptr_.detach();}

void DPtr::detach_receive(const DPtr & ptr) {ptr_.detach_receive(ptr.ptr_);}

template<typename NewStoredType, typename ... Args>
void DPtr::detach_set(Args && ... args) {ptr_.detach_set<DDeriv<NewStoredType>>(std::forward<Args>(args) ...);}

void DPtr::detach_unset() {ptr_.detach_unset();}

void DPtr::receive(const DPtr & ptr) const {ptr_.receive(ptr.ptr_);}

template<typename NewStoredType, typename ... Args>
void DPtr::set(Args && ... args) const {ptr_.set<DDeriv<NewStoredType>>(std::forward<Args>(args) ...);}

void DPtr::swap(const DPtr & ptr) const {ptr_.swap(ptr.ptr_);}

void DPtr::unset() const {ptr_.unset();}

DPtr DPtr::clone() const {return ptr_.clone();}

void DPtr::send(const DPtr & ref) const {ptr_.send(ref.ptr_);}

bool DPtr::empty() const {return ptr_.empty();}

bool DPtr::nonempty() const {return ptr_.nonempty();}

template<typename StoredType>
StoredType & DPtr::val() const {return ptr_.val<DDeriv<StoredType>>().value;}

DPtr::DPtr(const Ptr<DBase> & ptr)
  : ptr_(ptr) {}

DPtr::DPtr(Ptr<DBase> && ptr)
  : ptr_(std::move(ptr)) {}

template<typename StoredType, typename ... Args>
DPtr make_dptr(Args && ... args) {return make_ptr<DBase, DDeriv<StoredType>>(std::forward<Args>(args)...);}

template<typename StoredType>
StoredType & val(const DPtr & ptr) {return ptr.val<StoredType>();}

} // namespace type_abuse
} // namespace pm

#endif
