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
#ifndef __PM_REGEXP_EXPRESSIONS_LAZY_COMPOSITION_HPP
#define __PM_REGEXP_EXPRESSIONS_LAZY_COMPOSITION_HPP

#include <cstddef>
#include <set>
#include <string>
#include "pm/regexp/regexp.hpp"

namespace pm {
namespace regexp {

// char -> let(char)
Regexp operator |(const Regexp & r, char c);
Regexp operator |(Regexp && r, char c);
Regexp operator |(char c, const Regexp & r);
Regexp operator |(char c, Regexp && r);
Regexp operator -(const Regexp & r, char c);
Regexp operator -(Regexp && r, char c);
Regexp operator -(char c, const Regexp & r);
Regexp operator -(char c, Regexp && r);
Regexp operator &(const Regexp & r, char c);
Regexp operator &(Regexp && r, char c);
Regexp operator &(char c, const Regexp & r);
Regexp operator &(char c, Regexp && r);

// set<char> -> let(set<char>)
Regexp operator |(const Regexp & r, const std::set<char> & s);
Regexp operator |(const Regexp & r, std::set<char> && s);
Regexp operator |(Regexp && r, const std::set<char> & s);
Regexp operator |(Regexp && r, std::set<char> && s);
Regexp operator |(const std::set<char> & s, const Regexp & r);
Regexp operator |(const std::set<char> & s, Regexp && r);
Regexp operator |(std::set<char> && s, const Regexp & r);
Regexp operator |(std::set<char> && s, Regexp && r);
Regexp operator -(const Regexp & r, const std::set<char> & s);
Regexp operator -(const Regexp & r, std::set<char> && s);
Regexp operator -(Regexp && r, const std::set<char> & s);
Regexp operator -(Regexp && r, std::set<char> && s);
Regexp operator -(const std::set<char> & s, const Regexp & r);
Regexp operator -(const std::set<char> & s, Regexp && r);
Regexp operator -(std::set<char> && s, const Regexp & r);
Regexp operator -(std::set<char> && s, Regexp && r);
Regexp operator &(const Regexp & r, const std::set<char> & s);
Regexp operator &(const Regexp & r, std::set<char> && s);
Regexp operator &(Regexp && r, const std::set<char> & s);
Regexp operator &(Regexp && r, std::set<char> && s);
Regexp operator &(const std::set<char> & s, const Regexp & r);
Regexp operator &(const std::set<char> & s, Regexp && r);
Regexp operator &(std::set<char> && s, const Regexp & r);
Regexp operator &(std::set<char> && s, Regexp && r);

// string -> str(string)
Regexp operator |(const Regexp & r, const std::string & s);
Regexp operator |(const Regexp & r, std::string && s);
Regexp operator |(Regexp && r, const std::string & s);
Regexp operator |(Regexp && r, std::string && s);
Regexp operator |(const std::string & s, const Regexp & r);
Regexp operator |(const std::string & s, Regexp && r);
Regexp operator |(std::string && s, const Regexp & r);
Regexp operator |(std::string && s, Regexp && r);
Regexp operator -(const Regexp & r, const std::string & s);
Regexp operator -(const Regexp & r, std::string && s);
Regexp operator -(Regexp && r, const std::string & s);
Regexp operator -(Regexp && r, std::string && s);
Regexp operator -(const std::string & s, const Regexp & r);
Regexp operator -(const std::string & s, Regexp && r);
Regexp operator -(std::string && s, const Regexp & r);
Regexp operator -(std::string && s, Regexp && r);
Regexp operator &(const Regexp & r, const std::string & s);
Regexp operator &(const Regexp & r, std::string && s);
Regexp operator &(Regexp && r, const std::string & s);
Regexp operator &(Regexp && r, std::string && s);
Regexp operator &(const std::string & s, const Regexp & r);
Regexp operator &(const std::string & s, Regexp && r);
Regexp operator &(std::string && s, const Regexp & r);
Regexp operator &(std::string && s, Regexp && r);

} // namespace regexp
} // namespace pm

#endif
