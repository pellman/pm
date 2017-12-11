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
#include "pm/regexp/expressions/composition.hpp"

#include <utility>

namespace pm {
namespace regexp {

namespace {

// core
class Save
  : public RegexpInterface {
public:
  // DEFAULTS
  // Save() deleted
  // CONSTRUCTORS
  Save(const Regexp & r);
  Save(Regexp && r);
  // PRESERVING METHODS
  bool match_full(stream::Stream & s, const Context & context) const override;

private:
  // FIELDS
  Regexp r_;
};

// core implementation
Save::Save(const Regexp & r)
  : r_(r) {}

Save::Save(Regexp && r)
  : r_(std::move(r)) {}

bool Save::match_full(stream::Stream & s, const Context & context) const {
  type_abuse::DPtr saved;
  saved.receive(context.cadata.cdata.safe);
  bool res = r_.match_full(s, context);
  saved.swap(context.cadata.cdata.safe);
  return res;
}

} // namespace

// interface
Regexp save(const Regexp & r) {return new Save(r);}
Regexp save(Regexp && r) {return new Save(std::move(r));}

} // namespace regexp
} // namespace pm
