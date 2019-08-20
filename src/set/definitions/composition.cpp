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
#include "pm/set/definitions/composition.hpp"

#include <utility>
//#include <vector>

//#include "pm/set/definition.hpp"
#include "pm/set/utils/functions/composition.hpp"
#include "pm/set/utils/interpreter.hpp"

namespace pm {
namespace set {

namespace {

// core
class InterpreterComposition
  : public utils::Interpreter {
public:
  InterpreterComposition(std::vector<utils::InterpreterPtr> ptrseq);
  utils::Function interpret(Domain & dom) const override;

private:
  const std::vector<utils::InterpreterPtr> ptrseq_;
};

// core implementation
InterpreterComposition::InterpreterComposition(std::vector<utils::InterpreterPtr> ptrseq)
  : ptrseq_(std::move(ptrseq)) {}

utils::Function InterpreterComposition::interpret(Domain & dom) const {
  std::vector<utils::Function> reslist;
  reslist.reserve(ptrseq_.size());
  for(const auto & ptr : ptrseq_) {
    reslist.push_back(ptr->interpret(dom));
  }
  return utils::comp(std::move(reslist));
}

} // namespace

// interface
Definition comp(std::vector<Definition> dseq) {
  std::vector<utils::InterpreterPtr> ptrseq;
  ptrseq.reserve(dseq.size());
  for(auto & d : dseq) {
    ptrseq.push_back(std::move(d).ptr());
  }
  return new InterpreterComposition(std::move(ptrseq));
}

} // namespace set
} // namespace pm
