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
#include "dataset/syntax/function.hpp"

#include <utility>

namespace pm {
namespace dataset {
namespace syntax {

void Function::set_applier(const std::string & target, const std::string & source, const type_abuse::Applier & fun) {
  unset_();
  t_ = APPLIER;
  target_ = target;
  source_ = source;
  applier_ = fun;
}

void Function::set_applier(const std::string & target, const std::string & source, type_abuse::Applier && fun) {
  unset_();
  t_ = APPLIER;
  target_ = target;
  source_ = source;
  applier_ = std::move(fun);
}

void Function::set_applier(const std::string & target, std::string && source, const type_abuse::Applier & fun) {
  unset_();
  t_ = APPLIER;
  target_ = target;
  source_ = std::move(source);
  applier_ = fun;
}

void Function::set_applier(const std::string & target, std::string && source, type_abuse::Applier && fun) {
  unset_();
  t_ = APPLIER;
  target_ = target;
  source_ = std::move(source);
  applier_ = std::move(fun);
}

void Function::set_applier(std::string && target, const std::string & source, const type_abuse::Applier & fun) {
  unset_();
  t_ = APPLIER;
  target_ = std::move(target);
  source_ = source;
  applier_ = fun;
}

void Function::set_applier(std::string && target, const std::string & source, type_abuse::Applier && fun) {
  unset_();
  t_ = APPLIER;
  target_ = std::move(target);
  source_ = source;
  applier_ = std::move(fun);
}

void Function::set_applier(std::string && target, std::string && source, const type_abuse::Applier & fun) {
  unset_();
  t_ = APPLIER;
  target_ = std::move(target);
  source_ = std::move(source);
  applier_ = fun;
}

void Function::set_applier(std::string && target, std::string && source, type_abuse::Applier && fun) {
  unset_();
  t_ = APPLIER;
  target_ = std::move(target);
  source_ = std::move(source);
  applier_ = std::move(fun);
}

void Function::set_cloner(const std::string & target, const std::string & source) {
  unset_();
  t_ = CLONER;
  target_ = target;
  source_ = source;
}

void Function::set_cloner(const std::string & target, std::string && source) {
  unset_();
  t_ = CLONER;
  target_ = target;
  source_ = std::move(source);
}

void Function::set_cloner(std::string && target, const std::string & source) {
  unset_();
  t_ = CLONER;
  target_ = std::move(target);
  source_ = source;
}

void Function::set_cloner(std::string && target, std::string && source) {
  unset_();
  t_ = CLONER;
  target_ = std::move(target);
  source_ = std::move(source);
}

void Function::set_composition(const std::list<Function> & funcs) {
  unset_();
  t_ = COMPOSITION;
  function_list_ = funcs;
}

void Function::set_composition(std::list<Function> && funcs) {
  unset_();
  t_ = COMPOSITION;
  function_list_ = std::move(funcs);
}

void Function::set_creator(const std::string & target, const type_abuse::Creator & fun) {
  unset_();
  t_ = CREATOR;
  target_ = target;
  creator_ = fun;
}

void Function::set_creator(const std::string & target, type_abuse::Creator && fun) {
  unset_();
  t_ = CREATOR;
  target_ = target;
  creator_ = std::move(fun);
}

void Function::set_creator(std::string && target, const type_abuse::Creator & fun) {
  unset_();
  t_ = CREATOR;
  target_ = std::move(target);
  creator_ = fun;
}

void Function::set_creator(std::string && target, type_abuse::Creator && fun) {
  unset_();
  t_ = CREATOR;
  target_ = std::move(target);
  creator_ = std::move(fun);
}

void Function::set_flusher(const std::string & target, const type_abuse::DRef & data) {
  unset_();
  t_ = FLUSHER;
  target_ = target;
  data_ = data;
}

void Function::set_flusher(const std::string & target, type_abuse::DRef && data) {
  unset_();
  t_ = FLUSHER;
  target_ = target;
  data_ = std::move(data);
}

void Function::set_flusher(std::string && target, const type_abuse::DRef & data) {
  unset_();
  t_ = FLUSHER;
  target_ = std::move(target);
  data_ = data;
}

void Function::set_flusher(std::string && target, type_abuse::DRef && data) {
  unset_();
  t_ = FLUSHER;
  target_ = std::move(target);
  data_ = std::move(data);
}

void Function::set_modifier(const std::string & target, const type_abuse::Modifier & fun) {
  unset_();
  t_ = MODIFIER;
  target_ = target;
  modifier_ = fun;
}

void Function::set_modifier(const std::string & target, type_abuse::Modifier && fun) {
  unset_();
  t_ = MODIFIER;
  target_ = target;
  modifier_ = std::move(fun);
}

void Function::set_modifier(std::string && target, const type_abuse::Modifier & fun) {
  unset_();
  t_ = MODIFIER;
  target_ = std::move(target);
  modifier_ = fun;
}

void Function::set_modifier(std::string && target, type_abuse::Modifier && fun) {
  unset_();
  t_ = MODIFIER;
  target_ = std::move(target);
  modifier_ = std::move(fun);
}

void Function::unset() {
  unset_();
  t_ = TRIVIAL;
}

void Function::unset_() {
  switch(t_) {
  case APPLIER:
    target_.unset();
    source_.unset();
    applier_.unset();
    break;
  case CLONER:
    target_.unset();
    source_.unset();
    break;
  case COMPOSITION:
    function_list_.unset();
    break;
  case CREATOR:
    target_.unset();
    creator_.unset();
    break;
  case FLUSHER:
    target_.unset();
    data_.unset();
    break;
  case MODIFIER:
    target_.unset();
    modifier_.unset();
    break;
  default:
    break;
  }
}

Function trivial_function;

Function applier(const std::string & target, const std::string & source, const type_abuse::Applier & fun) {
  Function res;
  res.set_applier(target, source, fun);
  return res;
}

Function applier(const std::string & target, const std::string & source, type_abuse::Applier && fun) {
  Function res;
  res.set_applier(target, source, std::move(fun));
  return res;
}

Function applier(const std::string & target, std::string && source, const type_abuse::Applier & fun) {
  Function res;
  res.set_applier(target, std::move(source), fun);
  return res;
}

Function applier(const std::string & target, std::string && source, type_abuse::Applier && fun) {
  Function res;
  res.set_applier(target, std::move(source), std::move(fun));
  return res;
}

Function applier(std::string && target, const std::string & source, const type_abuse::Applier & fun) {
  Function res;
  res.set_applier(std::move(target), source, fun);
  return res;
}

Function applier(std::string && target, const std::string & source, type_abuse::Applier && fun) {
  Function res;
  res.set_applier(std::move(target), source, std::move(fun));
  return res;
}

Function applier(std::string && target, std::string && source, const type_abuse::Applier & fun) {
  Function res;
  res.set_applier(std::move(target), std::move(source), fun);
  return res;
}

Function applier(std::string && target, std::string && source, type_abuse::Applier && fun) {
  Function res;
  res.set_applier(std::move(target), std::move(source), std::move(fun));
  return res;
}

Function cloner(const std::string & target, const std::string & source) {
  Function res;
  res.set_cloner(target, source);
  return res;
}

Function cloner(const std::string & target, std::string && source) {
  Function res;
  res.set_cloner(target, std::move(source));
  return res;
}

Function cloner(std::string && target, const std::string & source) {
  Function res;
  res.set_cloner(std::move(target), source);
  return res;
}

Function cloner(std::string && target, std::string && source) {
  Function res;
  res.set_cloner(std::move(target), std::move(source));
  return res;
}

Function composition(const std::list<Function> & funcs) {
  Function res;
  res.set_composition(funcs);
  return res;
}

Function composition(std::list<Function> && funcs) {
  Function res;
  res.set_composition(std::move(funcs));
  return res;
}

Function creator(const std::string & target, const type_abuse::Creator & fun) {
  Function res;
  res.set_creator(target, fun);
  return res;
}

Function creator(const std::string & target, type_abuse::Creator && fun) {
  Function res;
  res.set_creator(target, std::move(fun));
  return res;
}

Function creator(std::string && target, const type_abuse::Creator & fun) {
  Function res;
  res.set_creator(std::move(target), fun);
  return res;
}

Function creator(std::string && target, type_abuse::Creator && fun) {
  Function res;
  res.set_creator(std::move(target), std::move(fun));
  return res;
}

Function flusher(const std::string & target, const type_abuse::DRef & data) {
  Function res;
  res.set_flusher(target, data);
  return res;
}

Function flusher(const std::string & target, type_abuse::DRef && data) {
  Function res;
  res.set_flusher(target, std::move(data));
  return res;
}

Function flusher(std::string && target, const type_abuse::DRef & data) {
  Function res;
  res.set_flusher(std::move(target), data);
  return res;
}

Function flusher(std::string && target, type_abuse::DRef && data) {
  Function res;
  res.set_flusher(std::move(target), std::move(data));
  return res;
}

Function modifier(const std::string & target, const type_abuse::Modifier & fun) {
  Function res;
  res.set_modifier(target, fun);
  return res;
}

Function modifier(const std::string & target, type_abuse::Modifier && fun) {
  Function res;
  res.set_modifier(target, std::move(fun));
  return res;
}

Function modifier(std::string && target, const type_abuse::Modifier & fun) {
  Function res;
  res.set_modifier(std::move(target), fun);
  return res;
}

Function modifier(std::string && target, type_abuse::Modifier && fun) {
  Function res;
  res.set_modifier(std::move(target), std::move(fun));
  return res;
}

} // namespace syntax
} // namespace dataset
} // namespace pm
