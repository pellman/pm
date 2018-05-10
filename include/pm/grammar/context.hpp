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
#include <string>
#include "pm/dataset/set.hpp"
#include "pm/regexp/subcontext/activator.hpp"
#include "pm/type_abuse/dptr.hpp"
#include "pm/type_abuse/sptr.hpp"

namespace pm {
namespace grammar {

class Context {
public:
  // ALTERING METHODS
  void detach();
  void detach_receive(const Context & gcontext);
  void detach_unset();
  // PRESERVING METHODS
  // = alter subcontexts =
  void receive(const Context & gcontext) const;
  void swap(const Context & gcontext) const;
  void unset() const;
  // = preserve subcontexts =
  inline Context clone() const;
  void send(const Context & gcontext) const;
  // ACCESS METHODS
  // = flags =
  inline bool & data_flag() const;
  inline bool & string_flag() const;
  // = data =
  template<typename T>
  T & data(size_t i) const;
  inline const type_abuse::DPtr & ptr(size_t i) const;
  inline std::string & str() const;
  // FIELDS
  // = flags =
  regexp::subcontext::Activator p_data_flag;
  regexp::subcontext::Activator p_string_flag;
  // = data =
  dataset::Set dataset;
  type_abuse::SPtr<std::string> p_string;
};

extern Context default_context; // TODO: should be "const", but cannot be due to defects of earlier C++ standard versions; defects were fixed, but still persists in commonly-used versions of clang


// implementation
Context Context::clone() const {return {p_data_flag.clone(), p_string_flag.clone(), dataset.clone(), p_string.clone()};}

bool & Context::data_flag() const {return p_data_flag.val();}

bool & Context::string_flag() const {return p_string_flag.val();}

template<typename T>
T & Context::data(size_t i) const {return dataset.data<T>(i);}

const type_abuse::DPtr & Context::ptr(size_t i) const {return dataset.ptr(i);}

std::string & Context::str() const {return p_string.val();}

} // namespace grammar
} // namespace pm

#endif
