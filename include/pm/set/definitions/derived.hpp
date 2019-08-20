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
#ifndef PM_SET_DEFINITIONS_DERIVED_HPP
#define PM_SET_DEFINITIONS_DERIVED_HPP

#include <utility>
//#include <vector>

//#include "pm/set/definition.hpp"
#include "pm/set/definitions/composition.hpp"

namespace pm {
namespace set {

template<typename ... Definitions>
Definition comp(Definitions && ... dseq) {
  return comp(std::vector<Definition> {std::forward<Definitions>(dseq) ...});
}
Definition operator *(Definition d1, Definition d2);

} // namespace set
} // namespace pm

#endif
