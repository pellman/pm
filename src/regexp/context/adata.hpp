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
#ifndef __REGEXP_CONTEXT_ADATA_HPP
#define __REGEXP_CONTEXT_ADATA_HPP

#include <utility>
#include <type_abuse/dref.hpp>
#include "regexp/context/activator.hpp"

namespace pm {
namespace regexp {
namespace context {

class AData {
public:
  // DEFAULTS
  // AData() deleted
  // CONSTRUCTORS
  inline AData(bool act);
  inline AData(const Activator & ac, const type_abuse::DRef & dc);
  inline AData(const Activator & ac, type_abuse::DRef && dc);
  inline AData(Activator && ac, const type_abuse::DRef & dc);
  inline AData(Activator && ac, type_abuse::DRef && dc);
  // ALTERING METHODS
  inline void detach();
  inline void detach_receive(const AData & adc);
  template<typename Value, typename ... Args>
  void detach_set_activate(Args && ... args);
  template<typename Value, typename ... Args>
  void detach_set_deactivate(Args && ... args);
  inline void detach_unset_activate();
  inline void detach_unset_deactivate();
  // PRESERVING METHODS
  // = alter subcontexts =
  inline void activate() const;
  inline void deactivate() const;
  inline void receive(const AData & adc) const;
  template<typename Value, typename ... Args>
  void set_activate(Args && ... args) const;
  template<typename Value, typename ... Args>
  void set_deactivate(Args && ... args) const;
  inline void unset_activate() const;
  inline void unset_deactivate() const;
  // = preserve subcontexts =
  inline AData clone() const;
  inline void send(const AData & adc) const;
  // ACCESS METHODS
  template<typename Value>
  Value & data() const;
  inline bool is_active() const;
  inline bool is_empty() const;
  inline bool is_inactive() const;
  inline bool is_nonempty() const;
  // FIELDS
  Activator ac;
  type_abuse::DRef dc;
};


// IMPLEMENTATION
AData::AData(bool act)
  : ac(act) {}

AData::AData(const Activator & ac, const type_abuse::DRef & dc)
  : ac(ac),
    dc(dc) {}

AData::AData(const Activator & ac, type_abuse::DRef && dc)
  : ac(ac),
    dc(std::move(dc)) {}

AData::AData(Activator && ac, const type_abuse::DRef & dc)
  : ac(std::move(ac)),
    dc(dc) {}

AData::AData(Activator && ac, type_abuse::DRef && dc)
  : ac(std::move(ac)),
    dc(std::move(dc)) {}

void AData::detach() {
  ac.detach();
  dc.detach();
}

void AData::detach_receive(const AData & adc) {
  ac.detach_receive(adc.ac);
  dc.detach_receive(adc.dc);
}

template<typename Value, typename ... Args>
void AData::detach_set_activate(Args && ... args) {
  ac.detach_activate();
  dc.detach_set<Value>(std::forward<Args>(args) ...);
}

template<typename Value, typename ... Args>
void AData::detach_set_deactivate(Args && ... args) {
  ac.detach_deactivate();
  dc.detach_set<Value>(std::forward<Args>(args) ...);
}

void AData::detach_unset_activate() {
  ac.detach_activate();
  dc.detach_unset();
}

void AData::detach_unset_deactivate() {
  ac.detach_deactivate();
  dc.detach_unset();
}

void AData::activate() const {ac.activate();}

void AData::deactivate() const {ac.deactivate();}

void AData::receive(const AData & adc) const {
  ac.receive(adc.ac);
  dc.receive(adc.dc);
}

template<typename Value, typename ... Args>
void AData::set_activate(Args && ... args) const {
  ac.activate();
  dc.set<Value>(std::forward<Args>(args) ...);
}

template<typename Value, typename ... Args>
void AData::set_deactivate(Args && ... args) const {
  ac.deactivate();
  dc.set<Value>(std::forward<Args>(args) ...);
}

void AData::unset_activate() const {
  ac.activate();
  dc.unset();
}

void AData::unset_deactivate() const {
  ac.deactivate();
  dc.unset();
}

AData AData::clone() const {return {ac.clone(), dc.clone()};}

void AData::send(const AData & adc) const {
  ac.send(adc.ac);
  dc.send(adc.dc);
}

template<typename Value>
Value & AData::data() const {return dc.val<Value>();}

bool AData::is_active() const {return ac.val();}

bool AData::is_empty() const {return dc.empty();}

bool AData::is_inactive() const {return !ac.val();}

bool AData::is_nonempty() const {return dc.nonempty();}

} // namespace context
} // namespace regexp
} // namespace pm

#endif
