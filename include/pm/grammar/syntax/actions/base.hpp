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
#ifndef __PM_GRAMMAR_SYNTAX_ACTIONS_BASE_HPP
#define __PM_GRAMMAR_SYNTAX_ACTIONS_BASE_HPP

#include <list>
#include <string>
#include <utility>
#include "pm/dataset/syntax/function.hpp"
#include "pm/regexp/regexp.hpp"
#include "pm/grammar/syntax/action.hpp"

namespace pm {
namespace grammar {
namespace syntax {

// functions
Action ac(const dataset::syntax::Function & f);
Action ac(dataset::syntax::Function && f);
Action ac(const Action & action, const dataset::syntax::Function & f_fail);
Action ac(const Action & action, dataset::syntax::Function && f_fail);
Action ac(Action && action, const dataset::syntax::Function & f_fail);
Action ac(Action && action, dataset::syntax::Function && f_fail);

// regexp
Action ac(const regexp::Regexp & r);
Action ac(regexp::Regexp && r);
Action ac(const regexp::Regexp & r, const std::string & data_name);
Action ac(const regexp::Regexp & r, std::string && data_name);
Action ac(regexp::Regexp && r, const std::string & data_name);
Action ac(regexp::Regexp && r, std::string && data_name);

// name (redirect)
Action ac(const std::string & action_name);
Action ac(std::string && action_name);

// constants
Action ac_false();
Action ac_true();

// alternative
Action alt(const std::list<Action> & actions);
Action alt(std::list<Action> && actions);
template<typename ... Actions>
Action alt(Actions && ... actions);

// opt
Action opt(const Action & a);
Action opt(Action && a);

// rule
Action rule(const std::list<Action> & actions);
Action rule(std::list<Action> && actions);
template<typename ... Actions>
Action rule(Actions && ... actions);

// star
Action star(const Action & a);
Action star(Action && a);


// implementation
template<typename ... Actions>
Action alt(Actions && ... actions) {return alt(std::list<Action>{std::forward<Actions>(actions) ...});}

template<typename ... Actions>
Action rule(Actions && ... actions) {return rule(std::list<Action>{std::forward<Actions>(actions) ...});}

} // namespace syntax
} // namespace grammar
} // namespace pm

#endif
