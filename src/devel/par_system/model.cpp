/*
    This file is part of the pm library package.
    Copyright (C) 2017-2020 Vladislav Podymov

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
#include "pm/devel/par_system/model.hpp"

namespace pm::devel::par_set {

Model::Model(const Model & ml)
  : actions_(ml.actions_.size()),
    terminals_(ml.terminals_),
    skip_(ml.skip_) {
  for(size_t i = 0; i < ml.actions_.size(); ++i) {
    actions_[i].reset(new Parser(*ml.actions_[i]));
  }
}

Model & Model::operator =(const Model & ml) {
  terminals_ = ml.terminals_;
  skip_ = ml.skip_;
  actions_.resize(ml.actions_.size());
  for(size_t i = 0; i < ml.actions_.size(); ++i) {
    actions_[i].reset(new Parser(*ml.actions_[i]));
  }
  return *this;
}

size_t Model::add(bool is_terminal) {
  size_t res = actions_.size();
  actions_.emplace_back(new Parser());
  terminals_.push_back(is_terminal);
  return res;
}

Parser & Model::action(size_t index) {
  return *actions_[index];
}

Parser & Model::skip() {
  return skip_;
}

void Model::set_terminality(size_t index, bool is_terminal) {
  terminals_[index] = is_terminal;
}


bool Model::parse(size_t index, Stream & is, Context & con) const {
  if(terminals_[index]) {
    Stream backup_is = is;
    while(skip_.parse(is, con));
    bool res = actions_[index]->parse(is, con);
    if(!res) {
      is = backup_is;
    }
    return res;
  }
  return actions_[index]->parse(is, con);
}

} // namespace pm::devel::par_set
