/*
    This file is part of the pm library package.
    Copyright (C) 2017-2019 Vladislav Podymov

    This library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your Starion) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    To contact author, email to <vpod@cs.msu.ru>
 */
#include "pm/grammar/utils/actions/star.hpp"

#include <utility>

//#include "pm/grammar/utils/action.hpp"
#include "pm/grammar/utils/parser.hpp"

namespace pm {
namespace grammar {
namespace utils {

namespace {

// core
class ParserStar
  : public Parser {
public:
  ParserStar(ParserPtr ptr);
  bool match(stream::Stream & is, set::Set & ds) const override;

private:
  const ParserPtr ptr_;
};

// implementation
ParserStar::ParserStar(ParserPtr ptr)
  : ptr_(std::move(ptr)) {}

bool ParserStar::match(stream::Stream & is, set::Set & ds) const {
  while(ptr_->match(is, ds));
  return true;
}

} // namespace

// interface
Action star(Action a) {
  return new ParserStar(std::move(a).ptr());
}

} // namespace utils
} // namespace grammar
} // namespace pm
