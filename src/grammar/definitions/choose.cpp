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
#include "pm/grammar/definitions/choose.hpp"

//#include <string>
#include <utility>
//#include <vector>

//#include "pm/grammar/definition.hpp"
#include "pm/grammar/utils/actions/choose.hpp"
#include "pm/grammar/utils/interpreter.hpp"

namespace pm {
namespace grammar {

namespace {

// core
class InterpreterChoose
  : public utils::Interpreter {
public:
  InterpreterChoose(std::string data_name, std::vector<utils::InterpreterPtr> ptrseq);
  utils::Action interpret(utils::Model & model, utils::InterpretInfo & ii) const override;
private:
  const std::string data_name_;
  const std::vector<utils::InterpreterPtr> ptrseq_;
};

// core implementation
InterpreterChoose::InterpreterChoose(std::string data_name, std::vector<utils::InterpreterPtr> ptrseq)
  : data_name_(std::move(data_name)),
    ptrseq_(std::move(ptrseq)) {}

utils::Action InterpreterChoose::interpret(utils::Model & model, utils::InterpretInfo & ii) const {
  std::vector<utils::Action> res_actions;
  res_actions.reserve(ptrseq_.size());
  for(const auto & ptr : ptrseq_) {
    res_actions.push_back(ptr->interpret(model, ii));
  }
  return utils::choose(ii.data_domain.add(data_name_), std::move(res_actions));
}

} // namespace

// interface
Definition choose(std::string data_name, std::vector<Definition> dseq) {
  std::vector<utils::InterpreterPtr> ptrseq;
  ptrseq.reserve(dseq.size());
  for(auto & d : dseq) {
    ptrseq.push_back(std::move(d).ptr());
  }
  return new InterpreterChoose(std::move(data_name), std::move(ptrseq));
}

} // namespace grammar
} // namespace pm
