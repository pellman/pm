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
#ifndef PM_GRAMMAR_NONTERMINAL_HPP
#define PM_GRAMMAR_NONTERMINAL_HPP

//#include <cstddef>
//#include <iosfwd>
//#include "pm/set/set.hpp"
#include "pm/stream/stream.hpp"

#include "pm/grammar/context.hpp"
#include "pm/grammar/utils/model.hpp"

namespace pm {
namespace grammar {

class Grammar;

class Nonterminal {
public:
  // DEFAULTS
  Nonterminal();
  // PRESERVING METHODS
  bool match(std::istream & is) const;
  bool match(std::istream & is, Context & context) const;
  bool match(stream::Stream & is) const;
  bool match(stream::Stream & is, Context & context) const;
  bool match(stream::Stream & is, set::Set & ds) const;
private:
  // CONSTRUCTORS
  Nonterminal(utils::ModelPtr model_ptr, size_t index);
  // FIELDS
  utils::ModelPtr model_ptr_;
  size_t index_;
  // FRIENDS
  friend class Grammar;
};

} // namespace grammar
} // namespace pm

#endif
