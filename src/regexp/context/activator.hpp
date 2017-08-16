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
#ifndef __REGEXP_CONTEXT_ACTIVATOR_HPP
#define __REGEXP_CONTEXT_ACTIVATOR_HPP

#include <utility>
#include <type_abuse/bref.hpp>

namespace pm {
namespace regexp {
namespace context {

class Activator
  : public type_abuse::BRef<bool> {
public:
  // DEFAULTS
  // Activator() deleted
  // CONSTRUCTORS
  inline Activator(bool act);
  // ALTERING METHODS
  inline void detach_activate();
  inline void detach_deactivate();
  // PRESERVING METHODS
  // = alter subcontexts =
  inline void activate() const;
  inline void deactivate() const;
  // = preserve subcontexts =
  inline Activator clone() const;

private:
  // CONSTRUCTORS
  inline Activator(const BRef<bool> & ref);
  inline Activator(BRef<bool> && ref);
};


// IMPLEMENTATION
Activator::Activator(bool act)
  : type_abuse::BRef<bool>(act) {}

void Activator::detach_activate() {detach_set(true);}

void Activator::detach_deactivate() {detach_set(false);}

void Activator::activate() const {val() = true;}

void Activator::deactivate() const {val() = false;}

Activator Activator::clone() const {return type_abuse::BRef<bool>::clone();}

Activator::Activator(const BRef<bool> & ref)
  : type_abuse::BRef<bool>(ref) {}

Activator::Activator(BRef<bool> && ref)
  : type_abuse::BRef<bool>(std::move(ref)) {}

} // namespace context
} // namespace regexp
} // namespace pm

#endif
