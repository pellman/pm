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
#ifndef __PM_REGEXP_CONTEXT_HPP
#define __PM_REGEXP_CONTEXT_HPP

#include <utility>
#include "pm/regexp/subcontext/adata.hpp"
#include "pm/regexp/subcontext/astring.hpp"

namespace pm {
namespace regexp {

class Context {
public:
  // ALTERING METHODS
  inline void detach();
  inline void detach_receive(const Context & context);
  // PRESERVING METHODS
  // = alter subcontexts =
  inline void activate() const;
  inline void deactivate() const;
  inline void receive(const Context & context) const;
  inline void swap(const Context & context) const;
  // = preserve subcontexts =
  inline Context clone() const;
  inline void send(const Context & context) const;
  // ACCESS METHODS
  inline bool active() const;
  inline type_abuse::DPtr & data();
  inline const type_abuse::DPtr & data() const;
  inline bool inactive() const;
  inline std::string & str() const;
  template<typename StoredType>
  StoredType & val() const;
  // FIELDS
  subcontext::AString castr;
  subcontext::AData cadata;
};

extern Context default_context;


// implementation
void Context::detach() {
  castr.detach();
  cadata.detach();
}

void Context::detach_receive(const Context & context) {
  castr.detach_receive(context.castr);
  cadata.detach_receive(context.cadata);
}

void Context::activate() const {
  castr.activate();
  cadata.activate();
}

void Context::deactivate() const {
  castr.deactivate();
  cadata.deactivate();
}

void Context::receive(const Context & context) const {
  castr.receive(context.castr);
  cadata.receive(context.cadata);
}

void Context::swap(const Context & context) const {
  castr.swap(context.castr);
  cadata.swap(context.cadata);
}

Context Context::clone() const {return {castr.clone(), cadata.clone()};}

void Context::send(const Context & context) const {
  castr.send(context.castr);
  cadata.send(context.cadata);
}

bool Context::active() const {return castr.active() || cadata.active();}

type_abuse::DPtr & Context::data() {return cadata.data();}

const type_abuse::DPtr & Context::data() const {return cadata.data();}

bool Context::inactive() const {return castr.inactive() && cadata.inactive();}

std::string & Context::str() const {return castr.str();}

template<typename StoredType>
StoredType & Context::val() const {return cadata.val<StoredType>();}

} // namespace regexp
} // namespace pm

#endif

