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
#ifndef PM_PARSER_HPP
#define PM_PARSER_HPP

#include <memory>

#include "pm/context.hpp"
#include "pm/stream.hpp"

#include "pm/devel/parser/base.hpp"

namespace pm {

class Parser {
public:
  Parser();
  Parser(devel::parser::Base * ptr);
  bool parse(Stream & is, Context & con) const;
private:
  std::shared_ptr<devel::parser::Base> ptr_;
};

} // namespace pm

#endif
