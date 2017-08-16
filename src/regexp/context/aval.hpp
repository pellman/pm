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
#ifndef __REGEXP_CONTEXT_AVAL_HPP
#define __REGEXP_CONTEXT_AVAL_HPP

#include <utility>
#include <type_abuse/bref.hpp>
#include "regexp/context/activator.hpp"

namespace pm {
namespace regexp {
namespace context {

template<typename Value>
class AVal {
public:
  // DEFAULTS
  // AVal() deleted
  // CONSTRUCTORS
  AVal(bool act);
  AVal(bool act, const Value & v);
  AVal(bool act, Value && v);
  AVal(const Activator & ac, const type_abuse::BRef<Value> & vc);
  AVal(const Activator & ac, type_abuse::BRef<Value> && vc);
  AVal(Activator && ac, const type_abuse::BRef<Value> & vc);
  AVal(Activator && ac, type_abuse::BRef<Value> && vc);
  // ALTERING METHODS
  void detach();
  void detach_receive(const AVal<Value> & avc);
  template<typename ... Args>
  void detach_set_activate(Args && ... args);
  template<typename ... Args>
  void detach_set_deactivate(Args && ... args);
  // PRESERVING METHODS
  // = alter subcontexts =
  void activate() const;
  void deactivate() const;
  void receive(const AVal<Value> & avc) const;
  template<typename ... Args>
  void set_activate(Args && ... args) const;
  template<typename ... Args>
  void set_deactivate(Args && ... args) const;
  // = preserve subcontexts =
  AVal<Value> clone() const;
  void send(const AVal<Value> & avc) const;
  // ACCESS METHODS
  bool is_active() const;
  bool is_inactive() const;
  Value & val() const;
  // FIELDS
  Activator ac;
  type_abuse::BRef<Value> vc;
};


// IMPLEMENTATION
template<typename Value>
AVal<Value>::AVal(bool act)
  : ac(act) {}

template<typename Value>
AVal<Value>::AVal(bool act, const Value & v)
  : ac(act),
    vc(v) {}

template<typename Value>
AVal<Value>::AVal(bool act, Value && v)
  : ac(act),
    vc(std::move(v)) {}

template<typename Value>
AVal<Value>::AVal(const Activator & ac, const type_abuse::BRef<Value> & vc)
  : ac(ac),
    vc(vc) {}

template<typename Value>
AVal<Value>::AVal(const Activator & ac, type_abuse::BRef<Value> && vc)
  : ac(ac),
    vc(std::move(vc)) {}

template<typename Value>
AVal<Value>::AVal(Activator && ac, const type_abuse::BRef<Value> & vc)
  : ac(std::move(ac)),
    vc(vc) {}

template<typename Value>
AVal<Value>::AVal(Activator && ac, type_abuse::BRef<Value> && vc)
  : ac(std::move(ac)),
    vc(std::move(vc)) {}

template<typename Value>
void AVal<Value>::detach() {
  ac.detach();
  vc.detach();
}

template<typename Value>
void AVal<Value>::detach_receive(const AVal<Value> & avc) {
  ac.detach_receive(avc.ac);
  vc.detach_receive(avc.vc);
}

template<typename Value>
template<typename ... Args>
void AVal<Value>::detach_set_activate(Args && ... args) {
  ac.detach_activate();
  vc.detach_set(std::forward<Args>(args) ...);
}

template<typename Value>
template<typename ... Args>
void AVal<Value>::detach_set_deactivate(Args && ... args) {
  ac.detach_deactivate();
  vc.detach_set(std::forward<Args>(args) ...);
}

template<typename Value>
void AVal<Value>::activate() const {
  ac.activate();
}

template<typename Value>
void AVal<Value>::deactivate() const {
  ac.deactivate();
}

template<typename Value>
void AVal<Value>::receive(const AVal<Value> & avc) const {
  ac.receive(avc.ac);
  vc.receive(avc.vc);
}

template<typename Value>
template<typename ... Args>
void AVal<Value>::set_activate(Args && ... args) const {
  ac.activate();
  vc.set(std::forward<Args>(args) ...);
}

template<typename Value>
template<typename ... Args>
void AVal<Value>::set_deactivate(Args && ... args) const {
  ac.deactivate();
  vc.set(std::forward<Args>(args) ...);
}

template<typename Value>
AVal<Value> AVal<Value>::clone() const {return {ac.clone(), vc.clone()};}

template<typename Value>
void AVal<Value>::send(const AVal<Value> & avc) const {
  ac.send(avc.ac);
  vc.send(avc.vc);
}

template<typename Value>
bool AVal<Value>::is_active() const {return ac.val();}

template<typename Value>
bool AVal<Value>::is_inactive() const {return !ac.val();}

template<typename Value>
Value & AVal<Value>::val() const {return vc.val();}

} // namespace context
} // namespace regexp
} // namespace pm

#endif
