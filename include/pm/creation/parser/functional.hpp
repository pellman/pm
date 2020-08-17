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
#ifndef PM_CREATION_PARSER_FUNCTIONAL_HPP
#define PM_CREATION_PARSER_FUNCTIONAL_HPP

#include <functional>

#include "pm/char_set.hpp"
#include "pm/context.hpp"
#include "pm/parser.hpp"
#include "pm/stream.hpp"

namespace pm::parser {

using FParse = std::function<bool(Stream &, Context &)>;
using FExecute = std::function<void(Stream &, Context &)>;

Parser fparse(FParse f);
Parser fexecute(FExecute f);

} // namespace pm::parser

#endif
