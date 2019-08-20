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
#ifndef PM_REGEX_EXPRESSIONS_FUNCTIONAL_UNIVERSAL_HPP
#define PM_REGEX_EXPRESSIONS_FUNCTIONAL_UNIVERSAL_HPP

//#include <cstddef>
#include <functional>
//#include <utility>
#include "pm/data/data.hpp"
#include "pm/utility/pack_tricks.hpp"

#include "pm/regex/regex.hpp"
//#include "pm/regex/utils/parser.hpp"

namespace pm {
namespace regex {
namespace utils {

template<typename ... Targets>
class ParserFun
  : public utils::Parser {
public:
  ParserFun(std::function<void(typename utility::replicate<data::Data &, Targets>::type ...)> f, Targets ... targets)
    : f_(std::move(f)), targets_{targets ...} {}
  bool match(stream::Stream &, DataContext & context) const override {
    if(context.flag) {
      apply_template_(std::index_sequence_for<Targets ...> {}, context);
    }
    return true;
  }

private:
  template<size_t ... indexes>
  void apply_template_(std::index_sequence<indexes ...>, DataContext & context) const {
    f_(context.data(std::get<indexes>(targets_)) ...);
  }

  const std::function<void(typename utility::replicate<data::Data &, Targets>::type ...)> f_;
  const std::array<Target, sizeof...(Targets)> targets_;
};

} // namespace utils

template<typename ... Targets>
Regex fun(std::function<void(typename utility::replicate<data::Data &, Targets>::type ...)> f, Targets ... targets) {
  return new utils::ParserFun<Targets ...>(std::move(f), targets ...);
}

} // namespace regex
} // namespace pm

#endif
