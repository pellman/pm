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
#include "pm/regexp/expressions/lazy_composition.hpp"

#include "pm/regexp/expressions/operators.hpp"
#include "pm/regexp/expressions/terminals.hpp"

namespace pm {
namespace regexp {

// char -> let(char)
Regexp operator |(const Regexp & r, char c) {return r | let(c);}
Regexp operator |(Regexp && r, char c) {return std::move(r) | let(c);}
Regexp operator |(char c, const Regexp & r) {return let(c) | r;}
Regexp operator |(char c, Regexp && r) {return let(c) | std::move(r);}
Regexp operator -(const Regexp & r, char c) {return r - let(c);}
Regexp operator -(Regexp && r, char c) {return std::move(r) - let(c);}
Regexp operator -(char c, const Regexp & r) {return let(c) - r;}
Regexp operator -(char c, Regexp && r) {return let(c) - std::move(r);}
Regexp operator &(const Regexp & r, char c) {return r & let(c);}
Regexp operator &(Regexp && r, char c) {return std::move(r) & let(c);}
Regexp operator &(char c, const Regexp & r) {return let(c) & r;}
Regexp operator &(char c, Regexp && r) {return let(c) & std::move(r);}

// set<char> -> let(set<char>)
Regexp operator |(const Regexp & r, const std::set<char> & s) {return r | let(s);}
Regexp operator |(const Regexp & r, std::set<char> && s) {return r | let(std::move(s));}
Regexp operator |(Regexp && r, const std::set<char> & s) {return std::move(r) | let(s);}
Regexp operator |(Regexp && r, std::set<char> && s) {return std::move(r) | let(std::move(s));}
Regexp operator |(const std::set<char> & s, const Regexp & r) {return let(s) | r;}
Regexp operator |(const std::set<char> & s, Regexp && r) {return let(s) | std::move(r);}
Regexp operator |(std::set<char> && s, const Regexp & r) {return let(std::move(s)) | r;}
Regexp operator |(std::set<char> && s, Regexp && r) {return let(std::move(s)) | std::move(r);}
Regexp operator -(const Regexp & r, const std::set<char> & s) {return r - let(s);}
Regexp operator -(const Regexp & r, std::set<char> && s) {return r - let(std::move(s));}
Regexp operator -(Regexp && r, const std::set<char> & s) {return std::move(r) - let(s);}
Regexp operator -(Regexp && r, std::set<char> && s) {return std::move(r) - let(std::move(s));}
Regexp operator -(const std::set<char> & s, const Regexp & r) {return let(s) - r;}
Regexp operator -(const std::set<char> & s, Regexp && r) {return let(s) - std::move(r);}
Regexp operator -(std::set<char> && s, const Regexp & r) {return let(std::move(s)) - r;}
Regexp operator -(std::set<char> && s, Regexp && r) {return let(std::move(s)) - std::move(r);}
Regexp operator &(const Regexp & r, const std::set<char> & s) {return r & let(s);}
Regexp operator &(const Regexp & r, std::set<char> && s) {return r & let(std::move(s));}
Regexp operator &(Regexp && r, const std::set<char> & s) {return std::move(r) & let(s);}
Regexp operator &(Regexp && r, std::set<char> && s) {return std::move(r) & let(std::move(s));}
Regexp operator &(const std::set<char> & s, const Regexp & r) {return let(s) & r;}
Regexp operator &(const std::set<char> & s, Regexp && r) {return let(s) & std::move(r);}
Regexp operator &(std::set<char> && s, const Regexp & r) {return let(std::move(s)) & r;}
Regexp operator &(std::set<char> && s, Regexp && r) {return let(std::move(s)) & std::move(r);}

// string -> str(string)
Regexp operator |(const Regexp & r, const std::string & s) {return r | str(s);}
Regexp operator |(const Regexp & r, std::string && s) {return r | str(std::move(s));}
Regexp operator |(Regexp && r, const std::string & s) {return std::move(r) | str(s);}
Regexp operator |(Regexp && r, std::string && s) {return std::move(r) | str(std::move(s));}
Regexp operator |(const std::string & s, const Regexp & r) {return str(s) | r;}
Regexp operator |(const std::string & s, Regexp && r) {return str(s) | std::move(r);}
Regexp operator |(std::string && s, const Regexp & r) {return str(std::move(s)) | r;}
Regexp operator |(std::string && s, Regexp && r) {return str(std::move(s)) | std::move(r);}
Regexp operator -(const Regexp & r, const std::string & s) {return r - str(s);}
Regexp operator -(const Regexp & r, std::string && s) {return r - str(std::move(s));}
Regexp operator -(Regexp && r, const std::string & s) {return std::move(r) - str(s);}
Regexp operator -(Regexp && r, std::string && s) {return std::move(r) - str(std::move(s));}
Regexp operator -(const std::string & s, const Regexp & r) {return str(s) - r;}
Regexp operator -(const std::string & s, Regexp && r) {return str(s) - std::move(r);}
Regexp operator -(std::string && s, const Regexp & r) {return str(std::move(s)) - r;}
Regexp operator -(std::string && s, Regexp && r) {return str(std::move(s)) - std::move(r);}
Regexp operator &(const Regexp & r, const std::string & s) {return r & str(s);}
Regexp operator &(const Regexp & r, std::string && s) {return r & str(std::move(s));}
Regexp operator &(Regexp && r, const std::string & s) {return std::move(r) & str(s);}
Regexp operator &(Regexp && r, std::string && s) {return std::move(r) & str(std::move(s));}
Regexp operator &(const std::string & s, const Regexp & r) {return str(s) & r;}
Regexp operator &(const std::string & s, Regexp && r) {return str(s) & std::move(r);}
Regexp operator &(std::string && s, const Regexp & r) {return str(std::move(s)) & r;}
Regexp operator &(std::string && s, Regexp && r) {return str(std::move(s)) & std::move(r);}

} // namespace regexp
} // namespace pm
