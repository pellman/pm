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

#include <string>
//#include <utility>
#include "pm/regexp/subcontext/activator.hpp"
#include "pm/type_abuse/sptr.hpp"
#include "pm/type_abuse/dptr.hpp"

namespace pm {
namespace regexp {

class Context {
public:
  // ALTERING METHODS
  void detach();
  void detach_receive(const Context & context);
  void detach_unset();
  // PRESERVING METHODS
  // = alter data =
  void receive(const Context & context) const;
  void swap(const Context & context) const;
  void unset() const;
  // = preserve data =
  inline Context clone() const;
  void send(const Context & context) const;
  // ACCESS METHODS
  // = flags =
  inline bool & data_flag() const;
  inline bool & string_flag() const;
  // = generated data =
  template<typename T>
  T & current_data() const;
  template<typename T>
  T & saved_data() const;
  inline std::string & str() const;
  // FIELDS
  // = flags =
  subcontext::Activator p_data_flag;
  subcontext::Activator p_string_flag;
  // = generated data =
  type_abuse::DPtr p_current_data;
  type_abuse::DPtr p_saved_data;
  type_abuse::SPtr<std::string> p_string;
};

extern Context default_context; // TODO: should be "const", but cannot be due to defects of earlier C++ standard versions; defects were fixed, but still persist in commonly-used versions of clang


// implementation
Context Context::clone() const {return {p_data_flag.clone(), p_string_flag.clone(), p_current_data.clone(), p_saved_data.clone(), p_string.clone()};}

bool & Context::data_flag() const {return p_data_flag.val();}

bool & Context::string_flag() const {return p_string_flag.val();}

template<typename T>
T & Context::current_data() const {return p_current_data.val<T>();}

template<typename T>
T & Context::saved_data() const {return p_saved_data.val<T>();}

std::string & Context::str() const {return p_string.val();}

} // namespace regexp
} // namespace pm

#endif

