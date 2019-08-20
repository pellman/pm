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
#include "pm/grammar/utils/actions/constants.hpp"

//#include "pm/grammar/utils/action.hpp"
#include "pm/grammar/utils/parser.hpp"

namespace pm {
namespace grammar {
namespace utils {

namespace {

// core
class ParserAFalse
  : public Parser {
public:
  bool match(stream::Stream &, set::Set &) const override {
    return false;
  }
};

class ParserATrue
  : public Parser {
public:
  bool match(stream::Stream &, set::Set &) const override {
    return true;
  }
};

} // namespace

// interface
Action afalse() {
  return new ParserAFalse();
}
Action atrue() {
  return new ParserATrue();
}

} // namespace utils
} // namespace grammar
} // namespace pm
