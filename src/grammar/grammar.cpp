/*
    This file is part of the pm library package.
    Copyright (C) 2017-2019 Vladislav Podymov

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
#include "pm/grammar/grammar.hpp"

//#include <cstddef>
//#include <map>
//#include <memory>
//#include <string>
//#include <utility>
//#include "pm/regex/regex.hpp"
#include "pm/regex/utils/parser.hpp"
//#include "pm/set/domain.hpp"
#include "pm/set/set.hpp"
//#include "pm/stream/stream.hpp"
#include "pm/utility/optional.hpp"

//#include "pm/grammar/definition.hpp"
//#include "pm/grammar/nonterminal.hpp"
//#include "pm/grammar/utils/interpret_info.hpp"
//#include "pm/grammar/utils/model.hpp"

namespace pm {
namespace grammar {

class ReAction
  : public regex::utils::Parser {
public:
  // DEFAULTS
  // ReAction() deleted
  // CONSTRUCTORS
  ReAction(utils::ModelPtr model, size_t index, utility::Optional<size_t> data_index)
    : model_(std::move(model)),
      index_(index),
      data_index_(std::move(data_index)) {}
  // PRESERVING METHODS
  bool match(stream::Stream & is, regex::DataContext & context) const override {
    set::Set ds;
    if(data_index_.nonempty()) {
      ds.data(data_index_.val()) = context.dcur;
    }
    bool res = (*model_)[index_].match(is, ds);
    if(res && data_index_.nonempty() && context.flag) {
      context.dcur.swap(ds.data(data_index_.val()));
    }
    return res;
  }

private:
  // FIELDS
  const utils::ModelPtr model_;
  const size_t index_;
  const utility::Optional<size_t> data_index_;
};

void Grammar::set_skip(regex::Regex r) {
  ii_.skip = std::move(r);
}

void Grammar::synchronize() {
  ii_.action_map.clear();
  ii_.data_domain.clear();
  for(auto & defelem : definitions) {
    defelem.second.update(defelem.first, *model_ptr_, ii_);
  }
}

void Grammar::unset_skip() {
  ii_.skip.unset();
}

bool Grammar::has_data(const std::string & data_name) const {
  return ii_.data_domain.contains(data_name);
}

bool Grammar::has_nt(const std::string & nt_name) const {
  return ii_.action_map.find(nt_name) != ii_.action_map.end();
}

bool Grammar::has_skip() const {
  return ii_.skip.nonempty();
}

set::Domain Grammar::data_domain() const {
  return ii_.data_domain;
}

size_t Grammar::data_index(const std::string & data_name) const {
  return ii_.data_domain.index(data_name);
}

Nonterminal Grammar::nt(const std::string & nt_name) const {
  auto it = ii_.action_map.find(nt_name);
  if(it != ii_.action_map.end()) {
    return {model_ptr_, it->second};
  }
  else {
    return Nonterminal();
  }
}

std::map<std::string, Nonterminal> Grammar::nt_map() const {
  std::map<std::string, Nonterminal> res;
  for(const auto & ac_elem : ii_.action_map) {
    res[ac_elem.first] = Nonterminal(model_ptr_, ac_elem.second);
  }
  return res;
}

regex::Regex Grammar::re(const std::string & nt_name) const {
  auto it = ii_.action_map.find(nt_name);
  if(it != ii_.action_map.end()) {
    return new ReAction(model_ptr_, it->second, {});
  }
  else {
    return regex::Regex();
  }
}

regex::Regex Grammar::re(const std::string & nt_name, const std::string & data_name) const {
  if(ii_.data_domain.contains(data_name)) {
    auto it = ii_.action_map.find(nt_name);
    if(it != ii_.action_map.end()) {
      return new ReAction(model_ptr_, it->second, {ii_.data_domain.index(data_name)});
    }
    else {
      return regex::Regex();
    }
  }
  else {
    return re(nt_name);
  }
}

} // namespace grammar
} // namespace pm
