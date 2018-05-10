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
#ifndef __PM_DATASET_FUNCTIONS_COMPOSITION_HPP
#define __PM_DATASET_FUNCTIONS_COMPOSITION_HPP

#include <list>
#include <utility>
#include "pm/dataset/function.hpp"

namespace pm {
namespace dataset {

Function comp(const std::list<Function> & fl);
Function comp(std::list<Function> && fl);
template<typename ... Args>
Function comp(Args && ... args) {return comp(std::list<Function>{std::forward<Args>(args) ...});}

Function operator *(const Function & f1, const Function & f2);
Function operator *(const Function & f1, Function && f2);
Function operator *(Function && f1, const Function & f2);
Function operator *(Function && f1, Function && f2);

} // namespace dataset
} // namespace pm

#endif
