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
#include "regexp/composition/concat.hpp"

namespace pm {
namespace regexp {

bool Concat::match_full(stream::Stream & stream, Context & context) const {
  Context aux_context = context;
  aux_context.asc.detach_set_activate("");
  if(aux_context.adc.is_active()) {
    aux_context.adc.detach();
  }
  if(!rl1_->match_full(stream, aux_context)) {
    return false;
  }
  if(context.asc.is_inactive()) {
    aux_context.asc.ac.deactivate();
  }
  if(!rl2_->match_full(stream, aux_context)) {
    stream.unget(aux_context.string());
    return false;
  }
  if(context.asc.is_active()) {
    context.string() += aux_context.string();
  }
  if(context.adc.is_active()) {
    context.adc.dc = aux_context.adc.dc;
  }
  return true;
}

} // namespace regexp
} // namespace pm
