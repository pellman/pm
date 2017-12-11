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
#ifndef __PM_GRAMMAR_CONTEXT_HPP
#define __PM_GRAMMAR_CONTEXT_HPP

#include <cstddef>
#include "pm/regexp/subcontext/astring.hpp"
#include "pm/grammar/subcontext/adataset.hpp"

namespace pm {
namespace grammar {

class Context {
public:
  // ALTERING METHODS
  inline void detach();
  inline void detach_receive(const Context & gcontext);
  // PRESERVING METHODS
  // = alter subcontexts =
  inline void activate() const;
  inline void deactivate() const;
  inline void receive(const Context & gcontext) const;
  inline void swap(const Context & gcontext) const;
  // = preserve subcontexts =
  inline Context clone() const;
  inline void send(const Context & gcontext) const;
  // ACCESS METHODS
  inline bool active() const;
  inline const type_abuse::DPtr & data(size_t i) const;
  inline bool inactive() const;
  inline std::string & str() const;
  template<typename StoredType>
  StoredType & val(size_t i) const;
  // FIELDS
  regexp::subcontext::AString castr;
  subcontext::ADataSet cadataset;
};

extern Context default_context;


// implementation
void Context::detach() {
  castr.detach();
  cadataset.detach();
}

void Context::detach_receive(const Context & gcontext) {
  castr.detach_receive(gcontext.castr);
  cadataset.detach_receive(gcontext.cadataset);
}

void Context::activate() const {
  castr.activate();
  cadataset.activate();
}

void Context::deactivate() const {
  castr.deactivate();
  cadataset.deactivate();
}

void Context::receive(const Context & gcontext) const {
  castr.receive(gcontext.castr);
  cadataset.receive(gcontext.cadataset);
}

void Context::swap(const Context & gcontext) const {
  castr.swap(gcontext.castr);
  cadataset.swap(gcontext.cadataset);
}

Context Context::clone() const {return {castr.clone(), cadataset.clone()};}

void Context::send(const Context & gcontext) const {
  castr.send(gcontext.castr);
  cadataset.send(gcontext.cadataset);
}

bool Context::active() const {return castr.active() || cadataset.active();}

const type_abuse::DPtr & Context::data(size_t i) const {return cadataset.data(i);}

bool Context::inactive() const {return castr.inactive() && cadataset.inactive();}

std::string & Context::str() const {return castr.str();}

template<typename StoredType>
StoredType & Context::val(size_t i) const {return cadataset.val<StoredType>(i);}

} // namespace grammar
} // namespace pm

#endif
