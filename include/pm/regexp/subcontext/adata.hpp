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
#ifndef __PM_REGEXP_SUBCONTEXT_ADATA_HPP
#define __PM_REGEXP_SUBCONTEXT_ADATA_HPP

#include <utility>
#include "pm/regexp/subcontext/activator.hpp"
#include "pm/regexp/subcontext/data.hpp"

namespace pm {
namespace regexp {
namespace subcontext {

class AData {
public:
  // ALTERING METHODS
  inline void detach();
  inline void detach_receive(const AData & cadata);
  inline void detach_unset(bool act);
  // PRESERVING METHODS
  // = alter subcontexts =
  inline void activate() const;
  inline void deactivate() const;
  inline void receive(const AData & cadata) const;
  inline void swap(const AData & cadata) const;
  inline void unset(bool act) const;
  // = preserve subcontexts =
  inline AData clone() const;
  inline void send(const AData & cadata) const;
  // ACCESS METHODS
  inline bool active() const;
  inline type_abuse::DPtr & data();
  inline const type_abuse::DPtr & data() const;
  inline bool inactive() const;
  template<typename StoredType>
  StoredType & val() const;
  // FIELDS
  Activator cact;
  Data cdata;
};


// implementation
void AData::detach() {
  cact.detach();
  cdata.detach();
}

void AData::detach_receive(const AData & cadata) {
  cact.detach_receive(cadata.cact);
  cdata.detach_receive(cadata.cdata);
}

void AData::detach_unset(bool act) {
  cact.detach_set(act);
  cdata.detach_unset();
}

void AData::activate() const {cact.activate();}

void AData::deactivate() const {cact.deactivate();}

void AData::receive(const AData & cadata) const {
  cact.receive(cadata.cact);
  cdata.receive(cadata.cdata);
}

void AData::swap(const AData & cadata) const {
  cact.swap(cadata.cact);
  cdata.swap(cadata.cdata);
}

void AData::unset(bool act) const {
  cact.set(act);
  cdata.unset();
}

AData AData::clone() const {return {cact.clone(), cdata.clone()};}

void AData::send(const AData & cadata) const {
  cact.send(cadata.cact);
  cdata.send(cadata.cdata);
}

bool AData::active() const {return cact.val();}

type_abuse::DPtr & AData::data() {return cdata.data();}

const type_abuse::DPtr & AData::data() const {return cdata.data();}

bool AData::inactive() const {return !cact.val();}

template<typename StoredType>
StoredType & AData::val() const {return cdata.val<StoredType>();}

} // namespace subcontext
} // namespace regexp
} // namespace pm

#endif
