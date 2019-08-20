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
#include "pm/grammar/utils/actions/alternative.hpp"

#include <utility>
//#include <vector>

//#include "pm/grammar/utils/action.hpp"
#include "pm/grammar/utils/parser.hpp"

namespace pm {
namespace grammar {
namespace utils {

namespace {

// core
class ParserAlternative
  : public Parser {
public:
  ParserAlternative(std::vector<ParserPtr> ptrseq);
  bool match(stream::Stream & is, set::Set & ds) const override;

private:
  const std::vector<ParserPtr> aseq_;
};

// core implementation
ParserAlternative::ParserAlternative(std::vector<ParserPtr> ptrseq)
  : aseq_(std::move(ptrseq)) {}

bool ParserAlternative::match(stream::Stream & is, set::Set & ds) const {
  for(const auto & ptr : aseq_) {
    if(ptr->match(is, ds)) {
      return true;
    }
  }
  return false;
}

} // namespace

// interface
Action alt(std::vector<Action> aseq) {
  std::vector<ParserPtr> ptrseq;
  ptrseq.reserve(aseq.size());
  for(auto & a : aseq) {
    ptrseq.push_back(std::move(a).ptr());
  }
  return new ParserAlternative(std::move(ptrseq));
}

} // namespace utils
} // namespace grammar
} // namespace pm
