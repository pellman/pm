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
#include "pm/grammar/syntax/actions/base.hpp"

#include "pm/utils/optional.hpp"
#include "pm/grammar/actions.hpp"
#include "pm/grammar/syntax/interpret_info.hpp"

namespace pm {
namespace grammar {
namespace syntax {

namespace {

// core
class Re
  : public ActionInterface {
public:
  // DEFAULTS
  // Re() deleted
  // CONSTRUCTORS
  Re(const regexp::Regexp & r);
  Re(regexp::Regexp && r);
  Re(const regexp::Regexp & r, const std::string & data);
  Re(const regexp::Regexp & r, std::string && data);
  Re(regexp::Regexp && r, const std::string & data);
  Re(regexp::Regexp && r, std::string && data);
  // PRESERVING METHODS
  grammar::Action interpret(grammar::Grammar & g, InterpretInfo & ii) const override;
private:
  // FIELDS
  regexp::Regexp r_;
  utils::Optional<std::string> data_;
};

// core implementation
Re::Re(const regexp::Regexp & r)
  : r_(r) {}

Re::Re(regexp::Regexp && r)
  : r_(std::move(r)) {}

Re::Re(const regexp::Regexp & r, const std::string & data)
  : r_(r), data_(data) {}

Re::Re(const regexp::Regexp & r, std::string && data)
  : r_(r), data_(std::move(data)) {}

Re::Re(regexp::Regexp && r, const std::string & data)
  : r_(std::move(r)), data_(data) {}

Re::Re(regexp::Regexp && r, std::string && data)
  : r_(std::move(r)), data_(std::move(data)) {}

grammar::Action Re::interpret(grammar::Grammar &, InterpretInfo & ii) const {
  if(data_.nonempty()) {
    return grammar::ac(r_, ii.data.add(data_.val()));
  }
  else {
    return grammar::ac(r_);
  }
}

} // namespace

// interface
Action ac(const regexp::Regexp & r) {return new Re(r);}
Action ac(regexp::Regexp && r) {return new Re(std::move(r));}
Action ac(const regexp::Regexp & r, const std::string & data) {return new Re(r, data);}
Action ac(const regexp::Regexp & r, std::string && data) {return new Re(r, std::move(data));}
Action ac(regexp::Regexp && r, const std::string & data) {return new Re(std::move(r), data);}
Action ac(regexp::Regexp && r, std::string && data) {return new Re(std::move(r), std::move(data));}

} // namespace syntax
} // namespace grammar
} // namespace pm
