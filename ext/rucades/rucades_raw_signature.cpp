// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_raw_signature.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_RawSignature::pre_rb_RawSignature(void):
    m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesRawSignatureObject>(new CPPCadesRawSignatureObject())) { }

pre_rb_RawSignature::pre_rb_RawSignature(NS_SHARED_PTR::shared_ptr<CPPCadesRawSignatureObject> other):
    m_pCppCadesImpl(other) { }

std::string pre_rb_RawSignature::sign_hash(pre_rb_HashedData& data, pre_rb_Certificate& cert)
{
    CAtlString sSignature;
    hr_method_check(m_pCppCadesImpl->SignHash(data.m_pCppCadesImpl, cert.m_pCppCadesImpl, sSignature));
    return std::string(sSignature.GetString());
}

void pre_rb_RawSignature::verify_hash(pre_rb_HashedData& data, pre_rb_Certificate& cert, std::string signature)
{
    CAtlString sSignature(signature.c_str());
    hr_method_check(m_pCppCadesImpl->VerifyHash(data.m_pCppCadesImpl, sSignature, cert.m_pCppCadesImpl));
}

void pre_rb_RawSignature::define_ruby_class(VALUE module)
{
    Data_Type<pre_rb_RawSignature> rb_cRawSignature =
        define_class_under<pre_rb_RawSignature>(module, "RawSignature")
        .define_constructor(Constructor<pre_rb_RawSignature>())
        .define_method("sign_hash", &pre_rb_RawSignature::sign_hash)
        .define_method("verify_hash", &pre_rb_RawSignature::verify_hash);
}
}
