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
#ifndef __PM_GRAMMAR_ACTIONS_HPP
#define __PM_GRAMMAR_ACTIONS_HPP

#include <cstddef>
#include <list>
#include "pm/dataset/function.hpp"
#include "pm/regexp/regexp.hpp"
#include "pm/grammar/action.hpp"

namespace pm {
namespace grammar {

// functions
Action ac(const dataset::Function & f);
Action ac(dataset::Function && f);
Action ac(size_t index, const dataset::Function & f_fail);
Action ac(size_t index, dataset::Function && f_fail);

// regexp
Action ac(const regexp::Regexp & r);
Action ac(regexp::Regexp && r);
Action ac(const regexp::Regexp & r, size_t data_index);
Action ac(regexp::Regexp && r, size_t data_index);

// redirect
Action ac(size_t index);

// constants
Action ac_false();
Action ac_true();

// alternative
Action alt(const std::list<size_t> & indexes);
Action alt(std::list<size_t> && indexes);
template<typename ... Indexes>
Action alt(Indexes ... indexes);

// opt
Action opt(size_t index);

// rule
Action rule(const std::list<size_t> & indexes);
Action rule(std::list<size_t> && indexes);
template<typename ... Indexes>
Action rule(Indexes ... indexes);

// star
Action star(size_t index);


// implementation
template<typename ... Indexes>
Action alt(Indexes ... indexes) {return alt(std::list<size_t>{indexes ...});}

template<typename ... Indexes>
Action rule(Indexes ... indexes) {return alt(std::list<size_t>{indexes ...});}

} // namespace grammar
} // namespace pm

#endif
