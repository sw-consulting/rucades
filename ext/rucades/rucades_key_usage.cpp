// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_key_usage.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_KeyUsage::pre_rb_KeyUsage(void):
      m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesCPKeyUsageObject>(new CPPCadesCPKeyUsageObject())) { }

pre_rb_KeyUsage::pre_rb_KeyUsage(NS_SHARED_PTR::shared_ptr<CPPCadesCPKeyUsageObject> other):
      m_pCppCadesImpl(other) { }

bool pre_rb_KeyUsage::is_present(void)
{
    BOOL bVal = 0;
    hr_method_check(m_pCppCadesImpl->get_IsPresent(&bVal));
    return (bVal != 0);
}

bool pre_rb_KeyUsage::is_critical(void)
{
    BOOL bVal = 0;
    hr_method_check(m_pCppCadesImpl->get_IsCritical(&bVal));
    return (bVal != 0);
}

bool pre_rb_KeyUsage::is_digital_signature_enabled(void)
{
    BOOL bVal = 0;
    hr_method_check(m_pCppCadesImpl->get_IsDigitalSignatureEnabled(&bVal));
    return (bVal != 0);
}

bool pre_rb_KeyUsage::is_non_repudiation_enabled(void)
{
    BOOL bVal = 0;
    hr_method_check(m_pCppCadesImpl->get_IsNonRepudiationEnabled(&bVal));
    return (bVal != 0);
}

bool pre_rb_KeyUsage::is_key_encipherment_enabled(void)
{
    BOOL bVal = 0;
    hr_method_check(m_pCppCadesImpl->get_IsKeyEnciphermentEnabled(&bVal));
    return (bVal != 0);
}

bool pre_rb_KeyUsage::is_key_agreement_enabled(void)
{
    BOOL bVal = 0;
    hr_method_check(m_pCppCadesImpl->get_IsKeyAgreementEnabled(&bVal));
    return (bVal != 0);
}

bool pre_rb_KeyUsage::is_key_cert_sign_enabled(void)
{
    BOOL bVal = 0;
    hr_method_check(m_pCppCadesImpl->get_IsKeyCertSignEnabled(&bVal));
    return (bVal != 0);
}

bool pre_rb_KeyUsage::is_data_encipherment_enabled(void)
{
    BOOL bVal = 0;
    hr_method_check(m_pCppCadesImpl->get_IsDataEnciphermentEnabled(&bVal));
    return (bVal != 0);
}

bool pre_rb_KeyUsage::is_crl_sign_enabled(void)
{
    BOOL bVal = 0;
    hr_method_check(m_pCppCadesImpl->get_IsCRLSignEnabled(&bVal));
    return (bVal != 0);
}

bool pre_rb_KeyUsage::is_encipher_only_enabled(void)
{
    BOOL bVal = 0;
    hr_method_check(m_pCppCadesImpl->get_IsEncipherOnlyEnabled(&bVal));
    return (bVal != 0);
}

bool pre_rb_KeyUsage::is_decipher_only_enabled(void)
{
    BOOL bVal = 0;
    hr_method_check(m_pCppCadesImpl->get_IsDecipherOnlyEnabled(&bVal));
    return (bVal != 0);
}

void pre_rb_KeyUsage::define_ruby_class(VALUE module)
{
  Data_Type<pre_rb_KeyUsage> rb_cKeyUsage =
    define_class_under<pre_rb_KeyUsage>(module, "KeyUsage")
    .define_constructor(Constructor<pre_rb_KeyUsage>())
    .define_method("present?", &pre_rb_KeyUsage::is_present)
    .define_method("critical?", &pre_rb_KeyUsage::is_critical)
    .define_method("digital_signature_enabled?", &pre_rb_KeyUsage::is_digital_signature_enabled)
    .define_method("non_repudiation_enabled?", &pre_rb_KeyUsage::is_non_repudiation_enabled)
    .define_method("key_encipherment_enabled?", &pre_rb_KeyUsage::is_key_encipherment_enabled)
    .define_method("key_agreement_enabled?", &pre_rb_KeyUsage::is_key_agreement_enabled)
    .define_method("key_cert_sign_enabled?", &pre_rb_KeyUsage::is_key_cert_sign_enabled)
    .define_method("data_encipherment_enabled?", &pre_rb_KeyUsage::is_data_encipherment_enabled)
    .define_method("crl_sign_enabled?", &pre_rb_KeyUsage::is_crl_sign_enabled)
    .define_method("encipher_only_enabled?", &pre_rb_KeyUsage::is_encipher_only_enabled)
    .define_method("decipher_only_enabled?", &pre_rb_KeyUsage::is_decipher_only_enabled);
}

}
