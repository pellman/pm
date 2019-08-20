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
#include "pm/grammar/definitions/regex.hpp"

//#include <string>
#include <utility>
//#include "pm/regex/regex.hpp"

//#include "pm/grammar/definition.hpp"
#include "pm/grammar/utils/actions/regex.hpp"
#include "pm/grammar/utils/actions/rule.hpp"
#include "pm/grammar/utils/actions/star.hpp"
#include "pm/grammar/utils/interpreter.hpp"

namespace pm {
namespace grammar {

namespace {

// core
class InterpreterRegex
  : public utils::Interpreter {
public:
  InterpreterRegex(regex::Regex r, utility::Optional<std::string> data_name, bool has_skip);
  utils::Action interpret(utils::Model & model, utils::InterpretInfo & ii) const override;
private:
  const regex::Regex r_;
  const utility::Optional<std::string> data_name_;
  const bool has_skip_;
};

// core implementation
InterpreterRegex::InterpreterRegex(regex::Regex r, utility::Optional<std::string> data_name, bool has_skip)
  : r_(std::move(r)),
    data_name_(std::move(data_name)),
    has_skip_(has_skip) {}

utils::Action InterpreterRegex::interpret(utils::Model &, utils::InterpretInfo & ii) const {
  if(data_name_.nonempty()) {
    if(has_skip_ && ii.skip.nonempty()) {
      std::vector<utils::Action> vec;
      vec.reserve(2);
      vec.push_back(utils::star(utils::re(ii.skip.val(), {})));
      vec.push_back(utils::re(r_, ii.data_domain.add(data_name_.val())));
      return utils::rule(std::move(vec));
    }
    else {
      return utils::re(r_, ii.data_domain.add(data_name_.val()));
    }
  }
  else {
    if(has_skip_ && ii.skip.nonempty()) {
      std::vector<utils::Action> vec;
      vec.reserve(2);
      vec.push_back(utils::star(utils::re(ii.skip.val(), {})));
      vec.push_back(utils::re(r_, {}));
      return utils::rule(std::move(vec));
    }
    else {
      return utils::re(r_, {});
    }
  }
}

} // namespace

// interface
Definition re(regex::Regex r) {
  return new InterpreterRegex(std::move(r), {}, true);
}
Definition re(regex::Regex r, std::string data_name) {
  return new InterpreterRegex(std::move(r), {std::move(data_name)}, true);
}
Definition re_noskip(regex::Regex r) {
  return new InterpreterRegex(std::move(r), {}, false);
}
Definition re_noskip(regex::Regex r, std::string data_name) {
  return new InterpreterRegex(std::move(r), {std::move(data_name)}, false);
}

} // namespace grammar
} // namespace pm
