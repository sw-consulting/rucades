// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_eku.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {

pre_rb_EKU::pre_rb_EKU(void):
      m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesCPEKUObject>(new CPPCadesCPEKUObject())) { }

pre_rb_EKU::pre_rb_EKU(NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPEKUObject> other):
      m_pCppCadesImpl(other) { }

long pre_rb_EKU::get_name(void)
{
  CAPICOM_EKU name;
  hr_method_check(m_pCppCadesImpl->get_Name(&name));
  return static_cast<long>(name);
}
void pre_rb_EKU::set_name (long name)
{
  hr_method_check(m_pCppCadesImpl->put_Name(static_cast<CAPICOM_EKU>(name)));
}
std::string pre_rb_EKU::get_oid(void)
{
  CAtlStringA OID;
  hr_method_check(m_pCppCadesImpl->get_OID(OID));
  return std::string(OID.GetString());
}
void pre_rb_EKU::set_oid(std::string& oid)
{
  CAtlStringA sOID = CAtlString(oid.c_str());
  hr_method_check(m_pCppCadesImpl->put_OID(sOID));
}

void pre_rb_EKU::define_ruby_class(VALUE module)
{
  Data_Type<pre_rb_EKU> rb_cEKU =
    define_class_under<pre_rb_EKU>(module, "EKU")
    .define_constructor(Constructor<pre_rb_EKU>())
    .define_method("name", &pre_rb_EKU::get_name)
    .define_method("name=", &pre_rb_EKU::set_name)
    .define_method("oid", &pre_rb_EKU::get_oid)
    .define_method("oid=", &pre_rb_EKU::set_oid);
}

}
