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
#include "pm/regex/expressions/flow/concat.hpp"

#include <utility>
//#include <vector>

//#include "pm/regex/regex.hpp"
#include "pm/regex/utils/parser.hpp"

namespace pm {
namespace regex {

namespace {

// core
class ParserConcat
  : public utils::Parser {
public:
  ParserConcat(std::vector<utils::ParserPtr> ptrseq);
  bool match(stream::Stream & is, DataContext & context) const override;

private:
  const std::vector<utils::ParserPtr> ptrseq_;
};

// core implementation
ParserConcat::ParserConcat(std::vector<utils::ParserPtr> ptrseq)
  : ptrseq_(std::move(ptrseq)) {}

bool ParserConcat::match(stream::Stream & is, DataContext & context) const {
  DataContext aux_context(context.flag
                          ? context
                          : DataContext()
                         );
  stream::Stream nis = is;
  for(const auto & ptr : ptrseq_) {
    if(!ptr->match(nis, aux_context)) {
      return false;
    }
  }
  if(context.flag) {
    context.dcur.swap(aux_context.dcur);
    context.dacc.swap(aux_context.dacc);
  }
  is.reposition(nis.pos());
  return true;
}

} // namespace

// interface
Regex concat(std::vector<Regex> rseq) {
  std::vector<utils::ParserPtr> ptrseq;
  ptrseq.reserve(rseq.size());
  for(auto & r : rseq) {
    ptrseq.push_back(std::move(r).ptr());
  }
  return new ParserConcat(std::move(ptrseq));
}

} // namespace regex
} // namespace pm
