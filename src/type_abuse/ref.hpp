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
#ifndef __TYPE_ABUSE_REF_HPP
#define __TYPE_ABUSE_REF_HPP

#include <memory>
#include <utility>

namespace pm {
namespace type_abuse {

// TODO: receive from "&&" without copy
// умный указатель на не более чем один разделяемый объект типа с клонируемой базой BaseType
// клонируемый тип: содержит метод BaseType & clone(), возвращающий указатель на копию объекта
// важная особенность: если указатель ни на кого не указывает, то это "ничто" разделяется между всеми указателями и изменяется у -всех- при создании объекта
template<typename Base>
class Ref {
public:
  // DEFAULTS
  Ref();
  // CONSTRUCTORS
  Ref(Base * ptr);
  // OPERATORS
  Base * operator ->() const;
  Base & operator *() const;
  operator bool() const;
  // ALTERING METHODS
  void detach();
  void detach_own(Base * ptr);
  void detach_receive(const Ref<Base> & ref);
  template<typename Value = Base, typename ... Args>
  void detach_set(Args && ... args);
  void detach_unset();
  // PRESERVING METHODS
  // = alter pointed object =
  void own(Base * ptr) const;
  void receive(const Ref<Base> & ref) const;
  template<typename Value = Base, typename ... Args>
  void set(Args && ... args) const;
  void swap(const Ref<Base> & ref) const;
  void swap(std::unique_ptr<Base> & ptr) const;
  void unset() const;
  // = preserve pointed object =
  Ref<Base> clone() const;
  // ACCESS METHODS
  bool empty() const;
  Base * get() const;
  Base * get_copy() const;
  bool nonempty() const;
  template<typename Value = Base>
  Value & val() const;
  // STATIC METHODS
  template<typename Value = Base, typename ... Args>
  static Ref<Base> create(Args && ... args);

private:
  // METHODS
  std::unique_ptr<Base> & uptr_() const;
  // FIELDS
  std::shared_ptr<std::unique_ptr<Base>> ptr_;
};


// IMPLEMENTATION
template<typename Base>
Ref<Base>::Ref()
  : ptr_(new std::unique_ptr<Base>()) {}

template<typename Base>
Ref<Base>::Ref(Base * ptr)
  : ptr_(new std::unique_ptr<Base>(ptr)) {}

template<typename Base>
Base * Ref<Base>::operator ->() const {return get();}

template<typename Base>
Base & Ref<Base>::operator *() const {return val();}

template<typename Base>
void Ref<Base>::detach() {*this = clone();}

template<typename Base>
void Ref<Base>::detach_own(Base * ptr) {ptr_.reset(new std::unique_ptr<Base>(ptr));}

template<typename Base>
void Ref<Base>::detach_receive(const Ref<Base> & ref) {
  if(ref.empty()) {
    detach_unset();
  }
  else {
    detach_own(ref.get_copy());
  }
}

template<typename Base>
Ref<Base>::operator bool() const {return nonempty();}

template<typename Base>
template<typename Value, typename ... Args>
void Ref<Base>::detach_set(Args && ... args) {ptr_.reset(new std::unique_ptr<Base>(new Value(std::forward<Args>(args) ...)));}

template<typename Base>
void Ref<Base>::detach_unset() {ptr_.reset(new std::unique_ptr<Base>());}

template<typename Base>
void Ref<Base>::own(Base * ptr) const {uptr_().reset(ptr);}

template<typename Base>
void Ref<Base>::receive(const Ref<Base> & ref) const {
  if(ref.empty()) {
    unset();
  }
  else {
    own(ref.get_copy());
  }
}

template<typename Base>
template<typename Value, typename ... Args>
void Ref<Base>::set(Args && ... args) const {own(new Value(std::forward<Args>(args) ...));}

template<typename Base>
void Ref<Base>::swap(const Ref<Base> & ref) const {swap(ref.uptr_());}

template<typename Base>
void Ref<Base>::swap(std::unique_ptr<Base> & ptr) const {uptr_().swap(ptr);}

template<typename Base>
void Ref<Base>::unset() const {uptr_().reset();}

template<typename Base>
Ref<Base> Ref<Base>::clone() const {return empty() ?  Ref() : Ref(get_copy());}

template<typename Base>
bool Ref<Base>::empty() const {return !nonempty();}

template<typename Base>
Base * Ref<Base>::get() const {return uptr_().get();}

template<typename Base>
Base * Ref<Base>::get_copy() const {return uptr_()->clone();}

template<typename Base>
bool Ref<Base>::nonempty() const {return static_cast<bool>(uptr_());}

template<typename Base>
template<typename Value>
Value & Ref<Base>::val() const {return *static_cast<Value *>(uptr_().get());}

template<typename Base>
template<typename Value, typename ... Args>
Ref<Base> Ref<Base>::create(Args && ... args) {return new Value(std::forward<Args>(args) ...);}

template<typename Base>
std::unique_ptr<Base> & Ref<Base>::uptr_() const {return *ptr_;}

} // namespace type_abuse
} // namespace pm

#endif
