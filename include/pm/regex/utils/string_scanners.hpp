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
#ifndef PM_REGEX_UTILS_STRING_SCANNERS_HPP
#define PM_REGEX_UTILS_STRING_SCANNERS_HPP

//#include <cstddef>
#include <functional>
//#include <string>
#include "pm/stream/stream.hpp"

namespace pm {
namespace regex {
namespace utils {

std::function<bool(stream::Stream &)> str(std::string s);
std::function<bool(stream::Stream &)> len(size_t size);
std::function<bool(stream::Stream &)> future(std::string s);
std::function<bool(stream::Stream &)> optional_future(std::string s);

} // namespace utils
} // namespace regex
} // namespace pm

#endif
