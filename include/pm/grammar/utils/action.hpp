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
#ifndef PM_GRAMMAR_UTILS_ACTION_HPP
#define PM_GRAMMAR_UTILS_ACTION_HPP

//#include "pm/set/set.hpp"
//#include "pm/stream/stream.hpp"

#include "pm/grammar/utils/parser.hpp"

namespace pm {
namespace grammar {
namespace utils {

class Action {
public:
  // DEFAULTS
  Action();
  Action(Parser * ptr);
  // PRESERVING METHODS
  bool match(stream::Stream & is, set::Set & context) const;
  ParserPtr ptr() &&;

private:
  // FIELDS
  ParserPtr ptr_;
};

} // namespace utils
} // namespace grammar
} // namespace pm

#endif