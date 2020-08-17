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
#include "pm/par_system.hpp"

#include <utility>

#include "pm/devel/par_system/model.hpp"
#include "pm/devel/parser/base.hpp"

namespace pm {
namespace {

class SetParser
  : public devel::parser::Base {
public:
  SetParser(std::shared_ptr<devel::par_set::Model> base, size_t index)
    : base_(std::move(base)),
      index_(index) {}
  bool parse(Stream & is, Context & con) const override {
    return base_->parse(index_, is, con);
  }
private:
  const std::shared_ptr<devel::par_set::Model> base_;
  const size_t index_;
};

} // namespace

ParSystem::ParSystem()
  : model_(new devel::par_set::Model()) {}

ParSystem::ParSystem(ParSystem && g)
  : domain_(std::move(g.domain_)),
    model_(std::move(g.model_)) {
  g.domain_.clear();
  g.model_.reset(new devel::par_set::Model());
}

ParSystem & ParSystem::operator =(ParSystem && g) {
  domain_ = std::move(g.domain_);
  model_ = std::move(g.model_);
  g.domain_.clear();
  g.model_.reset(new devel::par_set::Model());
  return *this;
}

Parser & ParSystem::skipped(const std::string & name) {
  return model_->action(get_index_strong_(name, true));
}

Parser & ParSystem::skipped(std::string && name) {
  return model_->action(get_index_strong_(std::move(name), true));
}

Parser & ParSystem::unskipped(const std::string & name) {
  return model_->action(get_index_strong_(name, false));
}

Parser & ParSystem::unskipped(std::string && name) {
  return model_->action(get_index_strong_(std::move(name), false));
}

Parser & ParSystem::action(const std::string & name, bool skip_hint) {
  return model_->action(get_index_weak_(name, skip_hint));
}

Parser & ParSystem::action(std::string && name, bool skip_hint) {
  return model_->action(get_index_weak_(std::move(name), skip_hint));
}

Parser & ParSystem::skip() {
  return model_->skip();
}

Parser ParSystem::parser(const std::string & name, bool skip_hint) {
  return new SetParser{model_, get_index_weak_(name, skip_hint)};
}

Parser ParSystem::parser(std::string && name, bool skip_hint) {
  return new SetParser{model_, get_index_weak_(std::move(name), skip_hint)};
}

size_t ParSystem::get_index_strong_(const std::string & name, bool is_terminal) {
  const auto [it, b] = domain_.insert({name, {}});
  if(b) {
    it->second = model_->add(is_terminal);
  }
  else {
    model_->set_terminality(it->second, is_terminal);
  }
  return it->second;
}

size_t ParSystem::get_index_strong_(std::string && name, bool is_terminal) {
  const auto [it, b] = domain_.insert({std::move(name), {}});
  if(b) {
    it->second = model_->add(is_terminal);
  }
  else {
    model_->set_terminality(it->second, is_terminal);
  }
  return it->second;
}

size_t ParSystem::get_index_weak_(const std::string & name, bool is_terminal) {
  const auto [it, b] = domain_.insert({name, {}});
  if(b) {
    it->second = model_->add(is_terminal);
  }
  return it->second;
}

size_t ParSystem::get_index_weak_(std::string && name, bool is_terminal) {
  const auto [it, b] = domain_.insert({std::move(name), {}});
  if(b) {
    it->second = model_->add(is_terminal);
  }
  return it->second;
}

} // namespace pm
