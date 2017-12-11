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
#ifndef __PM_REGEXP_SUBCONTEXT_ACTIVATOR_HPP
#define __PM_REGEXP_SUBCONTEXT_ACTIVATOR_HPP

#include <utility>
#include "pm/type_abuse/sptr.hpp"

namespace pm {
namespace regexp {
namespace subcontext {

class Activator
  : public type_abuse::SPtr<bool> {
public:
  // DEFAULTS
  inline Activator();
  // CONSTRUCTORS
  inline Activator(bool act);
  inline Activator(const SPtr<bool> & ptr);
  inline Activator(SPtr<bool> && ptr);
  // ALTERING METHODS
  inline void detach_activate();
  inline void detach_deactivate();
  inline void detach_unset();
  // PRESERVING METHODS
  // = alter subcontexts =
  inline void activate() const;
  inline void deactivate() const;
  inline void unset() const;
  // = preserve subcontexts =
  inline Activator clone() const;
  // ACCESS METHODS
  inline bool active() const;
  inline bool inactive() const;
};


// implementation
Activator::Activator()
  : Activator(false) {}

Activator::Activator(bool act)
  : type_abuse::SPtr<bool>(act) {}

Activator::Activator(const SPtr<bool> & ptr)
  : type_abuse::SPtr<bool>(ptr) {}

Activator::Activator(SPtr<bool> && ptr)
  : type_abuse::SPtr<bool>(std::move(ptr)) {}

void Activator::detach_activate() {detach_set(true);}

void Activator::detach_deactivate() {detach_set(false);}

void Activator::detach_unset() {detach_set(false);}

void Activator::activate() const {val() = true;}

void Activator::deactivate() const {val() = false;}

void Activator::unset() const {val() = false;}

Activator Activator::clone() const {return type_abuse::SPtr<bool>::clone();}

bool Activator::active() const {return val();}

bool Activator::inactive() const {return !val();}

} // namespace subcontext
} // namespace regexp
} // namespace pm

#endif
