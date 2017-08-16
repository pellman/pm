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
#ifndef __DATASET_SYNTAX_FUNCTION_HPP
#define __DATASET_SYNTAX_FUNCTION_HPP

#include <list>
#include <string>
#include <type_abuse/dfun.hpp>
#include <type_abuse/dref.hpp>
#include <utils/optional.hpp>

namespace pm {
namespace dataset {
namespace syntax {

class Function {
public:
  // TYPES
  enum T {TRIVIAL, APPLIER, CLONER, COMPOSITION, CREATOR, FLUSHER, MODIFIER};
  // ALTERING METHODS
  void set_applier(const std::string & target, const std::string & source, const type_abuse::Applier & fun);
  void set_applier(const std::string & target, const std::string & source, type_abuse::Applier && fun);
  void set_applier(const std::string & target, std::string && source, const type_abuse::Applier & fun);
  void set_applier(const std::string & target, std::string && source, type_abuse::Applier && fun);
  void set_applier(std::string && target, const std::string & source, const type_abuse::Applier & fun);
  void set_applier(std::string && target, const std::string & source, type_abuse::Applier && fun);
  void set_applier(std::string && target, std::string && source, const type_abuse::Applier & fun);
  void set_applier(std::string && target, std::string && source, type_abuse::Applier && fun);
  void set_cloner(const std::string & target, const std::string & source);
  void set_cloner(const std::string & target, std::string && source);
  void set_cloner(std::string && target, const std::string & source);
  void set_cloner(std::string && target, std::string && source);
  void set_composition(const std::list<Function> & funcs);
  void set_composition(std::list<Function> && funcs);
  void set_creator(const std::string & target, const type_abuse::Creator & fun);
  void set_creator(const std::string & target, type_abuse::Creator && fun);
  void set_creator(std::string && target, const type_abuse::Creator & fun);
  void set_creator(std::string && target, type_abuse::Creator && fun);
  void set_flusher(const std::string & target, const type_abuse::DRef & data);
  void set_flusher(const std::string & target, type_abuse::DRef && data);
  void set_flusher(std::string && target, const type_abuse::DRef & data);
  void set_flusher(std::string && target, type_abuse::DRef && data);
  void set_modifier(const std::string & target, const type_abuse::Modifier & fun);
  void set_modifier(const std::string & target, type_abuse::Modifier && fun);
  void set_modifier(std::string && target, const type_abuse::Modifier & fun);
  void set_modifier(std::string && target, type_abuse::Modifier && fun);
  void unset();
  // ACCESS METHODS
  // = type =
  inline T type() const;
  // = check =
  inline bool has_applier() const;
  inline bool has_creator() const;
  inline bool has_data() const;
  inline bool has_function_list() const;
  inline bool has_modifier() const;
  inline bool has_source() const;
  inline bool has_target() const;
  // = get =
  inline type_abuse::Applier & applier();
  inline const type_abuse::Applier & applier() const;
  inline type_abuse::Creator & creator();
  inline const type_abuse::Creator & creator() const;
  inline type_abuse::DRef & data();
  inline const type_abuse::DRef & data() const;
  inline std::list<Function> & function_list();
  inline const std::list<Function> & function_list() const;
  inline type_abuse::Modifier & modifier();
  inline const type_abuse::Modifier & modifier() const;
  inline std::string & source();
  inline const std::string & source() const;
  inline std::string & target();
  inline const std::string & target() const;

private:
  // ALTERING METHODS
  void unset_();
  // FIELDS
  T t_ = TRIVIAL;
  utils::Optional<std::string> target_;
  utils::Optional<std::string> source_;
  utils::Optional<type_abuse::Applier> applier_;
  utils::Optional<type_abuse::Creator> creator_;
  utils::Optional<type_abuse::Modifier> modifier_;
  utils::Optional<type_abuse::DRef> data_;
  utils::Optional<std::list<Function>> function_list_;
};

extern Function trivial_function;

Function applier(const std::string & target, const std::string & source, const type_abuse::Applier & fun);
Function applier(const std::string & target, const std::string & source, type_abuse::Applier && fun);
Function applier(const std::string & target, std::string && source, const type_abuse::Applier & fun);
Function applier(const std::string & target, std::string && source, type_abuse::Applier && fun);
Function applier(std::string && target, const std::string & source, const type_abuse::Applier & fun);
Function applier(std::string && target, const std::string & source, type_abuse::Applier && fun);
Function applier(std::string && target, std::string && source, const type_abuse::Applier & fun);
Function applier(std::string && target, std::string && source, type_abuse::Applier && fun);
Function cloner(const std::string & target, const std::string & source);
Function cloner(const std::string & target, std::string && source);
Function cloner(std::string && target, const std::string & source);
Function cloner(std::string && target, std::string && source);
Function composition(const std::list<Function> & funcs);
Function composition(std::list<Function> && funcs);
Function creator(const std::string & target, const type_abuse::Creator & fun);
Function creator(const std::string & target, type_abuse::Creator && fun);
Function creator(std::string && target, const type_abuse::Creator & fun);
Function creator(std::string && target, type_abuse::Creator && fun);
Function flusher(const std::string & target, const type_abuse::DRef & data);
Function flusher(const std::string & target, type_abuse::DRef && data);
Function flusher(std::string && target, const type_abuse::DRef & data);
Function flusher(std::string && target, type_abuse::DRef && data);
Function modifier(const std::string & target, const type_abuse::Modifier & fun);
Function modifier(const std::string & target, type_abuse::Modifier && fun);
Function modifier(std::string && target, const type_abuse::Modifier & fun);
Function modifier(std::string && target, type_abuse::Modifier && fun);


// IMPLEMENTATION
Function::T Function::type() const {return t_;}

bool Function::has_applier() const {return applier_.has_value();}

bool Function::has_creator() const {return creator_.has_value();}

bool Function::has_data() const {return data_.has_value();}

bool Function::has_function_list() const {return function_list_.has_value();}

bool Function::has_modifier() const {return modifier_.has_value();}

bool Function::has_source() const {return source_.has_value();}

bool Function::has_target() const {return target_.has_value();}

type_abuse::Applier & Function::applier() {return applier_.value();}

const type_abuse::Applier & Function::applier() const {return applier_.value();}

type_abuse::Creator & Function::creator() {return creator_.value();}

const type_abuse::Creator & Function::creator() const {return creator_.value();}

type_abuse::DRef & Function::data() {return data_.value();}

const type_abuse::DRef & Function::data() const {return data_.value();}

std::list<Function> & Function::function_list() {return function_list_.value();}

const std::list<Function> & Function::function_list() const {return function_list_.value();}

type_abuse::Modifier & Function::modifier() {return modifier_.value();}

const type_abuse::Modifier & Function::modifier() const {return modifier_.value();}

std::string & Function::source() {return source_.value();}

const std::string & Function::source() const {return source_.value();}

std::string & Function::target() {return target_.value();}

const std::string & Function::target() const {return target_.value();}

} // namespace syntax
} // namespace dataset
} // namespace pm

#endif
