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
#ifndef __GRAMMAR_CONTEXT_ADATASET_HPP
#define __GRAMMAR_CONTEXT_ADATASET_HPP

#include <cstddef>
#include <utility>
#include <dataset/set.hpp>
#include <regexp/context/activator.hpp>
#include <type_abuse/dref.hpp>

namespace pm {
namespace grammar {
namespace context {

class ADataSet {
public:
  // DEFAULTS
  // ADataSet() deleted
  // CONSTRUCTORS
  inline ADataSet(bool act, size_t size);
  inline ADataSet(const regexp::context::Activator & act, const dataset::Set & set);
  inline ADataSet(const regexp::context::Activator & act, dataset::Set & set);
  inline ADataSet(regexp::context::Activator & act, const dataset::Set & set);
  inline ADataSet(regexp::context::Activator & act, dataset::Set & set);
  // OPERATORS
  inline type_abuse::DRef & operator [](size_t i);
  inline const type_abuse::DRef & operator [](size_t i) const;
  // ALTERING METHODS
  void detach();
  void detach_receive(const ADataSet & adc);
  void detach_unset_activate();
  void detach_unset_deactivate();
  // PRESERVING METHODS
  // = alter subcontexts =
  void receive(const ADataSet & adc) const;
  void unset_activate() const;
  void unset_deactivate() const;
  // = preserve subcontexts =
  inline ADataSet clone() const;
  void send(const ADataSet & adc) const;
  // ACCESS METHODS
  inline type_abuse::DRef & at(size_t i);
  inline const type_abuse::DRef & at(size_t i) const;
  inline bool is_active() const;
  inline bool is_empty(size_t i) const;
  inline bool is_inactive() const;
  inline bool is_nonempty(size_t i) const;
  inline size_t size() const;
  template<typename Value>
  Value & value(size_t i) const;
  // FIELDS
  regexp::context::Activator ac;
  dataset::Set dc;
};


// IMPLEMENTATION
ADataSet::ADataSet(bool act, size_t size)
  : ac(act),
    dc(size) {}

ADataSet::ADataSet(const regexp::context::Activator & act, const dataset::Set & set)
  : ac(act),
    dc(set) {}

ADataSet::ADataSet(const regexp::context::Activator & act, dataset::Set & set)
  : ac(act),
    dc(std::move(set)) {}

ADataSet::ADataSet(regexp::context::Activator & act, const dataset::Set & set)
  : ac(std::move(act)),
    dc(set) {}

ADataSet::ADataSet(regexp::context::Activator & act, dataset::Set & set)
  : ac(std::move(act)),
    dc(std::move(set)) {}

type_abuse::DRef & ADataSet::operator [](size_t i) {return dc[i];}

const type_abuse::DRef & ADataSet::operator [](size_t i) const {return dc[i];}

ADataSet ADataSet::clone() const {return {ac.clone(), dc.clone()};}

type_abuse::DRef & ADataSet::at(size_t i) {return dc.at(i);}

const type_abuse::DRef & ADataSet::at(size_t i) const {return dc.at(i);}

bool ADataSet::is_active() const {return ac.val();}

bool ADataSet::is_empty(size_t i) const {return dc[i].empty();}

bool ADataSet::is_inactive() const {return !ac.val();}

bool ADataSet::is_nonempty(size_t i) const {return dc[i].nonempty();}

size_t ADataSet::size() const {return dc.size();}

template<typename Value>
Value & ADataSet::value(size_t i) const {return dc[i].val<Value>();}

} // namespace context
} // namespace grammar
} // namespace pm

#endif // ADATASET_HPP
