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
#ifndef __PM_REGEXP_SUBCONTEXT_ASTRING_HPP
#define __PM_REGEXP_SUBCONTEXT_ASTRING_HPP

#include <string>
#include "pm/type_abuse/sptr.hpp"
#include "pm/regexp/subcontext/activator.hpp"

namespace pm {
namespace regexp {
namespace subcontext {

class AString {
public:
  // ALTERING METHODS
  inline void detach();
  inline void detach_receive(const AString & castr);
  template<typename ... Args>
  void detach_set(bool act, Args && ... args);
  inline void detach_unset(bool act);
  // PRESERVING METHODS
  // = alter subcontexts =
  inline void activate() const;
  inline void deactivate() const;
  inline void receive(const AString & castr) const;
  template<typename ... Args>
  void set(bool act, Args && ... args) const;
  inline void swap(const AString & castr) const;
  inline void unset(bool act) const;
  // = preserve subcontexts =
  inline AString clone() const;
  inline void send(const AString & castr) const;
  // ACCESS METHODS
  inline bool active() const;
  inline bool inactive() const;
  inline std::string & str() const;
  // FIELDS
  Activator cact;
  type_abuse::SPtr<std::string> cstr;
};


// implementation
void AString::detach() {
  cact.detach();
  cstr.detach();
}

void AString::detach_receive(const AString & castr) {
  cact.detach_receive(castr.cact);
  cstr.detach_receive(castr.cstr);
}

template<typename ... Args>
void AString::detach_set(bool act, Args && ... args) {
  cact.detach_set(act);
  cstr.detach_set(std::forward<Args>(args) ...);
}

void AString::detach_unset(bool act) {
  cact.detach_set(act);
  cstr.detach_unset();
}

void AString::activate() const {cact.activate();}

void AString::deactivate() const {cact.deactivate();}

void AString::receive(const AString & castr) const {
  cact.receive(castr.cact);
  cstr.receive(castr.cstr);
}

template<typename ... Args>
void AString::set(bool act, Args && ... args) const {
  cact.set(act);
  cstr.set(std::forward<Args>(args) ...);
}

void AString::swap(const AString & castr) const {
  cact.swap(castr.cact);
  cstr.swap(castr.cstr);
}

void AString::unset(bool act) const {
  cact.set(act);
  cstr.unset();
}

AString AString::clone() const {return {cact.clone(), cstr.clone()};}

void AString::send(const AString & castr) const {
  cact.send(castr.cact);
  cstr.send(castr.cstr);
}

bool AString::active() const {return cact.val();}

bool AString::inactive() const {return !cact.val();}

std::string & AString::str() const {return cstr.val();}

} // namespace subcontext
} // namespace regexp
} // namespace pm

#endif
