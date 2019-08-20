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
#include "pm/set/utils/functions/trivial.hpp"

#include <utility>

#include "pm/set/utils/applier.hpp"
//#include "pm/set/utils/function.hpp"

namespace pm {
namespace set {
namespace utils {

namespace {

// core
class ApplierTrivial
  : public utils::Applier {
public:
  void apply(Set &) const override {}
};

// core implementation
Function pre_trivial = {new ApplierTrivial()};

} // namespace

// interface
Function fun() {
  return pre_trivial;
}

} // namespace utils
} // namespace set
} // namespace pm
