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
#ifndef __TYPE_ABUSE_CREF_HPP
#define __TYPE_ABUSE_CREF_HPP

#include <memory>
#include <utility>

namespace pm {
namespace type_abuse {

// умный указатель на не более чем один разделяемый объект сохраняемого типа с клонируемой базой BaseType
// сохраняемый тип: наличие/отсутствие и тип объекта не могут меняться на протяжении жизни
// клонируемый тип: содержит метод BaseType * clone(), возвращающий указатель на копию объекта
template<typename Base>
class CRef {
public:
  // DEFAULTS
  CRef() = default;
  // CONSTRUCTORS
  CRef(Base * ptr);
  // OPERATORS
  Base * operator ->() const;
  Base & operator *() const;
  operator bool() const;
  // ALTERING METHODS
  void detach();
  void detach_own(Base * ptr);
  void detach_receive(const CRef<Base> & ref);
  template<typename Value = Base, typename ... Args>
  void detach_set(Args && ... args);
  // PRESERVING METHODS
  CRef<Base> clone() const;
  // ACCRSS METHODS
  bool empty() const;
  Base * get() const;
  Base * get_copy() const;
  bool nonempty() const;
  template<typename Value = Base>
  Value & val() const;
  // STATIC METHODS
  template<typename Value = Base, typename ... Args>
  static CRef<Base> create(Args && ... args);

private:
  // FIELDS
  std::shared_ptr<Base> ptr_;
};


// IMPLEMENTATION
template<typename Base>
CRef<Base>::CRef(Base * ptr)
  : ptr_(ptr) {}

template<typename Base>
Base * CRef<Base>::operator ->() const {return get();}

template<typename Base>
Base & CRef<Base>::operator *() const {return val();}

template<typename Base>
void CRef<Base>::detach() {detach_own(get_copy());}

template<typename Base>
void CRef<Base>::detach_own(Base * ptr) {ptr_.reset(ptr);}

template<typename Base>
void CRef<Base>::detach_receive(const CRef<Base> & ref) {detach_own(ref.get_copy());}

template<typename Base>
CRef<Base>::operator bool() const {return nonempty();}

template<typename Base>
template<typename Value, typename ... Args>
void CRef<Base>::detach_set(Args && ... args) {detach_own(new Value(std::forward<Args>(args) ...));}

template<typename Base>
CRef<Base> CRef<Base>::clone() const {return empty() ? CRef() : CRef(get_copy());}

template<typename Base>
bool CRef<Base>::empty() const {return !nonempty();}

template<typename Base>
Base * CRef<Base>::get() const {return ptr_.get();}

template<typename Base>
Base * CRef<Base>::get_copy() const {return ptr_->clone();}

template<typename Base>
bool CRef<Base>::nonempty() const {return static_cast<bool>(ptr_);}

template<typename Base>
template<typename Value>
Value & CRef<Base>::val() const {return *static_cast<Value *>(get());}

template<typename Base>
template<typename Value, typename ... Args>
CRef<Base> CRef<Base>::create(Args && ... args) {return new Value(std::forward<Args>(args) ...);}

} // namespace type_abuse
} // namespace pm

#endif
