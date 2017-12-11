/*
    This file is part of the pm library package.
    Copyright (C) 2017, 2018 Vladislav Podymov
    
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
#ifndef __PM_DATASET_FUNCTIONS_LAZY_HPP
#define __PM_DATASET_FUNCTIONS_LAZY_HPP

#include <utility>
#include "pm/type_abuse/mutators.hpp"
#include "pm/dataset/functions/base.hpp"
#include "pm/dataset/function.hpp"

namespace pm {
namespace dataset {

template<typename ... Args, typename ... Targets>
Function dref(const std::function<void(Args ...)> & f, Targets ... targets);
template<typename ... Args, typename ... Targets>
Function dref(std::function<void(Args ...)> && f, Targets ... targets);
template<typename Ret, typename ... Args, typename ... Targets>
Function dren(const std::function<Ret(Args ...)> & f, Targets ... targets);
template<typename Ret, typename ... Args, typename ... Targets>
Function dren(std::function<Ret(Args ...)> && f, Targets ... targets);
template<typename Ret, typename ... Args, typename ... Targets>
Function dret(const std::function<Ret(Args ...)> & f, Targets ... targets);
template<typename Ret, typename ... Args, typename ... Targets>
Function dret(std::function<Ret(Args ...)> && f, Targets ... targets);

template<typename Any, typename ... Args, typename ... Targets>
Function dgref(Any (*f)(Args ...), Targets ... targets);
template<typename Ret, typename ... Args, typename ... Targets>
Function dgren(Ret (*f)(Args ...), Targets ... targets);
template<typename Ret, typename ... Args, typename ... Targets>
Function dgret(Ret (*f)(Args ...), Targets ... targets);


// implementation
template<typename ... Args, typename ... Targets>
Function dref(const std::function<void(Args ...)> & f, Targets ... targets) {return dfun(type_abuse::mutator_ref(f), targets ...);}
template<typename ... Args, typename ... Targets>
Function dref(std::function<void(Args ...)> && f, Targets ... targets) {return dfun(type_abuse::mutator_ref(std::move(f)), targets ...);}
template<typename Ret, typename ... Args, typename ... Targets>
Function dren(const std::function<Ret(Args ...)> & f, Targets ... targets) {return dfun(type_abuse::mutator_ren(f), targets ...);}
template<typename Ret, typename ... Args, typename ... Targets>
Function dren(std::function<Ret(Args ...)> && f, Targets ... targets) {return dfun(type_abuse::mutator_ren(std::move(f)), targets ...);}
template<typename Ret, typename ... Args, typename ... Targets>
Function dret(const std::function<Ret(Args ...)> & f, Targets ... targets) {return dfun(type_abuse::mutator_ret(f), targets ...);}
template<typename Ret, typename ... Args, typename ... Targets>
Function dret(std::function<Ret(Args ...)> && f, Targets ... targets) {return dfun(type_abuse::mutator_ret(std::move(f)), targets ...);}

template<typename Any, typename ... Args, typename ... Targets>
Function dgref(Any (*f)(Args ...), Targets ... targets) {return dref(std::function<void(Args ...)>(f), targets ...);}
template<typename Ret, typename ... Args, typename ... Targets>
Function dgren(Ret (*f)(Args ...), Targets ... targets) {return dren(std::function<Ret(Args ...)>(f), targets ...);}
template<typename Ret, typename ... Args, typename ... Targets>
Function dgret(Ret (*f)(Args ...), Targets ... targets) {return dret(std::function<Ret(Args ...)>(f), targets ...);}

} // namespace dataset
} // namespace pm

#endif
