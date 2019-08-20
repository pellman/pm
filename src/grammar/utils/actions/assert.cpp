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
#include "pm/grammar/utils/actions/assert.hpp"

//#include <cstddef>

//#include "pm/grammar/utils/action.hpp"
#include "pm/grammar/utils/parser.hpp"

namespace pm {
namespace grammar {
namespace utils {

namespace {

// core
class ParserAssert
  : public Parser {
public:
  ParserAssert(size_t data_index);
  bool match(stream::Stream & is, set::Set & ds) const override;

private:
  const size_t data_index_;
};

// implementation
ParserAssert::ParserAssert(size_t data_index)
  : data_index_(data_index) {}

bool ParserAssert::match(stream::Stream &, set::Set & ds) const {
  return ds.data(data_index_).val<bool>();
}

} // namespace

// interface
Action assert(size_t data_index) {
  return new ParserAssert(data_index);
}

} // namespace utils
} // namespace grammar
} // namespace pm
