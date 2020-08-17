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
#include "pm/creation/parser/composition.hpp"

#include <utility>

#include "pm/devel/parser/base.hpp"

namespace pm::parser {
namespace {

class Lor
  : public devel::parser::Base {
public:
  Lor(std::vector<Parser> pars)
    : pars_(std::move(pars)) {}
  bool parse(Stream & is, Context & con) const override {
    for(const auto & m : pars_) {
      if(m.parse(is, con)) {
        return true;
      }
    }
    return false;
  }
private:
  const std::vector<Parser> pars_;
};

class Land
  : public devel::parser::Base {
public:
  Land(Parser par_main, Parser par_second)
    : par_main_(std::move(par_main)),
      par_second_(std::move(par_second)) {}
  bool parse(Stream & is, Context & con) const override {
    Stream backup_is = is;
    if(!par_main_.parse(is, con)) {
      return false;
    }
    Stream right_is = backup_is.get_prefix(is.get_position());
    if(!par_second_.parse(right_is, con)) {
      is = std::move(backup_is);
      return false;
    }
    return true;
  }
private:
  const Parser par_main_, par_second_;
};

class Lnot
  : public devel::parser::Base {
public:
  Lnot(Parser par)
    : par_(std::move(par)) {}
  bool parse(Stream & is, Context & con) const override {
    Stream neg_is = is;
    return !par_.parse(neg_is, con);
  }
private:
  const Parser par_;
};

class Concat
  : public devel::parser::Base {
public:
  Concat(std::vector<Parser> pars)
    : pars_(std::move(pars)) {}
  bool parse(Stream & is, Context & con) const override {
    Stream backup_is = is;
    for(const auto & m : pars_) {
      if(!m.parse(is, con)) {
        is = std::move(backup_is);
        return false;
      }
    }
    return true;
  }
private:
  const std::vector<Parser> pars_;
};

class Opt
  : public devel::parser::Base {
public:
  Opt(Parser par)
    : par_(std::move(par)) {}
  bool parse(Stream & is, Context & con) const override {
    par_.parse(is, con);
    return true;
  }
private:
  const Parser par_;
};

class Star
  : public devel::parser::Base {
public:
  Star(Parser par)
    : par_(std::move(par)) {}
  bool parse(Stream & is, Context & con) const override {
    while(par_.parse(is, con));
    return true;
  }
private:
  const Parser par_;
};

class Ite
  : public devel::parser::Base {
public:
  Ite(Parser par_test, Parser par_positive, Parser par_negative)
    : par_test_(std::move(par_test)),
      par_positive_(std::move(par_positive)),
      par_negative_(std::move(par_negative)) {}
  bool parse(Stream & is, Context & con) const override {
    Stream backup_is = is;
    if(par_test_.parse(is, con)) {
      if(par_positive_.parse(is, con)) {
        return true;
      }
      is = std::move(backup_is);
      return false;
    }
    return par_negative_.parse(is, con);
  }
private:
  const Parser par_test_, par_positive_, par_negative_;
};

class Choose
  : public devel::parser::Base {
public:
  Choose(std::vector<Parser> pars, size_t data_index)
    : pars_(std::move(pars)),
      data_index_(data_index) {}
  bool parse(Stream & is, Context & con) const override {
    const size_t par_num = con[data_index_].value<size_t>();
    if(par_num >= pars_.size()) {
      return false;
    }
    return pars_[par_num].parse(is, con);
  }
private:
  const std::vector<Parser> pars_;
  const size_t data_index_;
};

class SaveParsed
  : public devel::parser::Base {
public:
  SaveParsed(Parser par, size_t data_index)
    : par_(std::move(par)),
      data_index_(data_index) {}
  bool parse(Stream & is, Context & con) const override {
    Stream backup_is = is;
    if(!par_.parse(is, con)) {
      return false;
    }
    con[data_index_].emplace<std::string>(backup_is.peek(is.get_position()));
    return true;
  }
private:
  const Parser par_;
  const size_t data_index_;
};

class Scope
  : public devel::parser::Base {
public:
  Scope(Parser par, std::vector<size_t> data_indexes)
    : par_(std::move(par)),
      data_indexes_(std::move(data_indexes)) {}
  bool parse(Stream & is, Context & con) const override {
    Context tmp_con(data_indexes_.size());
    con.swap(data_indexes_, tmp_con);
    bool res = par_.parse(is, tmp_con);
    con.swap(data_indexes_, tmp_con);
    return res;
  }
private:
  const Parser par_;
  const std::vector<size_t> data_indexes_;
};

class Failsafe
  : public devel::parser::Base {
public:
  Failsafe(Parser par)
    : par_(std::move(par)) {}
  bool parse(Stream & is, Context & con) const override {
    Context tmp_con = con;
    if(par_.parse(is, con)) {
      return true;
    }
    con.swap(tmp_con);
    return false;
  }
private:
  const Parser par_;
};

} // namespace

Parser lor(std::vector<Parser> pars) {
  return new Lor(std::move(pars));
}
Parser land(Parser par_main, Parser par_second) {
  return new Land(std::move(par_main), std::move(par_second));
}
Parser lnot(Parser par) {
  return new Lnot(std::move(par));
}

Parser concat(std::vector<Parser> pars) {
  return new Concat(std::move(pars));
}
Parser opt(Parser par) {
  return new Opt(std::move(par));
}
Parser star(Parser par) {
  return new Star(std::move(par));
}

Parser ite(Parser par_test, Parser par_positive, Parser par_negative) {
  return new Ite(std::move(par_test), std::move(par_positive), std::move(par_negative));
}
Parser choose(std::vector<Parser> pars, size_t data_index) {
  return new Choose(std::move(pars), data_index);
}

Parser save_parsed(Parser par, size_t data_index) {
  return new SaveParsed(std::move(par), data_index);
}
Parser scope(Parser par, std::vector<size_t> data_indexes) {
  return new Scope(std::move(par), std::move(data_indexes));
}
Parser failsafe(Parser par) {
  return new Failsafe(std::move(par));
}

Parser act(Parser par, UnaryAction a) {
  switch(a) {
  case UnaryAction::Not:
    return lnot(std::move(par));
  case UnaryAction::Opt:
    return opt(std::move(par));
  case UnaryAction::Star:
    return star(std::move(par));
  case UnaryAction::Failsafe:
    return failsafe(std::move(par));
  case UnaryAction::ScopeOut:
    return scope(std::move(par), {});
  default:
    return par;
  }
}

} // namespace pm::parser

