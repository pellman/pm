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
#ifndef PM_SET_DEFINITIONS_GENERAL_HPP
#define PM_SET_DEFINITIONS_GENERAL_HPP

//#include <functional>
//#include <string>
//#include <utility>
#include "pm/data/utils/mutators.hpp"
//#include "pm/utility/pack_tricks.hpp"

//#include "pm/set/definition.hpp"
#include "pm/set/definitions/universal.hpp"

namespace pm {
namespace set {

template<typename ... Args>
Definition uref(std::function<void(Args ...)> f, typename utility::replicate<std::string, Args>::type ... names) {
  return fun(data::utils::ref(std::move(f)), std::move(names) ...);
}
template<typename Any, typename ... Args>
Definition ref(Any (*f)(Args ...), typename utility::replicate<std::string, Args>::type ... names) {
  return uref(std::function<void(Args ...)>(f), std::move(names) ...);
}

template<typename Ret, typename ... Args>
Definition uret(std::function<Ret(Args ...)> f, std::string ret_name, typename utility::replicate<std::string, Args>::type ... names) {
  return fun(data::utils::ret(std::move(f)), std::move(ret_name), std::move(names) ...);
}
template<typename Ret, typename ... Args>
Definition ret(Ret (*f)(Args ...), std::string ret_name, typename utility::replicate<std::string, Args>::type ... names) {
  return uret(std::function<Ret(Args ...)>(f), std::move(ret_name), std::move(names) ...);
}

template<typename Ret, typename Arg>
Definition uren(std::function<Ret(Arg)> f, std::string name) {
  std::string name_copy = name;
  return uret(std::move(f), std::move(name), std::move(name_copy));
}
template<typename Ret, typename Arg>
Definition ren(Ret (*f)(Arg), std::string name) {
  std::string name_copy = name;
  return ret(f, std::move(name), std::move(name_copy));
}

} // namespace set
} // namespace pm

#endif
