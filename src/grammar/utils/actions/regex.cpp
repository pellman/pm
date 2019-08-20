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
#include "pm/grammar/utils/actions/regex.hpp"

//#include <cstddef>
#include <utility>
//#include "pm/regex/data_context.hpp"
//#include "pm/regex/regex.hpp"
#include "pm/regex/utils/parser.hpp"
//#include "pm/utility/optional.hpp"

//#include "pm/grammar/utils/action.hpp"
#include "pm/grammar/utils/parser.hpp"

namespace pm {
namespace grammar {
namespace utils {

namespace {

// core
class ParserRegex
  : public Parser {
public:
  ParserRegex(regex::utils::ParserPtr ptr, utility::Optional<size_t> data_index);
  bool match(stream::Stream & is, set::Set & ds) const override;

private:
  const regex::utils::ParserPtr ptr_;
  const utility::Optional<size_t> data_index_;
};

// core implementation
ParserRegex::ParserRegex(regex::utils::ParserPtr ptr, utility::Optional<size_t> data_index)
  : ptr_(std::move(ptr)),
    data_index_(std::move(data_index)) {}

bool ParserRegex::match(stream::Stream & is, set::Set & context) const {
  regex::DataContext re_context;
  if(data_index_.nonempty()) {
    re_context.flag = true;
    re_context.dcur.swap(context.data(data_index_.val()));
  }
  bool res = ptr_->match(is, re_context);
  if(data_index_.nonempty()) {
    re_context.dcur.swap(context.data(data_index_.val()));
  }
  return res;
}

} // namespace

// interface
Action re(regex::Regex r, utility::Optional<size_t> data_index) {
  return new ParserRegex(std::move(r).ptr(), std::move(data_index));
}

} // namespace utils
} // namespace grammar
} // namespace pm
