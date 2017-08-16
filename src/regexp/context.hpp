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
#ifndef __REGEXP_CONTEXT_HPP
#define __REGEXP_CONTEXT_HPP

#include <utility>
#include "regexp/context/adata.hpp"
#include "regexp/context/astring.hpp"

namespace pm {
namespace regexp {

class Context {
public:
  // DEFAULTS
  inline Context();
  // CONSTRUCTORS
  inline Context(const context::AString & asc, const context::AData & adc);
  inline Context(const context::AString & asc, context::AData && adc);
  inline Context(context::AString && asc, const context::AData & adc);
  inline Context(context::AString && asc, context::AData && adc);
  // ALTERING METHODS
  inline void detach();
  inline void detach_receive(const Context & sdc);
  // PRESERVING METHODS
  // = alter subcontexts =
  inline void receive(const Context & sdc) const;
  // = preserve subcontexts =
  inline Context clone() const;
  inline void send(const Context & sdc) const;
  // ACCESS METHODS
  template<typename Value>
  Value & data() const;
  inline bool is_active() const;
  inline bool is_empty() const;
  inline bool is_inactive() const;
  inline bool is_nonempty() const;
  inline std::string & string() const;
  // FIELDS
  context::AString asc;
  context::AData adc;
};

extern Context default_context;


// IMPLEMENTATION
Context::Context()
  : asc(false),
    adc(false) {}

Context::Context(const context::AString & asc, const context::AData & adc)
  : asc(asc),
    adc(adc) {}

Context::Context(const context::AString & asc, context::AData && adc)
  : asc(asc),
    adc(std::move(adc)) {}

Context::Context(context::AString && asc, const context::AData & adc)
  : asc(std::move(asc)),
    adc(adc) {}

Context::Context(context::AString && asc, context::AData && adc)
  : asc(std::move(asc)),
    adc(std::move(adc)) {}

void Context::detach() {
  asc.detach();
  adc.detach();
}

void Context::detach_receive(const Context & sdc) {
  asc.detach_receive(sdc.asc);
  adc.detach_receive(sdc.adc);
}

void Context::receive(const Context & sdc) const {
  asc.receive(sdc.asc);
  adc.receive(sdc.adc);
}

Context Context::clone() const {return {asc.clone(), adc.clone()};}

void Context::send(const Context & sdc) const {
  asc.send(sdc.asc);
  adc.send(sdc.adc);
}

template<typename Value>
Value & Context::data() const {return adc.data<Value>();}

bool Context::is_active() const {return asc.is_active() || adc.is_active();}

bool Context::is_empty() const {
  return adc.is_empty();
}

bool Context::is_inactive() const {return asc.is_inactive() && adc.is_inactive();}

bool Context::is_nonempty() const {return adc.is_nonempty();}

std::string & Context::string() const {return asc.val();}

} // namespace regexp
} // namespace pm

#endif
