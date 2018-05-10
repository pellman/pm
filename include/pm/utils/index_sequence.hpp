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
#ifndef __PM_UTILS_INDEX_SEQUENCE_HPP
#define __PM_UTILS_INDEX_SEQUENCE_HPP

#include <cstddef>

namespace pm {
namespace utils {

// USAGE
//   SeqGen<N> equals to the type IndSeq<0, 1, 2, ..., N-1> - use a default object of this type as a template function parameter to deduce index sequence "0, 1, 2, ..., N-1" in a parameter pack expansion

template<size_t ... indexes>
struct IndSeq {};

template<size_t size, size_t ... generated>
struct SeqGenRec : SeqGenRec<size-1, size-1, generated ...> {};

template<size_t ... generated>
struct SeqGenRec<0, generated ...> {typedef IndSeq<generated ...> seq;};

template<size_t size>
using SeqGen = typename SeqGenRec<size>::seq;

} // namespace utils
} // namespace pm

#endif
