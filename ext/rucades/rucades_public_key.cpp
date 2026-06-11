// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_public_key.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_PublicKey::pre_rb_PublicKey(void):
          m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesCPPublicKeyObject>(new CPPCadesCPPublicKeyObject())) { }

pre_rb_PublicKey::pre_rb_PublicKey(NS_SHARED_PTR::shared_ptr<CPPCadesCPPublicKeyObject> other):
      m_pCppCadesImpl(other) { }

pre_rb_OID* pre_rb_PublicKey::get_algorithm(void)
{
    pre_rb_OID* pOID = new pre_rb_OID();
    hr_method_check(m_pCppCadesImpl->get_Algorithm(pOID->m_pCppCadesImpl));
    return pOID;
}

pre_rb_EncodedData pre_rb_PublicKey::get_encoded_key(void)
{
    pre_rb_EncodedData pEncodedData;
    hr_method_check(m_pCppCadesImpl->get_EncodedKey(pEncodedData.m_pCppCadesImpl));
    return pEncodedData;
}

pre_rb_EncodedData pre_rb_PublicKey::get_encoded_parameters(void)
{
    pre_rb_EncodedData pEncodedData;
    hr_method_check(m_pCppCadesImpl->get_EncodedParameters(pEncodedData.m_pCppCadesImpl));
    return pEncodedData;
}

long pre_rb_PublicKey::get_length(void)
{
    DWORD dwLen = 0;
    hr_method_check(m_pCppCadesImpl->get_Length(&dwLen));
    return dwLen;
}

void pre_rb_PublicKey::define_ruby_class(VALUE module)
{
  Data_Type<pre_rb_PublicKey> rb_cPublicKey =
    define_class_under<pre_rb_PublicKey>(module, "PublicKey")
    .define_constructor(Constructor<pre_rb_PublicKey>())
    .define_method("algorithm", &pre_rb_PublicKey::get_algorithm)
    .define_method("encoded_key", &pre_rb_PublicKey::get_encoded_key)
    .define_method("encoded_parameters", &pre_rb_PublicKey::get_encoded_parameters)
    .define_method("length", &pre_rb_PublicKey::get_length);
}
}
