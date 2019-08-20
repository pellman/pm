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
#ifndef PM_SET_UTILS_FUNCTIONS_UNIVERSAL_HPP
#define PM_SET_UTILS_FUNCTIONS_UNIVERSAL_HPP

#include <array>
//#include <cstddef>
#include <functional>
//#include <utility>
#include "pm/data/data.hpp"
#include "pm/utility/pack_tricks.hpp"

//#include "pm/set/utils/applier.hpp"
#include "pm/set/utils/function.hpp"

namespace pm {
namespace set {
namespace utils {

template<typename ... SizeT>
class ApplierUniversal
  : public Applier {
public:
  ApplierUniversal(std::function<void(typename utility::replicate<data::Data &, SizeT>::type ...)> f, SizeT ... targets) : f_(std::move(f)), targets_{size_t(targets) ...} {}
  void apply(Set & ds) const override {
    apply_template_(std::index_sequence_for<SizeT ...> {}, ds);
  }
private:
  template<size_t ... indexes>
  void apply_template_(std::index_sequence<indexes ...>, Set & ds) const {
    f_(ds.data(std::get<indexes>(targets_)) ...);
  }
  const std::function<void(typename utility::replicate<data::Data &, SizeT>::type ...)> f_;
  const std::array<size_t, sizeof...(SizeT)> targets_;
};

template<typename ... SizeT>
Function fun(std::function<void(typename utility::replicate<data::Data &, SizeT>::type ... args)> f, SizeT ... targets) {
  return new ApplierUniversal<SizeT ...>(std::move(f), targets ...);
}

} // namespace utils
} // namespace set
} // namespace pm

#endif
