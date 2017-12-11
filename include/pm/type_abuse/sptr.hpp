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
#ifndef __PM_TYPE_ABUSE_SPTR_HPP
#define __PM_TYPE_ABUSE_SPTR_HPP

#include <memory>
#include <utility>

namespace pm {
namespace type_abuse {

template<typename Base>
class SPtr {
public:
  // DEFAULTS
  SPtr();
  // CONSTRUCTORS
  SPtr(Base * ptr);
  SPtr(const Base & obj);
  SPtr(Base && obj);
  // OPERATORS
  Base * operator ->() const;
  Base & operator *() const;
  // ALTERING METHODS
  void detach();
  void detach_own(Base * ptr);
  void detach_receive(const SPtr<Base> & ptr);
  template<typename ... Args>
  void detach_set(Args && ... args);
  void detach_unset();
  // PRESERVING METHODS
  // = alter pointed object =
  void receive(const SPtr<Base> & ptr) const;
  template<typename ... Args>
  void set(Args && ... args) const;
  void swap(Base & obj) const;
  void swap(const SPtr<Base> & ptr) const;
  void unset() const;
  // = preserve pointed object =
  SPtr<Base> clone() const;
  void send(const SPtr<Base> & ptr) const;
  // ACCESS METHODS
  Base * get() const;
  Base * get_copy() const;
  Base & val() const;

private:
  // FIELDS
  std::shared_ptr<Base> ptr_;
};

template<typename Base, typename ... Args>
SPtr<Base> make_sptr(Args && ... args);


// implementation
template<typename Base>
SPtr<Base>::SPtr()
  : SPtr(new Base()) {}

template<typename Base>
SPtr<Base>::SPtr(Base * ptr)
  : ptr_(ptr == nullptr
         ? new Base()
         : ptr
        ) {}

template<typename Base>
SPtr<Base>::SPtr(const Base & obj)
  : SPtr(new Base(obj)) {}

template<typename Base>
SPtr<Base>::SPtr(Base && obj)
  : SPtr(new Base(std::move(obj))) {}

template<typename Base>
Base * SPtr<Base>::operator ->() const {return get();}

template<typename Base>
Base & SPtr<Base>::operator *() const {return val();}

template<typename Base>
void SPtr<Base>::detach() {detach_own(get_copy());}

template<typename Base>
void SPtr<Base>::detach_own(Base * ptr) {ptr_.reset(ptr == nullptr ? new Base() : ptr);}

template<typename Base>
void SPtr<Base>::detach_receive(const SPtr<Base> & ptr) {detach_own(ptr.get_copy());}

template<typename Base>
template<typename ... Args>
void SPtr<Base>::detach_set(Args && ... args) {detach_own(new Base(std::forward<Args>(args) ...));}

template<typename Base>
void SPtr<Base>::detach_unset() {detach_own(new Base());}

template<typename Base>
void SPtr<Base>::receive(const SPtr<Base> & ptr) const {val() = ptr.val();}

template<typename Base>
template<typename ... Args>
void SPtr<Base>::set(Args && ... args) const {val() = Base(std::forward<Args>(args) ...);}

template<typename Base>
void SPtr<Base>::swap(Base & obj) const {std::swap(val(), obj);}

template<typename Base>
void SPtr<Base>::swap(const SPtr<Base> & ptr) const {swap(ptr.val());}

template<typename Base>
void SPtr<Base>::unset() const {val() = Base();}

template<typename Base>
SPtr<Base> SPtr<Base>::clone() const {return get_copy();}

template<typename Base>
void SPtr<Base>::send(const SPtr<Base> & ptr) const {ptr.receive(*this);}

template<typename Base>
Base * SPtr<Base>::get() const {return ptr_.get();}

template<typename Base>
Base * SPtr<Base>::get_copy() const {return new Base(val());}

template<typename Base>
Base & SPtr<Base>::val() const {return *ptr_;}

template<typename Base, typename ... Args>
SPtr<Base> make_sptr(Args && ... args) {return new Base(std::forward<Args>(args) ...);}

} // namespace type_abuse
} // namespace pm

#endif