namespace pm {

// lor
Parser operator ||(Parser par_left, Parser par_right) {
  return parser::lor({std::move(par_left), std::move(par_right)});
}
// land
Parser operator &&(Parser par_left, Parser par_right) {
  return parser::land(std::move(par_left), std::move(par_right));
}
// lnot
Parser operator !(Parser par) {
  return parser::lnot(std::move(par));
}
// concat
Parser operator &(Parser par_left, Parser par_right) {
  return parser::concat({std::move(par_left), std::move(par_right)});
}
// opt
Parser operator ~(Parser par) {
  return parser::opt(std::move(par));
}
// star
Parser operator *(Parser par) {
  return parser::star(std::move(par));
}
// choose
Parser operator /(std::vector<Parser> pars, size_t data_index) {
  return parser::choose(std::move(pars), data_index);
}
// save_parsed
Parser operator >>(Parser par, size_t data_index) {
  return parser::save_parsed(std::move(par), data_index);
}
// scope
Parser operator <<(Parser par, std::vector<size_t> data_indexes) {
  return parser::scope(std::move(par), std::move(data_indexes));
}
Parser operator <<(Parser par, size_t data_index) {
  return parser::scope(std::move(par), {data_index});
}
Parser operator -(Parser par) {
  return parser::scope(std::move(par), {});
}
// act
Parser operator <<(Parser par, parser::UnaryAction a) {
  return parser::act(std::move(par), a);
}

} // namespace pm
