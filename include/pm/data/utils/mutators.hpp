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
#ifndef PM_DATA_UTILS_MUTATORS_HPP
#define PM_DATA_UTILS_MUTATORS_HPP

#include <functional>
#include <type_traits>
//#include <utility>
#include "pm/utility/pack_tricks.hpp"

#include "pm/data/data.hpp"

namespace pm {
namespace data {
namespace utils {

template<typename ... Args>
std::function<void(typename utility::replicate<Data &, Args>::type ...)> ref(std::function<void(Args ...)> f) {
  return [f = std::move(f)](typename utility::replicate<Data &, Args>::type ... dseq) {
    return f(dseq.template val<typename std::decay<Args>::type>() ...);
  };
}

template<typename Ret, typename ... Args>
std::function<void(Data &, typename utility::replicate<Data &, Args>::type ...)> ret(std::function<Ret(Args ...)> f) {
  return [f = std::move(f)](Data & d, typename utility::replicate<Data &, Args>::type ... dseq) {
    d.set<typename std::decay<Ret>::type>(f(dseq.template val<typename std::decay<Args>::type>() ...));
  };
}

} // namespace utils
} // namespace data
} // namespace pm

#endif
