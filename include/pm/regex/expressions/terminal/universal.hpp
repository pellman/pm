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
#ifndef PM_REGEX_EXPRESSIONS_TERMINAL_UNIVERSAL_HPP
#define PM_REGEX_EXPRESSIONS_TERMINAL_UNIVERSAL_HPP

#include <functional>
//#include "pm/stream/stream.hpp"

#include "pm/regex/regex.hpp"

namespace pm {
namespace regex {

Regex trivial(std::function<bool(stream::Stream)> matcher);
Regex symbol(std::function<bool(char)> checker);
Regex str(std::function<bool(stream::Stream &)> matcher);

} // namespace regex
} // namespace pm

#endif
