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
#include "pm/regex/expressions/flow/alt.hpp"

#include <utility>
//#include <vector>

//#include "pm/regex/regex.hpp"
#include "pm/regex/utils/parser.hpp"

namespace pm {
namespace regex {

namespace {

// core
class ParserAlt
  : public utils::Parser {
public:
  ParserAlt(std::vector<utils::ParserPtr> ptrseq);
  bool match(stream::Stream & is, DataContext & context) const override;

private:
  const std::vector<utils::ParserPtr> ptrseq_;
};

// core implementation
ParserAlt::ParserAlt(std::vector<utils::ParserPtr> ptrseq)
  : ptrseq_(std::move(ptrseq)) {}

bool ParserAlt::match(stream::Stream & is, DataContext & context) const {
  for(const auto & ptr : ptrseq_) {
    if(ptr->match(is, context)) {
      return true;
    }
  }
  return false;
}

} // namespace

// interface
Regex alt(std::vector<Regex> rseq) {
  std::vector<utils::ParserPtr> ptrseq;
  ptrseq.reserve(rseq.size());
  for(auto & r : rseq) {
    ptrseq.push_back(std::move(r).ptr());
  }
  return new ParserAlt(std::move(ptrseq));
}

} // namespace regex
} // namespace pm
