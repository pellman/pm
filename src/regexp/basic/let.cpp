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
#include "regexp/basic/let.hpp"

namespace pm {
namespace regexp {

bool Let::match_full(stream::Stream & stream, Context & context) const {
  char c;
  if(!stream.get(c)) {
    return false;
  }
  if(c != good_char_) {
    stream.unget(c);
    return false;
  }
  if(context.asc.is_active()) {
    context.string() += good_char_;
  }
  if(context.adc.is_active()) {
    context.adc.dc.set<char>(good_char_);
  }
  return true;
}

} // namespace regexp
} // namespace pm
