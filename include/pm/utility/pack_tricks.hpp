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
#ifndef PM_UTILITY_PACK_TRICKS_HPP
#define PM_UTILITY_PACK_TRICKS_HPP

#include <cstddef>

namespace pm {
namespace utility {

// USAGE
//   for a type T and a type pack P, the expression
//     replicate<T, P> ...
//   equals (unpacks) to
//     T, T, ..., T
//   - as many "T"-s as the sizeof...(P)

template<typename T, typename P>
struct replicate {
  using type = T;
};

} // namespace utility
} // namespace pm

#endif
