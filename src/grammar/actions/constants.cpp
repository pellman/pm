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
#include "pm/grammar/actions.hpp"

namespace pm {
namespace grammar {

namespace {

// core
class ATrue
  : public ActionInterface {
public:
  // PRESERVING METHODS
  bool gamatch_full(stream::Stream & s, const Grammar & g, const Context & gcontext) const override;
};

// core implementation
bool ATrue::gamatch_full(stream::Stream &, const Grammar &, const Context &) const {return true;}

} // namespace

// interface
Action ac_false() {return {};}
Action ac_true() {return new ATrue();}

} // namespace grammar
} // namespace pm
