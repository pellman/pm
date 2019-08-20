/*
    This file is part of the pm library package.
    Copyright (C) 2017-2019 Vladislav Podymov

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
#ifndef PM_GRAMMAR_CONTEXT_HPP
#define PM_GRAMMAR_CONTEXT_HPP

//#include <cstddef>
//#include <string>
//#include "pm/data/data.hpp"
#include "pm/regex/string_context.hpp"
#include "pm/set/set.hpp"

namespace pm {
namespace grammar {

class Context {
public:
  // ACCESS METHODS
  data::Data & data(size_t index);
  std::string & str();
  const std::string & str() const;
  bool & string_flag();
  bool string_flag() const;
  // FIELDS
  set::Set ds;
  regex::StringContext sc;
};

} // namespace grammar
} // namespace pm

#endif
