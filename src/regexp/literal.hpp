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
#ifndef __REGEXP_LITERAL_HPP
#define __REGEXP_LITERAL_HPP

#include <string>
#include <sstream>
#include <stream/stream.hpp>
#include "regexp/context.hpp"

namespace pm {
namespace regexp {

class Literal {
public:
  // DEFAULTS
  virtual ~Literal() {}
  // PRESERVING METHODS
  inline bool match(stream::Stream & stream, Context & context = default_context) const;
  inline bool match(std::istream & s, Context & context = default_context) const;
  inline bool match(const std::string & s, Context & context = default_context) const;
  inline virtual bool match_full(stream::Stream &, Context &) const;
};

extern const Literal lskip;


// IMPLEMENTATION
bool Literal::match(stream::Stream & stream, Context & context) const {return match_full(stream, context);}

bool Literal::match(std::istream & s, Context & context) const {
  stream::Stream str(s);
  return match(str, context);
}

bool Literal::match(const std::string & s, Context & context) const {
  std::stringstream str(s);
  return match(str, context);
}

bool Literal::match_full(stream::Stream &, Context &) const {return true;}

} // namespace regexp
} // namespace pm

#endif
