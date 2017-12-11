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
#ifndef __PM_REGEXP_SUBCONTEXT_DATA_HPP
#define __PM_REGEXP_SUBCONTEXT_DATA_HPP

#include <utility>
#include "pm/type_abuse/dptr.hpp"

namespace pm {
namespace regexp {
namespace subcontext {

class Data {
public:
  // ALTERING METHODS
  inline void detach();
  inline void detach_receive(const Data & cdata);
  inline void detach_unset();
  // PRESERVING METHODS
  // = alter subcontexts =
  inline void receive(const Data & cdata) const;
  inline void swap(const Data & cdata) const;
  inline void unset() const;
  // = preserve subcontexts =
  inline Data clone() const;
  inline void send(const Data & cdata) const;
  // ACCESS METHODS
  inline type_abuse::DPtr & data();
  inline const type_abuse::DPtr & data() const;
  template<typename StoredType>
  StoredType & val() const;
  // FIELDS
  type_abuse::DPtr current;
  type_abuse::DPtr safe;
};


// implementation
void Data::detach() {
  current.detach();
  safe.detach();
}

void Data::detach_receive(const Data & cdata) {
  current.detach_receive(cdata.current);
  safe.detach_receive(cdata.safe);
}

void Data::detach_unset() {
  current.detach_unset();
  safe.detach();
}

void Data::receive(const Data & cdata) const {
  current.receive(cdata.current);
  safe.receive(cdata.safe);
}

void Data::swap(const Data & cdata) const {
  current.swap(cdata.current);
  safe.swap(cdata.safe);
}

void Data::unset() const {
  current.unset();
  safe.unset();
}

Data Data::clone() const {return {current.clone(), safe.clone()};}

void Data::send(const Data & cdata) const {
  current.send(cdata.current);
  safe.send(cdata.safe);
}

type_abuse::DPtr & Data::data() {return current;}

const type_abuse::DPtr & Data::data() const {return current;}

template<typename StoredType>
StoredType & Data::val() const {return current.val<StoredType>();}

} // namespace subcontext
} // namespace regexp
} // namespace pm

#endif
