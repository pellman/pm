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
#include "pm/type_abuse/functions.hpp"

#include <string>

namespace pm {
namespace type_abuse {

void clone(const DPtr & ptr1, const DPtr & ptr2) {ptr1.receive(ptr2);}
void swap(const DPtr & ptr1, const DPtr & ptr2) {ptr1.swap(ptr2);}
void unset(const DPtr & ptr1) {ptr1.unset();}

void char_to_string(const DPtr & ptr) {ptr.set<std::string>(1, ptr.val<char>());}

} // namespace type_abuse
} // namespace pm
