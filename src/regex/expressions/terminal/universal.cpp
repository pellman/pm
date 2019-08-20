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
#include "pm/regex/expressions/terminal/universal.hpp"

//#include <functional>
#include <utility>

//#include "pm/regex/regex.hpp"
#include "pm/regex/utils/parser.hpp"

namespace pm {
namespace regex {

namespace {

// core
class ParserTrivial
  : public utils::Parser {
public:
  ParserTrivial(std::function<bool(stream::Stream)> matcher);
  bool match(stream::Stream & is, DataContext & context) const override;
private:
  const std::function<bool(stream::Stream)> matcher_;
};

class ParserSymbol
  : public utils::Parser {
public:
  ParserSymbol(std::function<bool(char)> checker);
  bool match(stream::Stream & is, DataContext & context) const override;
private:
  const std::function<bool(char)> checker_;
};

class ParserString
  : public utils::Parser {
public:
  ParserString(std::function<bool(stream::Stream &)> matcher);
  bool match(stream::Stream & is, DataContext & context) const override;
private:
  const std::function<bool(stream::Stream &)> matcher_;
};


// core implementation
ParserTrivial::ParserTrivial(std::function<bool(stream::Stream)> matcher)
  : matcher_(std::move(matcher)) {}

bool ParserTrivial::match(stream::Stream & is, DataContext &) const {
  return matcher_(is);
}

ParserSymbol::ParserSymbol(std::function<bool(char)> checker)
  : checker_(std::move(checker)) {}

bool ParserSymbol::match(stream::Stream & is, DataContext & context) const {
  char c;
  if(!(is.peek(c) && checker_(c))) {
    return false;
  }
  is.advance();
  if(context.flag) {
    context.dcur.set<char>(c);
  }
  return true;
}

ParserString::ParserString(std::function<bool(stream::Stream &)> matcher)
  : matcher_(std::move(matcher)) {}

bool ParserString::match(stream::Stream & is, DataContext & context) const {
  stream::Stream nis = is;
  if(!matcher_(nis)) {
    return false;
  }
  if(context.flag) {
    std::string tmps;
    is.peek(tmps, nis.pos());
    context.dcur.set<std::string>(std::move(tmps));
  }
  is.reposition(nis.pos());
  return true;
}

} // namespace

// interface
Regex trivial(std::function<bool(stream::Stream)> matcher) {
  return new ParserTrivial(std::move(matcher));
}
Regex symbol(std::function<bool(char)> checker) {
  return new ParserSymbol(std::move(checker));
}
Regex str(std::function<bool(stream::Stream &)> matcher) {
  return new ParserString(std::move(matcher));
}

} // namespace regex
} // namespace pm
