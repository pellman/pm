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
#ifndef PM_CREATION_PARSER_COMPOSITION_HPP
#define PM_CREATION_PARSER_COMPOSITION_HPP

#include <cstddef>

#include <vector>

#include "pm/parser.hpp"

namespace pm::parser {

Parser lor(std::vector<Parser> pars);
Parser land(Parser par_main, Parser par_second);
Parser lnot(Parser par);

Parser concat(std::vector<Parser> pars);
Parser opt(Parser par);
Parser star(Parser par);

Parser ite(Parser par_test, Parser par_positive, Parser par_negative);
Parser choose(std::vector<Parser> pars, size_t data_index = 0);

Parser save_parsed(Parser par, size_t data_index = 0);
Parser scope(Parser par, std::vector<size_t> data_indexes);
Parser failsafe(Parser par);

enum class UnaryAction {
  Not,
  Opt,
  Star,
  ScopeOut,
  Failsafe
};

Parser act(Parser par, UnaryAction a);

} // namespace pm::parser

namespace pm {

// lor
Parser operator ||(Parser par_left, Parser par_right);
// land
Parser operator &&(Parser par_left, Parser par_right);
// lnot
Parser operator !(Parser par);
// concat
Parser operator &(Parser par_left, Parser par_right);
// opt
Parser operator ~(Parser par);
// star
Parser operator *(Parser par);
// choose
Parser operator /(std::vector<Parser> pars, size_t data_index);
// save_parsed
Parser operator >>(Parser par, size_t data_index);
// scope
Parser operator <<(Parser par, std::vector<size_t> data_indexes);
Parser operator <<(Parser par, size_t data_index);
Parser operator -(Parser par);
// act
Parser operator <<(Parser par, parser::UnaryAction a);

} // namespace pm

#endif
