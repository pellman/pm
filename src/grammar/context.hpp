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
#ifndef __GRAMMAR_CONTEXT_HPP
#define __GRAMMAR_CONTEXT_HPP

#include <cstddef>
#include <utility>
#include <regexp/context/astring.hpp>
#include "grammar/context/adataset.hpp"

namespace pm {
namespace grammar {

class Context {
public:
  // DEFAULTS
  // Context() deleted
  // CONSTRUCTORS
  inline Context(size_t size);
  inline Context(const regexp::context::AString & asc, const context::ADataSet & adc);
  inline Context(const regexp::context::AString & asc, context::ADataSet && adc);
  inline Context(regexp::context::AString && asc, const context::ADataSet & adc);
  inline Context(regexp::context::AString && asc, context::ADataSet && adc);
  // ALTERING METHODS
  void detach();
  void detach_receive(const Context & sdc);
  // PRESERVING METHODS
  // = alter subcontexts =
  void receive(const Context & sdc) const;
  // = preserve subcontexts =
  inline Context clone() const;
  void send(const Context & sdc) const;
  // ACCESS METHODS
  inline type_abuse::DRef & data(size_t i);
  inline const type_abuse::DRef & data(size_t i) const;
  inline size_t data_size() const;
  template<typename Value>
  Value & data_value(size_t i) const;
  inline bool is_active() const;
  inline bool is_data_empty(size_t i) const;
  inline bool is_data_nonempty(size_t i) const;
  inline bool is_inactive() const;
  inline std::string & string() const;
  // FIELDS
  regexp::context::AString asc;
  context::ADataSet adc;
};

extern Context default_context;


// IMPLEMENTATION
Context::Context(size_t size)
  : asc(false),
    adc(false, size) {}

Context::Context(const regexp::context::AString & asc, const context::ADataSet & adc)
  : asc(asc),
    adc(adc) {}

Context::Context(const regexp::context::AString & asc, context::ADataSet && adc)
  : asc(asc),
    adc(std::move(adc)) {}

Context::Context(regexp::context::AString && asc, const context::ADataSet & adc)
  : asc(std::move(asc)),
    adc(adc) {}

Context::Context(regexp::context::AString && asc, context::ADataSet && adc)
  : asc(std::move(asc)),
    adc(std::move(adc)) {}

Context Context::clone() const {return {asc.clone(), adc.clone()};}

type_abuse::DRef & Context::data(size_t i) {return adc[i];}

const type_abuse::DRef & Context::data(size_t i) const {return adc[i];}

size_t Context::data_size() const {return adc.size();}

template<typename Value>
Value & Context::data_value(size_t i) const {return adc.value<Value>(i);}

bool Context::is_active() const {return asc.is_active() || adc.is_active();}

bool Context::is_data_empty(size_t i) const {return adc.is_empty(i);}

bool Context::is_data_nonempty(size_t i) const {return adc.is_nonempty(i);}

bool Context::is_inactive() const {return asc.is_inactive() && adc.is_inactive();}

std::string & Context::string() const {return asc.val();}

} // namespace grammar
} // namespace pm

#endif
