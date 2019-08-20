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
#ifndef PM_GRAMMAR_DEFINITIONS_REGEX_HPP
#define PM_GRAMMAR_DEFINITIONS_REGEX_HPP

//#include <string>
#include "pm/regex/regex.hpp"

#include "pm/grammar/definition.hpp"

namespace pm {
namespace grammar {

Definition re(regex::Regex r);
Definition re(regex::Regex r, std::string data_name);
Definition re_noskip(regex::Regex r);
Definition re_noskip(regex::Regex r, std::string data_name);

} // namespace grammar
} // namespace pm

#endif
