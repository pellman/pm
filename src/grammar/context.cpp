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
#include "pm/grammar/context.hpp"

namespace pm {
namespace grammar {

void Context::detach() {
  p_data_flag.detach();
  p_string_flag.detach();
  dataset.detach();
  p_string.detach();
}

void Context::detach_receive(const Context & gcontext) {
  p_data_flag.detach_receive(gcontext.p_data_flag);
  p_string_flag.detach_receive(gcontext.p_string_flag);
  dataset.detach_receive(gcontext.dataset);
  p_string.detach_receive(gcontext.p_string);
}

void Context::detach_unset() {
  p_data_flag.detach_unset();
  p_string_flag.detach_unset();
  dataset.detach_unset();
  p_string.detach_unset();
}

void Context::receive(const Context & gcontext) const {
  p_data_flag.receive(gcontext.p_data_flag);
  p_string_flag.receive(gcontext.p_string_flag);
  dataset.receive(gcontext.dataset);
  p_string.receive(gcontext.p_string);
}

void Context::swap(const Context & gcontext) const {
  p_data_flag.swap(gcontext.p_data_flag);
  p_string_flag.swap(gcontext.p_string_flag);
  dataset.swap(gcontext.dataset);
  p_string.swap(gcontext.p_string);
}

void Context::unset() const {
  p_data_flag.unset();
  p_string_flag.unset();
  dataset.unset();
  p_string.unset();
}

void Context::send(const Context & gcontext) const {
  p_data_flag.send(gcontext.p_data_flag);
  p_string_flag.send(gcontext.p_string_flag);
  dataset.send(gcontext.dataset);
  p_string.send(gcontext.p_string);
}

Context default_context;

} // namespace grammar
} // namespace pm
