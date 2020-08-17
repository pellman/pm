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
#include "pm/creation/parser/functional.hpp"

#include <utility>

//#include "pm/creation/char_set/functional.hpp"

//#include "pm/devel/parser/base.hpp"
//#include "pm/devel/parser/letter.hpp"
//#include "pm/devel/parser/scanner.hpp"
//#include "pm/devel/parser/trivial.hpp"

namespace pm::parser {
namespace {

class TFParse
  : public devel::parser::Base {
public:
  TFParse(std::function<bool(Stream &, Context &)> f)
    : f_(std::move(f)) {}
  bool parse(Stream & is, Context & con) const override {
    Stream backup_is = is;
    if(f_(is, con)) {
      return true;
    }
    is = std::move(backup_is);
    return false;
  }
private:
  const std::function<bool(Stream &, Context &)> f_;
};

class TFExecute
  : public devel::parser::Base {
public:
  TFExecute(std::function<void(Stream &, Context &)> f)
    : f_(std::move(f)) {}
  bool parse(Stream & is, Context & con) const override {
    f_(is, con);
    return true;
  }
private:
  const std::function<void(Stream &, Context &)> f_;
};

} // namespace

Parser fparse(FParse f) {
  return new TFParse(std::move(f));
}
Parser fexecute(FExecute f) {
  return new TFExecute(std::move(f));
}

} // namespace pm::parser
