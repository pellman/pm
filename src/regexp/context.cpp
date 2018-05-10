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
#include "pm/regexp/context.hpp"

namespace pm {
namespace regexp {

void Context::detach() {
  p_data_flag.detach();
  p_string_flag.detach();
  p_current_data.detach();
  p_saved_data.detach();
  p_string.detach();
}

void Context::detach_receive(const Context & context) {
  p_data_flag.detach_receive(context.p_data_flag);
  p_string_flag.detach_receive(context.p_string_flag);
  p_current_data.detach_receive(context.p_current_data);
  p_saved_data.detach_receive(context.p_saved_data);
  p_string.detach_receive(context.p_string);
}

void Context::detach_unset() {
  p_data_flag.detach_unset();
  p_string_flag.detach_unset();
  p_current_data.detach_unset();
  p_saved_data.detach_unset();
  p_string.detach_unset();
}

void Context::receive(const Context & context) const {
  p_data_flag.receive(context.p_data_flag);
  p_string_flag.receive(context.p_string_flag);
  p_current_data.receive(context.p_current_data);
  p_saved_data.receive(context.p_saved_data);
  p_string.receive(context.p_string);
}

void Context::swap(const Context & context) const {
  p_data_flag.swap(context.p_data_flag);
  p_string_flag.swap(context.p_string_flag);
  p_current_data.swap(context.p_current_data);
  p_saved_data.swap(context.p_saved_data);
  p_string.swap(context.p_string);
}

void Context::unset() const {
  p_data_flag.unset();
  p_string_flag.unset();
  p_current_data.unset();
  p_saved_data.unset();
  p_string.unset();
}

void Context::send(const Context & context) const {
  p_data_flag.send(context.p_data_flag);
  p_string_flag.send(context.p_string_flag);
  p_current_data.send(context.p_current_data);
  p_saved_data.send(context.p_saved_data);
  p_string.send(context.p_string);
}

Context default_context;

} // namespace regexp
} // namespace pm
