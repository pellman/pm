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
#include "pm/set/utils/functions/composition.hpp"

#include "utility"
//#include <vector>

#include "pm/set/utils/applier.hpp"
//#include "pm/set/utils/function.hpp"

namespace pm {
namespace set {
namespace utils {

namespace {

// core
class ApplierComposition
  : public utils::Applier {
public:
  ApplierComposition(std::vector<ApplierPtr> ptrseq);
  void apply(Set & ds) const override;
private:
  const std::vector<ApplierPtr> ptrseq_;
};

// core implementation
ApplierComposition::ApplierComposition(std::vector<ApplierPtr> ptrseq)
  : ptrseq_(std::move(ptrseq)) {}

void ApplierComposition::apply(Set & ds) const {
  for(const auto & ptr : ptrseq_) {
    ptr->apply(ds);
  }
}

} // namespace

// interface
Function comp(std::vector<Function> fseq) {
  std::vector<ApplierPtr> ptrseq;
  ptrseq.reserve(fseq.size());
  for(auto & f : fseq) {
    ptrseq.push_back(std::move(f).ptr());
  }
  return new ApplierComposition(std::move(ptrseq));
}

} // namespace utils
} // namespace set
} // namespace pm
