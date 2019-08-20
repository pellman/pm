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
#ifndef PM_REGEX_EXPRESSIONS_FUNCTIONAL_GENERAL_HPP
#define PM_REGEX_EXPRESSIONS_FUNCTIONAL_GENERAL_HPP

//#include <functional>
//#include <utility>
#include "pm/data/utils/mutators.hpp"
//#include "pm/utility/pack_tricks.hpp"

//#include "pm/regex/regex.hpp"
#include "pm/regex/expressions/functional/universal.hpp"

namespace pm {
namespace regex {

template<typename ... Args>
Regex uref(std::function<void(Args ...)> f, typename utility::replicate<Target, Args>::type ... targets) {
  return pm::regex::fun(data::utils::ref(std::move(f)), targets ...);
}
template<typename Any, typename ... Args>
Regex ref(Any (*f)(Args ...), typename utility::replicate<Target, Args>::type ... targets) {
  return uref(std::function<void(Args ...)>(f), targets ...);
}

template<typename Ret, typename ... Args>
Regex uret(std::function<Ret(Args ...)> f, Target ret_target, typename utility::replicate<Target, Args>::type ... arg_targets) {
  return pm::regex::fun(data::utils::ret(std::move(f)), ret_target, arg_targets ...);
}
template<typename Ret, typename ... Args>
Regex ret(Ret (*f)(Args ...), Target ret_target, typename utility::replicate<Target, Args>::type ... arg_targets) {
  return uret(std::function<Ret(Args ...)>(f), ret_target, arg_targets ...);
}

template<typename Ret, typename Arg>
Regex uren(std::function<Ret(Arg)> f, Target t) {
  return uret(std::move(f), t, t);
}
template<typename Ret, typename Arg>
Regex ren(Ret (*f)(Arg), Target t) {
  return ret(f, t, t);
}

} // namespace regex
} // namespace pm

#endif
