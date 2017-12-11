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
#ifndef __PM_REGEXP_EXPRESSIONS_COMPOSITION_HPP
#define __PM_REGEXP_EXPRESSIONS_COMPOSITION_HPP

#include <list>
#include <utility>
#include "pm/regexp/regexp.hpp"

namespace pm {
namespace regexp {

// = parse flow =
// == alternatives: match till first success ==
Regexp alt(const std::list<Regexp> & rl);
Regexp alt(std::list<Regexp> && rl);
template<typename ... Args>
Regexp alt(Args && ... args);
// == accept positive, if it is not matched by negative ==
Regexp but(const Regexp & positive, const Regexp & negative);
Regexp but(const Regexp & positive, Regexp && negative);
Regexp but(Regexp && positive, const Regexp & negative);
Regexp but(Regexp && positive, Regexp && negative);
// == concatenation: match all consecutively ==
Regexp concat(const std::list<Regexp> & rl);
Regexp concat(std::list<Regexp> && rl);
template<typename ... Args>
Regexp concat(Args && ... args);
// == optional: try to match, accept anyway ==
Regexp opt(const Regexp & r);
Regexp opt(Regexp && r);
// == Kleene star: match over and over until fail, accept anyway ==
Regexp star(const Regexp & r);
Regexp star(Regexp && r);

// = data manipulation =
// == hide accumulated data ==
Regexp hide(const Regexp & r);
Regexp hide(Regexp && r);
// == do not generate subexpression data ==
Regexp nodata(const Regexp & r);
Regexp nodata(Regexp && r);
// == save accumulated data ==
Regexp save(const Regexp & r);
Regexp save(Regexp && r);


// implementation
template<typename ... Args>
Regexp alt(Args && ... args) {return alt(std::list<Regexp>{std::forward<Args>(args) ...});}

template<typename ... Args>
Regexp concat(Args && ... args) {return concat(std::list<Regexp>{std::forward<Args>(args) ...});}

} // namespace regexp
} // namespace pm

#endif
