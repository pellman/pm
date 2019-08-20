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
#include "pm/grammar/utils/actions/choose.hpp"

//#include <cstddef>
#include <utility>
//#include <vector>

//#include "pm/grammar/utils/action.hpp"
#include "pm/grammar/utils/parser.hpp"

namespace pm {
namespace grammar {
namespace utils {

namespace {

// core
class ParserChoose
  : public Parser {
public:
  ParserChoose(size_t data_index, std::vector<ParserPtr> ptrseq);
  bool match(stream::Stream & is, set::Set & ds) const override;

private:
  const size_t data_index_;
  const std::vector<ParserPtr> ptrseq_;
};

// implementation
ParserChoose::ParserChoose(size_t data_index, std::vector<ParserPtr> ptrseq)
  : data_index_(data_index),
    ptrseq_(std::move(ptrseq)) {}

bool ParserChoose::match(stream::Stream & is, set::Set & ds) const {
  size_t choice = ds.data(data_index_).val<size_t>();
  if(choice >= ptrseq_.size()) {
    return false;
  }
  return ptrseq_[choice]->match(is, ds);
}

} // namespace

// interface
Action choose(size_t data_index, std::vector<Action> aseq) {
  std::vector<ParserPtr> ptrseq;
  ptrseq.reserve(aseq.size());
  for(auto & a : aseq) {
    ptrseq.push_back(std::move(a).ptr());
  }
  return new ParserChoose(data_index, std::move(ptrseq));
}

} // namespace utils
} // namespace grammar
} // namespace pm
