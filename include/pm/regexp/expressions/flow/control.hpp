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
#ifndef __PM_REGEXP_EXPRESSIONS_FLOW_CONTROL_HPP
#define __PM_REGEXP_EXPRESSIONS_FLOW_CONTROL_HPP

#include <list>
#include <set>
#include <string>
#include <utility>
#include "pm/regexp/regexp.hpp"

namespace pm {
namespace regexp {

// = alternative: match till first success ==
// == global functions ==
Regexp alt(const std::list<Regexp> & rl);
Regexp alt(std::list<Regexp> && rl);
template<typename ... Args>
Regexp alt(Args && ... args) {return alt(std::list<Regexp>{std::forward<Args>(args) ...});}
// == operators ==
Regexp operator |(const Regexp & r1, const Regexp & r2);
Regexp operator |(const Regexp & r1, Regexp && r2);
Regexp operator |(Regexp && r1, const Regexp & r2);
Regexp operator |(Regexp && r1, Regexp && r2);
// == lazy operators: let(char) -> char ==
Regexp operator |(const Regexp & r, char c);
Regexp operator |(Regexp && r, char c);
Regexp operator |(char c, const Regexp & r);
Regexp operator |(char c, Regexp && r);
// == lazy operators: let(set<char>) -> set<char> ==
Regexp operator |(const Regexp & r, const std::set<char> & s);
Regexp operator |(const Regexp & r, std::set<char> && s);
Regexp operator |(Regexp && r, const std::set<char> & s);
Regexp operator |(Regexp && r, std::set<char> && s);
Regexp operator |(const std::set<char> & s, const Regexp & r);
Regexp operator |(const std::set<char> & s, Regexp && r);
Regexp operator |(std::set<char> && s, const Regexp & r);
Regexp operator |(std::set<char> && s, Regexp && r);
// == lazy operators: str(string) -> string ==
Regexp operator |(const Regexp & r, const std::string & s);
Regexp operator |(const Regexp & r, std::string && s);
Regexp operator |(Regexp && r, const std::string & s);
Regexp operator |(Regexp && r, std::string && s);
Regexp operator |(const std::string & s, const Regexp & r);
Regexp operator |(const std::string & s, Regexp && r);
Regexp operator |(std::string && s, const Regexp & r);
Regexp operator |(std::string && s, Regexp && r);

// = concatenation: match all consecutively =
// == global functions ==
Regexp concat(const std::list<Regexp> & rl);
Regexp concat(std::list<Regexp> && rl);
template<typename ... Args>
Regexp concat(Args && ... args) {return concat(std::list<Regexp>{std::forward<Args>(args) ...});}
// == operators ==
Regexp operator &(const Regexp & r1, const Regexp & r2);
Regexp operator &(const Regexp & r1, Regexp && r2);
Regexp operator &(Regexp && r1, const Regexp & r2);
Regexp operator &(Regexp && r1, Regexp && r2);
// == lazy operators: let(char) -> char ==
Regexp operator &(const Regexp & r, char c);
Regexp operator &(Regexp && r, char c);
Regexp operator &(char c, const Regexp & r);
Regexp operator &(char c, Regexp && r);
// == lazy operators: let(set<char>) -> set<char> ==
Regexp operator &(const Regexp & r, const std::set<char> & s);
Regexp operator &(const Regexp & r, std::set<char> && s);
Regexp operator &(Regexp && r, const std::set<char> & s);
Regexp operator &(Regexp && r, std::set<char> && s);
Regexp operator &(const std::set<char> & s, const Regexp & r);
Regexp operator &(const std::set<char> & s, Regexp && r);
Regexp operator &(std::set<char> && s, const Regexp & r);
Regexp operator &(std::set<char> && s, Regexp && r);
// == lazy operators: str(string) -> string ==
Regexp operator &(const Regexp & r, const std::string & s);
Regexp operator &(const Regexp & r, std::string && s);
Regexp operator &(Regexp && r, const std::string & s);
Regexp operator &(Regexp && r, std::string && s);
Regexp operator &(const std::string & s, const Regexp & r);
Regexp operator &(const std::string & s, Regexp && r);
Regexp operator &(std::string && s, const Regexp & r);
Regexp operator &(std::string && s, Regexp && r);

// = difference: accept positive, if it is not accepted by negative =
// == global functions ==
Regexp but(const Regexp & positive, const Regexp & negative);
Regexp but(const Regexp & positive, Regexp && negative);
Regexp but(Regexp && positive, const Regexp & negative);
Regexp but(Regexp && positive, Regexp && negative);
// == operators ==
Regexp operator -(const Regexp & r1, const Regexp & r2);
Regexp operator -(const Regexp & r1, Regexp && r2);
Regexp operator -(Regexp && r1, const Regexp & r2);
Regexp operator -(Regexp && r1, Regexp && r2);
// == lazy operators: let(char) -> char ==
Regexp operator -(const Regexp & r, char c);
Regexp operator -(Regexp && r, char c);
Regexp operator -(char c, const Regexp & r);
Regexp operator -(char c, Regexp && r);
// == lazy operators: let(set<char>) -> set<char> ==
Regexp operator -(const Regexp & r, const std::set<char> & s);
Regexp operator -(const Regexp & r, std::set<char> && s);
Regexp operator -(Regexp && r, const std::set<char> & s);
Regexp operator -(Regexp && r, std::set<char> && s);
Regexp operator -(const std::set<char> & s, const Regexp & r);
Regexp operator -(const std::set<char> & s, Regexp && r);
Regexp operator -(std::set<char> && s, const Regexp & r);
Regexp operator -(std::set<char> && s, Regexp && r);
// == lazy operators: str(string) -> string ==
Regexp operator -(const Regexp & r, const std::string & s);
Regexp operator -(const Regexp & r, std::string && s);
Regexp operator -(Regexp && r, const std::string & s);
Regexp operator -(Regexp && r, std::string && s);
Regexp operator -(const std::string & s, const Regexp & r);
Regexp operator -(const std::string & s, Regexp && r);
Regexp operator -(std::string && s, const Regexp & r);
Regexp operator -(std::string && s, Regexp && r);

// = Kleene star: match over and over until fail, accept anyway =
// == global functions ==
Regexp star(const Regexp & r);
Regexp star(Regexp && r);
// == operators ==
Regexp operator *(const Regexp & r);
Regexp operator *(Regexp && r);

// = optional: try to match, accept anyway =
// == global functions ==
Regexp opt(const Regexp & r);
Regexp opt(Regexp && r);
// == operators ==
Regexp operator !(const Regexp & r);
Regexp operator !(Regexp && r);

} // namespace regexp
} // namespace pm

#endif
