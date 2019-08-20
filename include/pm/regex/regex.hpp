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
#ifndef PM_REGEX_REGEX_HPP
#define PM_REGEX_REGEX_HPP

//#include <iosfwd>
//#include "pm/stream/stream.hpp"

#include "pm/regex/context.hpp"
//#include "pm/regex/data_context.hpp"
#include "pm/regex/utils/parser.hpp"

namespace pm {
namespace regex {

class Regex {
public:
  // DEFAULTS
  Regex();
  Regex(utils::Parser * ptr);
  // PRESERVING METHODS
  bool match(std::istream & is) const;
  bool match(std::istream & is, Context & context) const;
  bool match(stream::Stream & is) const;
  bool match(stream::Stream & is, Context & context) const;
  bool match(stream::Stream & is, DataContext & context) const;
  utils::ParserPtr ptr() const &;
  utils::ParserPtr ptr() &&;

private:
  // FIELDS
  utils::ParserPtr ptr_;
};

} // namespace regex
} // namespace pm

#endif
