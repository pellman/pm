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
#include "pm/regexp/expressions/operators.hpp"

#include <utility>
#include "pm/regexp/expressions/composition.hpp"

namespace pm {
namespace regexp {

// alternative
Regexp operator |(const Regexp & r1, const Regexp & r2) {return alt(r1, r2);}
Regexp operator |(const Regexp & r1, Regexp && r2) {return alt(r1, std::move(r2));}
Regexp operator |(Regexp && r1, const Regexp & r2) {return alt(std::move(r1), r2);}
Regexp operator |(Regexp && r1, Regexp && r2) {return alt(std::move(r1), std::move(r2));}

// but
Regexp operator -(const Regexp & r1, const Regexp & r2) {return but(r1, r2);}
Regexp operator -(const Regexp & r1, Regexp && r2) {return but(r1, std::move(r2));}
Regexp operator -(Regexp && r1, const Regexp & r2) {return but(std::move(r1), r2);}
Regexp operator -(Regexp && r1, Regexp && r2) {return but(std::move(r1), std::move(r2));}

// concatenation
Regexp operator &(const Regexp & r1, const Regexp & r2) {return concat(r1, r2);}
Regexp operator &(const Regexp & r1, Regexp && r2) {return concat(r1, std::move(r2));}
Regexp operator &(Regexp && r1, const Regexp & r2) {return concat(std::move(r1), r2);}
Regexp operator &(Regexp && r1, Regexp && r2) {return concat(std::move(r1), std::move(r2));}

// star
Regexp operator *(const Regexp & r) {return star(r);}
Regexp operator *(Regexp && r) {return star(std::move(r));}

// optional
Regexp operator !(const Regexp & r) {return opt(r);}
Regexp operator !(Regexp && r) {return opt(std::move(r));}

// nodata
Regexp operator ~(const Regexp & r) {return nodata(r);}
Regexp operator ~(Regexp && r) {return nodata(std::move(r));}

} // namespace regexp
} // namespace pm
