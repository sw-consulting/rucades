// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_algorithm.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_Algorithm::pre_rb_Algorithm(void):
      m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesCPAlgorithmObject>(new CPPCadesCPAlgorithmObject())) { }

pre_rb_Algorithm::pre_rb_Algorithm(NS_SHARED_PTR::shared_ptr<CPPCadesCPAlgorithmObject> other):
      m_pCppCadesImpl(other) { }

long pre_rb_Algorithm::get_name(void)
{
  CADESCOM_ENCRYPTION_ALGORITHM name;
  hr_method_check(m_pCppCadesImpl->get_Name(&name));
  return static_cast<long>(name);
}

void pre_rb_Algorithm::set_name (long name)
{
  hr_method_check(m_pCppCadesImpl->put_Name(static_cast<CADESCOM_ENCRYPTION_ALGORITHM>(name)));
}

long pre_rb_Algorithm::get_key_length(void) {
  CAPICOM_ENCRYPTION_KEY_LENGTH len;
  hr_method_check(m_pCppCadesImpl->get_KeyLength(&len));
  return static_cast<long>(len);
}

void pre_rb_Algorithm::set_key_length(long len)
{
  hr_method_check(m_pCppCadesImpl->put_KeyLength(static_cast<CAPICOM_ENCRYPTION_KEY_LENGTH>(len)));
}

void pre_rb_Algorithm::define_ruby_class(VALUE module)
{
  Data_Type<pre_rb_Algorithm> rb_cAlgorithm =
    define_class_under<pre_rb_Algorithm>(module, "Algorithm")
    .define_constructor(Constructor<pre_rb_Algorithm>())
    .define_method("name", &pre_rb_Algorithm::get_name)
    .define_method("name=", &pre_rb_Algorithm::set_name)
    .define_method("key_length", &pre_rb_Algorithm::get_key_length)
    .define_method("key_length=", &pre_rb_Algorithm::set_key_length);
}
}
