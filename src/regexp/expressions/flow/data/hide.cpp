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
#include "pm/regexp/expressions/flow/data.hpp"

#include <utility>

namespace pm {
namespace regexp {

namespace {

// core
class Hide
  : public RegexpInterface {
public:
  // DEFAULTS
  // Hide() deleted
  // CONSTRUCTORS
  Hide(const Regexp & r);
  Hide(Regexp && r);
  // PRESERVING METHODS
  bool match_full(stream::Stream & s, const Context & context) const override;

private:
  // FIELDS
  Regexp r_;
};

// core implementation
Hide::Hide(const Regexp & r)
  : r_(r) {}

Hide::Hide(Regexp && r)
  : r_(std::move(r)) {}

bool Hide::match_full(stream::Stream & s, const Context & context) const {
  type_abuse::DPtr hidden;
  hidden.swap(context.p_saved_data);
  bool res = r_.match_full(s, context);
  hidden.swap(context.p_saved_data);
  return res;
}

} // namespace

// interface
Regexp hide(const Regexp & r) {return new Hide(r);}
Regexp hide(Regexp && r) {return new Hide(std::move(r));}

} // namespace regexp
} // namespace pm
