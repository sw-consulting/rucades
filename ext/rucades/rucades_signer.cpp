// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_signer.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_Signer::pre_rb_Signer(void):
      m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesCPSignerObject>(new CPPCadesCPSignerObject())) { }

pre_rb_Signer::pre_rb_Signer(NS_SHARED_PTR::shared_ptr<CPPCadesCPSignerObject> other):
        m_pCppCadesImpl(other) { }

pre_rb_Certificate* pre_rb_Signer::get_certificate(void)
{
    NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificateObject> pCert = NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificateObject>(new CPPCadesCPCertificateObject());
    hr_method_check(m_pCppCadesImpl->get_Certificate(pCert));
    return new pre_rb_Certificate(pCert);
}

void pre_rb_Signer::set_certificate(pre_rb_Certificate& cert)
{
    CCertContext certContext;
    hr_method_check(cert.m_pCppCadesImpl->get_CertContext(certContext));
    NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificateObject> pCPPCadesCPCert(new CPPCadesCPCertificateObject());
    pCPPCadesCPCert->put_CertContext(certContext);
    hr_method_check(m_pCppCadesImpl->put_Certificate(pCPPCadesCPCert));
}

bool pre_rb_Signer::get_check_certificate(void)
{
    BOOL bValue = 0;
    hr_method_check(m_pCppCadesImpl->get_CheckCertificate(bValue));
    return bValue != FALSE;
}

void pre_rb_Signer::set_check_certificate(bool value)
{
    hr_method_check(m_pCppCadesImpl->put_CheckCertificate(value ? TRUE : FALSE));
}
long pre_rb_Signer::get_options(void)
{
    CAPICOM_CERTIFICATE_INCLUDE_OPTION option;
    hr_method_check(m_pCppCadesImpl->get_Options(&option));
    return static_cast<long>(option);
}

void pre_rb_Signer::set_options(long opts)
{
    hr_method_check(m_pCppCadesImpl->put_Options(static_cast<CAPICOM_CERTIFICATE_INCLUDE_OPTION>(opts)));
}

std::string pre_rb_Signer::get_tsa_address(void)
{
    CAtlString sTSAAddress;
    hr_method_check(m_pCppCadesImpl->get_TSAAddress(sTSAAddress));
    return std::string(sTSAAddress.GetString());
}

void pre_rb_Signer::set_tsa_address(std::string addr)
{
    hr_method_check(m_pCppCadesImpl->put_TSAAddress(CAtlString(addr.c_str())));
}

pre_rb_Attributes pre_rb_Signer::get_unauthenticated_attributes(void)
{
    NS_SHARED_PTR::shared_ptr<CPPCadesCPAttributesObject> pAttrs = NS_SHARED_PTR::shared_ptr<CPPCadesCPAttributesObject>(new CPPCadesCPAttributesObject());
    hr_method_check(m_pCppCadesImpl->get_UnauthenticatedAttributes(pAttrs));
    return pre_rb_Attributes(pAttrs);
}

void pre_rb_Signer::set_unauthenticated_attributes(pre_rb_Attributes& attrb)
{
    hr_method_check(m_pCppCadesImpl->put_UnauthenticatedAttributes(attrb.m_pCppCadesImpl));
}

pre_rb_Attributes pre_rb_Signer::get_authenticated_attributes(void)
{
    NS_SHARED_PTR::shared_ptr<CPPCadesCPAttributesObject> pAttrs = NS_SHARED_PTR::shared_ptr<CPPCadesCPAttributesObject>(new CPPCadesCPAttributesObject());
    hr_method_check(m_pCppCadesImpl->get_AuthenticatedAttributes(pAttrs));
    return pre_rb_Attributes(pAttrs);
}

void pre_rb_Signer::set_authenticated_attributes(pre_rb_Attributes& attrb)
{
    hr_method_check(m_pCppCadesImpl->put_AuthenticatedAttributes(attrb.m_pCppCadesImpl));
}

pre_rb_Blobs pre_rb_Signer::get_crls(void)
{
    NS_SHARED_PTR::shared_ptr<CPPCadesCPBlobsObject> pBlobs = NS_SHARED_PTR::shared_ptr<CPPCadesCPBlobsObject>(new CPPCadesCPBlobsObject());
    hr_method_check(m_pCppCadesImpl->get_CRLs(pBlobs));
    return pre_rb_Blobs(pBlobs);
}

pre_rb_Blobs pre_rb_Signer::get_ocsp_responses(void)
{
    NS_SHARED_PTR::shared_ptr<CPPCadesCPBlobsObject> pBlobs = NS_SHARED_PTR::shared_ptr<CPPCadesCPBlobsObject>(new CPPCadesCPBlobsObject());
    hr_method_check(m_pCppCadesImpl->get_OCSPResponses(pBlobs));
    return pre_rb_Blobs(pBlobs);
}

std::string pre_rb_Signer::get_signing_time(void)
{
    CryptoPro::CDateTime Time;
    CryptoPro::CStringProxy strProxySigningTime;
    hr_method_check(m_pCppCadesImpl->get_SigningTime(Time));
    strProxySigningTime = Time.tostring();
    return std::string(strProxySigningTime.c_str());
}

std::string pre_rb_Signer::get_signature_time_stamp_time(void)
{
    CryptoPro::CDateTime Time;
    CryptoPro::CStringProxy strProxySigningTime;
    hr_method_check(m_pCppCadesImpl->get_SignatureTimeStampTime(Time));
    strProxySigningTime = Time.tostring();
    return std::string(strProxySigningTime.c_str());
}

void pre_rb_Signer::set_key_pin(std::string pin)
{
    CAtlStringA sKeyPin(CA2CA(CAtlStringA(pin.c_str()), CP_UTF8));
    hr_method_check(m_pCppCadesImpl->put_KeyPin(sKeyPin));
}

 void pre_rb_Signer::define_ruby_class(VALUE module)
 {
      Data_Type<pre_rb_Signer> rb_cSigner =
          define_class_under<pre_rb_Signer>(module, "Signer")
          .define_constructor(Constructor<pre_rb_Signer>())
          .define_method("certificate", &pre_rb_Signer::get_certificate)
          .define_method("certificate=", &pre_rb_Signer::set_certificate)
          .define_method("check_certificate", &pre_rb_Signer::get_check_certificate)
          .define_method("check_certificate=", &pre_rb_Signer::set_check_certificate)
          .define_method("options", &pre_rb_Signer::get_options)
          .define_method("options=", &pre_rb_Signer::set_options)
          .define_method("tsa_address", &pre_rb_Signer::get_tsa_address)
          .define_method("tsa_address=", &pre_rb_Signer::set_tsa_address)
          .define_method("unauthenticated_attributes", &pre_rb_Signer::get_unauthenticated_attributes)
          .define_method("unauthenticated_attributes=", &pre_rb_Signer::set_unauthenticated_attributes)
          .define_method("authenticated_attributes", &pre_rb_Signer::get_authenticated_attributes)
          .define_method("authenticated_attributes=", &pre_rb_Signer::set_authenticated_attributes)
          .define_method("crls", &pre_rb_Signer::get_crls)
          .define_method("ocsp_responses", &pre_rb_Signer::get_ocsp_responses)
          .define_method("signing_time", &pre_rb_Signer::get_signing_time)
          .define_method("signature_time_stamp_time", &pre_rb_Signer::get_signature_time_stamp_time)
          .define_method("key_pin=", &pre_rb_Signer::set_key_pin);
 }
}
