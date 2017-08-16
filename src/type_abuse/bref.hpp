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
#ifndef __TYPE_ABUSE_BREF_HPP
#define __TYPE_ABUSE_BREF_HPP

#include <memory>
#include <utility>

namespace pm {
namespace type_abuse {

// умный указатель на ровно один разделяемый объект заданного типа
template<typename Base>
class BRef {
public:
  // DEFAULTS
  BRef();
  // CONSTRUCTORS
  BRef(Base * ptr);
  BRef(const Base & v);
  BRef(Base && v);
  // OPERATORS
  Base * operator ->() const;
  Base & operator *() const;
  // ALTERING METHODS
  void detach();
  void detach_own(Base * ptr);
  void detach_receive(const BRef<Base> & ref);
  template<typename ... Args>
  void detach_set(Args && ... args);
  // PRESERVING METHODS
  // = alter pointed object =
  void receive(const BRef<Base> & ref) const;
  template<typename ... Args>
  void set(Args && ... args) const;
  // = preserve pointed object =
  BRef<Base> clone() const;
  void send(const BRef<Base> & ref) const;
  // ACCESS METHODS
  Base * get() const;
  Base * get_copy() const;
  Base & val() const;
  // STATIC METHODS
  template<typename ... Args>
  static BRef<Base> create(Args && ... args);

private:
  // FIELDS
  std::shared_ptr<Base> ptr_;
};


// IMPLEMENTATION
template<typename Base>
BRef<Base>::BRef()
  : BRef(new Base()) {}

template<typename Base>
BRef<Base>::BRef(Base * ptr)
  : ptr_(ptr == nullptr
         ? new Base()
         : ptr
        ) {}

template<typename Base>
BRef<Base>::BRef(const Base & v)
  : ptr_(new Base(v)) {}

template<typename Base>
BRef<Base>::BRef(Base && v)
  : ptr_(new Base(std::move(v))) {}

template<typename Base>
Base * BRef<Base>::operator ->() const {return get();}

template<typename Base>
Base & BRef<Base>::operator *() const {return val();}

template<typename Base>
void BRef<Base>::detach() {detach_own(get_copy());}

template<typename Base>
void BRef<Base>::detach_own(Base * ptr) {ptr_.reset(ptr);}

template<typename Base>
void BRef<Base>::detach_receive(const BRef<Base> & ref) {detach_own(ref.get_copy());}

template<typename Base>
template<typename ... Args>
void BRef<Base>::detach_set(Args && ... args) {detach_own(new Base(std::forward<Args>(args) ...));}

template<typename Base>
void BRef<Base>::receive(const BRef<Base> & ref) const {val() = ref.val();}

template<typename Base>
template<typename ... Args>
void BRef<Base>::set(Args && ... args) const {val() = Base(std::forward<Args>(args) ...);}

template<typename Base>
BRef<Base> BRef<Base>::clone() const {return get_copy();}

template<typename Base>
void BRef<Base>::send(const BRef & ref) const {ref.val() = val();}

template<typename Base>
Base * BRef<Base>::get() const {return ptr_.get();}

template<typename Base>
Base * BRef<Base>::get_copy() const {return new Base(val());}

template<typename Base>
Base & BRef<Base>::val() const {return *ptr_;}

template<typename Base>
template<typename ... Args>
BRef<Base> BRef<Base>::create(Args && ... args) {return new Base(std::forward<Args>(args) ...);}

} // namespace type_abuse
}

#endif
