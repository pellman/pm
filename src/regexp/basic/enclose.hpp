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
#ifndef __REGEXP_BASIC_ENCLOSE_HPP
#define __REGEXP_BASIC_ENCLOSE_HPP

#include <cstddef>
#include <list>
#include <string>
#include <utility>
#include "regexp/literal.hpp"
#include "regexp/regexp.hpp"

namespace pm {
namespace regexp {

class Enclose
  : public Literal {
public:
  // DEFAULTS
  // Enclose() deleted
  // CONSTRUCTORS
  inline Enclose(const std::string & opening_string, const std::string & closing_string);
  inline Enclose(const std::string & opening_string, std::string && closing_string);
  inline Enclose(std::string && opening_string, const std::string & closing_string);
  inline Enclose(std::string && opening_string, std::string && closing_string);
  // PRESERVING METHODS
  bool match_full(stream::Stream & stream, Context & context) const override;

private:
  // PRESERVING METHODS
  int close_char_(stream::Stream & stream, std::string & s_popped) const;
  int close_string_(stream::Stream & stream, std::string & s_popped) const;
  bool push_char_to_prefixes_(char c, std::list<size_t> & matched_prefix_sizes) const;
  // FIELDS
  const std::string opening_string_;
  const std::string closing_string_;
};

inline Regexp enclose(const std::string & opening_string, const std::string & closing_string);
inline Regexp enclose(const std::string & opening_string, std::string && closing_string);
inline Regexp enclose(std::string && opening_string, const std::string & closing_string);
inline Regexp enclose(std::string && opening_string, std::string && closing_string);


// IMPLEMENTATION
Enclose::Enclose(const std::string & opening_string, const std::string & closing_string)
  : opening_string_(opening_string),
    closing_string_(closing_string) {}

Enclose::Enclose(const std::string & opening_string, std::string && closing_string)
  : opening_string_(opening_string),
    closing_string_(std::move(closing_string)) {}

Enclose::Enclose(std::string && opening_string, const std::string & closing_string)
  : opening_string_(std::move(opening_string)),
    closing_string_(closing_string) {}

Enclose::Enclose(std::string && opening_string, std::string && closing_string)
  : opening_string_(std::move(opening_string)),
    closing_string_(std::move(closing_string)) {}

Regexp enclose(const std::string & opening_string, const std::string & closing_string) {return type_abuse::CRef<Literal>::create<Enclose>(opening_string, closing_string);}

Regexp enclose(const std::string & opening_string, std::string && closing_string) {return type_abuse::CRef<Literal>::create<Enclose>(opening_string, std::move(closing_string));}

Regexp enclose(std::string && opening_string, const std::string & closing_string) {return type_abuse::CRef<Literal>::create<Enclose>(std::move(opening_string), closing_string);}

Regexp enclose(std::string && opening_string, std::string && closing_string) {return type_abuse::CRef<Literal>::create<Enclose>(std::move(opening_string), std::move(closing_string));}

} // namespace regexp
} // namespace pm

#endif
