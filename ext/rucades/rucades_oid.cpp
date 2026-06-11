// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_oid.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {

pre_rb_OID::pre_rb_OID(void):
      m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesCPOIDObject>(new CPPCadesCPOIDObject())) { }

pre_rb_OID::pre_rb_OID(NS_SHARED_PTR::shared_ptr<CPPCadesCPOIDObject> other):
      m_pCppCadesImpl(other) { }

std::string pre_rb_OID::get_value(void)
{
  NS_SHARED_PTR::shared_ptr<CAtlStringA> pValue;
  hr_method_check(m_pCppCadesImpl->get_Value(pValue));
  return std::string((*pValue).GetString());
}

void pre_rb_OID::set_value(std::string& value)
{
  hr_method_check(m_pCppCadesImpl->put_Value(CAtlStringA(value.c_str())));
}

long pre_rb_OID::get_name(void)
{
  CAPICOM_OID name;
  hr_method_check(m_pCppCadesImpl->get_Name(&name));
  return static_cast<long>(name);
}

void pre_rb_OID::set_name (long name)
{
  hr_method_check(m_pCppCadesImpl->put_Name(static_cast<CAPICOM_OID>(name)));
}

std::string pre_rb_OID::get_friendly_name(void)
{
  CAtlString sFriendlyName;
  hr_method_check(m_pCppCadesImpl->get_FriendlyName(sFriendlyName));
  return std::string(sFriendlyName.GetString());
}

void pre_rb_OID::set_friendly_name(std::string& sFriendlyName)
{
  hr_method_check(m_pCppCadesImpl->put_FriendlyName(CAtlStringA(sFriendlyName.c_str())));
}

void pre_rb_OID::define_ruby_class(VALUE module)
{
  Data_Type<pre_rb_OID> rb_cOID =
    define_class_under<pre_rb_OID>(module, "OID")
    .define_constructor(Constructor<pre_rb_OID>())
    .define_method("name", &pre_rb_OID::get_name)
    .define_method("name=", &pre_rb_OID::set_name)
    .define_method("value", &pre_rb_OID::get_value)
    .define_method("value=", &pre_rb_OID::set_value)
    .define_method("friendly_name", &pre_rb_OID::get_friendly_name)
    .define_method("friendly_name=", &pre_rb_OID::set_friendly_name);
}
};
