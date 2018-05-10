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
#ifndef __PM_GRAMMAR_SYNTAX_ACTIONS_REGEXP_HPP
#define __PM_GRAMMAR_SYNTAX_ACTIONS_REGEXP_HPP

#include <string>
#include "pm/regexp/regexp.hpp"
#include "pm/grammar/syntax/action.hpp"

namespace pm {
namespace grammar {
namespace syntax {

Action ac(const regexp::Regexp & r);
Action ac(regexp::Regexp && r);
Action ac(const regexp::Regexp & r, const std::string & data_name);
Action ac(const regexp::Regexp & r, std::string && data_name);
Action ac(regexp::Regexp && r, const std::string & data_name);
Action ac(regexp::Regexp && r, std::string && data_name);

} // namespace syntax
} // namespace grammar
} // namespace pm

namespace pm {
namespace regexp {

grammar::syntax::Action operator >>(const Regexp & r, const std::string & data_name);
grammar::syntax::Action operator >>(const Regexp & r, std::string && data_name);
grammar::syntax::Action operator >>(Regexp && r, const std::string & data_name);
grammar::syntax::Action operator >>(Regexp && r, std::string && data_name);

} // namespace regexp
} // namespace pm

#endif
