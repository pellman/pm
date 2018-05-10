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
#ifndef __PM_TYPE_ABUSE_PTR_HPP
#define __PM_TYPE_ABUSE_PTR_HPP

#include <memory>
#include <utility>

namespace pm {
namespace type_abuse {

template<typename Base>
class Ptr {
public:
  // DEFAULTS
  Ptr();
  // CONSTRUCTORS
  Ptr(Base * ptr);
  // OPERATORS
  Base * operator ->() const;
  Base & operator *() const;
  operator bool() const;
  // ALTERING METHODS
  void detach();
  void detach_own(Base * ptr);
  void detach_receive(const Ptr<Base> & ptr);
  template<typename T = Base, typename ... Args>
  void detach_set(Args && ... args);
  void detach_unset();
  // PRESERVING METHODS
  // = alter pointed object =
  void own(Base * ptr) const;
  void receive(const Ptr<Base> & ptr) const;
  template<typename T = Base, typename ... Args>
  void set(Args && ... args) const;
  void swap(const Ptr<Base> & ptr) const;
  void swap(std::unique_ptr<Base> & ptr) const;
  void unset() const;
  // = preserve pointed object =
  Ptr<Base> clone() const;
  void send(const Ptr<Base> & ptr) const;
  // ACCESS METHODS
  bool empty() const;
  Base * get() const;
  Base * get_copy() const;
  bool nonempty() const;
  template<typename T = Base>
  T & val() const;

private:
  // METHODS
  std::unique_ptr<Base> & uptr_() const;
  // FIELDS
  std::shared_ptr<std::unique_ptr<Base>> ptr_;
};

template<typename Base, typename T = Base, typename ... Args>
Ptr<Base> make_ptr(Args && ... args) {return new T(std::forward<Args>(args) ...);}


// implementation
template<typename Base>
Ptr<Base>::Ptr()
  : ptr_(new std::unique_ptr<Base>()) {}

template<typename Base>
Ptr<Base>::Ptr(Base * ptr)
  : ptr_(new std::unique_ptr<Base>(ptr)) {}

template<typename Base>
Base * Ptr<Base>::operator ->() const {return get();}

template<typename Base>
Base & Ptr<Base>::operator *() const {return val();}

template<typename Base>
void Ptr<Base>::detach() {*this = clone();}

template<typename Base>
void Ptr<Base>::detach_own(Base * ptr) {ptr_.reset(new std::unique_ptr<Base>(ptr));}

template<typename Base>
void Ptr<Base>::detach_receive(const Ptr<Base> & ptr) {
  if(ptr.empty()) {
    detach_unset();
  }
  else {
    detach_own(ptr.get_copy());
  }
}

template<typename Base>
Ptr<Base>::operator bool() const {return nonempty();}

template<typename Base>
template<typename T, typename ... Args>
void Ptr<Base>::detach_set(Args && ... args) {detach_own(new T(std::forward<Args>(args) ...));}

template<typename Base>
void Ptr<Base>::detach_unset() {ptr_.reset(new std::unique_ptr<Base>());}

template<typename Base>
void Ptr<Base>::own(Base * ptr) const {uptr_().reset(ptr);}

template<typename Base>
void Ptr<Base>::receive(const Ptr<Base> & ptr) const {
  if(ptr.empty()) {
    unset();
  }
  else {
    own(ptr.get_copy());
  }
}

template<typename Base>
template<typename T, typename ... Args>
void Ptr<Base>::set(Args && ... args) const {own(new T(std::forward<Args>(args) ...));}

template<typename Base>
void Ptr<Base>::swap(std::unique_ptr<Base> & ptr) const {uptr_().swap(ptr);}

template<typename Base>
void Ptr<Base>::swap(const Ptr<Base> & ptr) const {swap(ptr.uptr_());}

template<typename Base>
void Ptr<Base>::unset() const {uptr_().reset();}

template<typename Base>
Ptr<Base> Ptr<Base>::clone() const {return empty() ?  Ptr() : Ptr(get_copy());}

template<typename Base>
void Ptr<Base>::send(const Ptr<Base> & ptr) const {ptr.receive(*this);}

template<typename Base>
bool Ptr<Base>::empty() const {return !nonempty();}

template<typename Base>
Base * Ptr<Base>::get() const {return uptr_().get();}

template<typename Base>
Base * Ptr<Base>::get_copy() const {return uptr_()->clone();}

template<typename Base>
bool Ptr<Base>::nonempty() const {return static_cast<bool>(uptr_());}

template<typename Base>
template<typename T>
T & Ptr<Base>::val() const {return *static_cast<T *>(uptr_().get());}

template<typename Base>
std::unique_ptr<Base> & Ptr<Base>::uptr_() const {return *ptr_;}

} // namespace type_abuse
} // namespace pm

#endif
