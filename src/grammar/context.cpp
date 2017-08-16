/*
    This file is part of the pm library package.
    Copyright (C) 2017 Vladislav Podymov
    
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
#include "grammar/context.hpp"

namespace pm {
namespace grammar {

Context default_context(0);

void Context::detach() {
  asc.detach();
  adc.detach();
}

void Context::detach_receive(const Context & sdc) {
  asc.detach_receive(sdc.asc);
  adc.detach_receive(sdc.adc);
}

void Context::receive(const Context & sdc) const {
  asc.receive(sdc.asc);
  adc.receive(sdc.adc);
}

void Context::send(const Context & sdc) const {
  asc.send(sdc.asc);
  adc.send(sdc.adc);
}

} // namespace grammar
} // namespace pm
