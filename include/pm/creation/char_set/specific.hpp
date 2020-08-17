/*
    This file is part of the pm library package.
    Copyright (C) 2017-2020 Vladislav Podymov

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
#ifndef PM_CREATION_CHAR_SET_SPECIFIC_HPP
#define PM_CREATION_CHAR_SET_SPECIFIC_HPP

#include "pm/char_set.hpp"

namespace pm::char_set {

CharSet decimal();
CharSet underscore();

} // namespace pm::char_set

namespace pm::char_set::latin {

CharSet lowercase();
CharSet uppercase();
CharSet any();

} // namespace pm::char_set::latin

namespace pm::char_set::c_id {

CharSet head();
CharSet tail();

} // namespace pm::char_set::c_id

#endif
