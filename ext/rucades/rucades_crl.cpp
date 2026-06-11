// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_crl.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {

pre_rb_CRL::pre_rb_CRL(void):
      m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesCPCRLObject>(new CPPCadesCPCRLObject())) { }

std::string pre_rb_CRL::get_auth_key_id(void)
{
    CAtlString sKeyID;
    hr_method_check(m_pCppCadesImpl->get_AuthKeyID(sKeyID));
    return std::string(sKeyID.GetString());
}

std::string pre_rb_CRL::get_issuer_name(void)
{
    CAtlString sIssuerName;
    hr_method_check(m_pCppCadesImpl->get_IssuerName(sIssuerName));
    return std::string(sIssuerName.GetString());
}

std::string pre_rb_CRL::get_next_update(void)
{
    CryptoPro::CDateTime nextUpdate;
    hr_method_check(m_pCppCadesImpl->get_NextUpdate(nextUpdate));
    return nextUpdate.tostring().c_str();
}

std::string pre_rb_CRL::get_this_update(void)
{
    CryptoPro::CDateTime thisUpdate;
    hr_method_check(m_pCppCadesImpl->get_ThisUpdate(thisUpdate));
    return thisUpdate.tostring().c_str();
}

std::string pre_rb_CRL::get_thumbprint(void)
{
    CAtlString sThumbprint;
    hr_method_check(m_pCppCadesImpl->get_Thumbprint(sThumbprint));
    return std::string(sThumbprint.GetString());
}

void pre_rb_CRL::crl_import(std::string& crl)
{
    CryptoPro::CBlob blobCRL;
    blobCRL.assign(reinterpret_cast<const BYTE *>(crl.c_str()), crl.length());
    hr_method_check(m_pCppCadesImpl->Import(blobCRL));
}

std::string pre_rb_CRL::crl_export(long type)
{
    CAPICOM_ENCODING_TYPE Type = static_cast<CAPICOM_ENCODING_TYPE>(type);
    CryptoPro::CBlob blobCRL;
    hr_method_check(m_pCppCadesImpl->Export(Type, blobCRL));
    return type == CAPICOM_ENCODE_BINARY ?
            std::string(reinterpret_cast<const char *>(blobCRL.pbData()),blobCRL.cbData()) :
            std::string(reinterpret_cast<const char *>(blobCRL.pbData()));
}

void pre_rb_CRL::define_ruby_class(VALUE module)
{
  Data_Type<pre_rb_CRL> rb_cCRL =
    define_class_under<pre_rb_CRL>(module, "CRL")
    .define_constructor(Constructor<pre_rb_CRL>())
    .define_method("auth_key_id", &pre_rb_CRL::get_auth_key_id)
    .define_method("issuer_name", &pre_rb_CRL::get_issuer_name)
    .define_method("next_update", &pre_rb_CRL::get_next_update)
    .define_method("this_update", &pre_rb_CRL::get_this_update)
    .define_method("thumbprint", &pre_rb_CRL::get_thumbprint)
    .define_method("export", &pre_rb_CRL::crl_export)
    .define_method("import", &pre_rb_CRL::crl_import);
}
}
