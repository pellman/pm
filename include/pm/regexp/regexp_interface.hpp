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
#ifndef __PM_REGEXP_REGEXP_INTERFACE_HPP
#define __PM_REGEXP_REGEXP_INTERFACE_HPP

#include <string>
#include <sstream>
#include "pm/stream/stream.hpp"
#include "pm/regexp/context.hpp"

namespace pm {
namespace regexp {

class RegexpInterface {
public:
  // DEFAULTS
  virtual ~RegexpInterface() {}
  // PRESERVING METHODS
  inline bool match(stream::Stream & s, const Context & context = default_context) const;
  inline bool match(std::istream & s, const Context & context = default_context) const;
  inline bool match(const std::string & s, const Context & context = default_context) const;
  inline virtual bool match_full(stream::Stream &, const Context &) const;
};


// implementation
bool RegexpInterface::match(stream::Stream & s, const Context & context) const {return match_full(s, context);}

bool RegexpInterface::match(std::istream & s, const Context & context) const {
  stream::Stream str(s);
  return match(str, context);
}

bool RegexpInterface::match(const std::string & s, const Context & context) const {
  std::stringstream str(s);
  return match(str, context);
}

bool RegexpInterface::match_full(stream::Stream &, const Context &) const {return false;}

} // namespace regexp
} // namespace pm

#endif
