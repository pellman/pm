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
#ifndef __PM_GRAMMAR_SUBCONTEXT_ADATASET_HPP
#define __PM_GRAMMAR_SUBCONTEXT_ADATASET_HPP

#include <cstddef>
#include "pm/dataset/set.hpp"
#include "pm/regexp/subcontext/activator.hpp"

namespace pm {
namespace grammar {
namespace subcontext {

class ADataSet {
public:
  // ALTERING METHODS
  inline void detach();
  inline void detach_receive(const ADataSet & cadataset);
  inline void detach_unset(bool act);
  // PRESERVING METHODS
  // = alter subcontexts =
  inline void activate() const;
  inline void deactivate() const;
  inline void receive(const ADataSet & cadataset) const;
  inline void swap(const ADataSet & cadataset) const;
  inline void unset(bool act) const;
  // = preserve subcontexts =
  inline ADataSet clone() const;
  inline void send(const ADataSet & cadataset) const;
  // ACCESS METHODS
  inline bool active() const;
  inline const type_abuse::DPtr & data(size_t i) const;
  inline bool inactive() const;
  template<typename StoredType>
  StoredType & val(size_t i) const;
  // FIELDS
  regexp::subcontext::Activator cact;
  dataset::Set cds;
};


// implementation
void ADataSet::detach() {
  cact.detach();
  cds.detach();
}

void ADataSet::detach_receive(const ADataSet & cadataset) {
  cact.detach_receive(cadataset.cact);
  cds.detach_receive(cadataset.cds);
}

void ADataSet::detach_unset(bool act) {
  cact.detach_set(act);
  cds.detach_unset();
}

void ADataSet::activate() const {cact.activate();}

void ADataSet::deactivate() const {cact.deactivate();}

void ADataSet::receive(const ADataSet & cadataset) const {
  cact.receive(cadataset.cact);
  cds.receive(cadataset.cds);
}

void ADataSet::swap(const ADataSet & cadataset) const {
  cact.swap(cadataset.cact);
  cds.swap(cadataset.cds);
}

void ADataSet::unset(bool act) const {
  cact.set(act);
  cds.unset();
}

ADataSet ADataSet::clone() const {return {cact.clone(), cds.clone()};}

void ADataSet::send(const ADataSet & cadataset) const {
  cact.send(cadataset.cact);
  cds.send(cadataset.cds);
}

bool ADataSet::active() const {return cact.val();}

const type_abuse::DPtr & ADataSet::data(size_t i) const {return cds.data(i);}

bool ADataSet::inactive() const {return !cact.val();}

template<typename StoredType>
StoredType & ADataSet::val(size_t i) const {return cds.val<StoredType>(i);}

} // namespace subcontext
} // namespace grammar
} // namespace pm

#endif // ADATASET_HPP
