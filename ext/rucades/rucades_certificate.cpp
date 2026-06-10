// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_certificate.h"
#include "rucades_store.h"

#include "CPPCadesCollections.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_Certificate::pre_rb_Certificate(void):
      m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificateObject>(new CPPCadesCPCertificateObject())) { }

pre_rb_Certificate::pre_rb_Certificate(NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificateObject> other):
      m_pCppCadesImpl(other) { }

std::string pre_rb_Certificate::get_subject_name(void)
{
    CAtlString sSubjectName;
    hr_method_check(m_pCppCadesImpl->get_SubjectName(sSubjectName));
    return std::string(sSubjectName.GetString());
}

std::string pre_rb_Certificate::get_issuer_name(void)
{
    CAtlString sIssuerName;
    hr_method_check(m_pCppCadesImpl->get_IssuerName(sIssuerName));
    return std::string(sIssuerName.GetString());
}

std::string pre_rb_Certificate::get_serial_number(void)
{
    CAtlString sSerialNumber;
    hr_method_check(m_pCppCadesImpl->get_SerialNumber(sSerialNumber));
    return std::string(sSerialNumber.GetString());
}

std::string pre_rb_Certificate::get_thumbprint(void)
{
    CAtlString sThumbprint;
    hr_method_check(m_pCppCadesImpl->get_Thumbprint(sThumbprint));
    return std::string(sThumbprint.GetString());
}

long pre_rb_Certificate::get_version(void)
{
    DWORD dwVersion;
    hr_method_check(m_pCppCadesImpl->get_Version(&dwVersion));
    return static_cast<long>(dwVersion);
}

std::string pre_rb_Certificate::get_valid_from_date(void)
{
    CryptoPro::CDateTime date;
    CryptoPro::CStringProxy strProxyDate;
    hr_method_check(m_pCppCadesImpl->get_ValidFromDate(date));
    strProxyDate = date.tostring();
    return std::string(strProxyDate.c_str());
}

std::string pre_rb_Certificate::get_valid_to_date(void)
{
    CryptoPro::CDateTime date;
    CryptoPro::CStringProxy strProxyDate;
    hr_method_check(m_pCppCadesImpl->get_ValidToDate(date));
    strProxyDate = date.tostring();
    return std::string(strProxyDate.c_str());
}

pre_rb_PrivateKey pre_rb_Certificate::get_private_key(void)
{
    pre_rb_PrivateKey pPrivateKey;
    hr_method_check(m_pCppCadesImpl->PrivateKey(pPrivateKey.m_pCppCadesImpl));
    return pPrivateKey;
}

pre_rb_PublicKey pre_rb_Certificate::get_public_key(void)
{
    pre_rb_PublicKey pPublicKey;
    hr_method_check(m_pCppCadesImpl->PublicKey(pPublicKey.m_pCppCadesImpl));
    return pPublicKey;
}

pre_rb_KeyUsage pre_rb_Certificate::get_key_usage(void)
{
    pre_rb_KeyUsage pKeyUsage;
    hr_method_check(m_pCppCadesImpl->KeyUsage(pKeyUsage.m_pCppCadesImpl));
    return pKeyUsage;
}

pre_rb_ExtendedKeyUsage pre_rb_Certificate::get_extended_key_usage(void)
{
    pre_rb_ExtendedKeyUsage pExtendedKeyUsage;
    hr_method_check(m_pCppCadesImpl->ExtendedKeyUsage(pExtendedKeyUsage.m_pCppCadesImpl));
    return pExtendedKeyUsage;
}

pre_rb_BasicConstraints  pre_rb_Certificate::get_basic_constraints(void)
{
    pre_rb_BasicConstraints pBasicConstraints;
    hr_method_check(m_pCppCadesImpl->BasicConstraints(pBasicConstraints.m_pCppCadesImpl));
    return pBasicConstraints;
}

pre_rb_CertificateStatus pre_rb_Certificate::get_certificate_status(void)
{
    pre_rb_CertificateStatus pCertificateStatus;
    hr_method_check(m_pCppCadesImpl->IsValid(pCertificateStatus.m_pCppCadesImpl));
    return pCertificateStatus;
}

std::string pre_rb_Certificate::get_info(long type)
{
    CAPICOM_CERT_INFO_TYPE Type = static_cast<CAPICOM_CERT_INFO_TYPE>(type);
    CAtlString sInfo;
    hr_method_check(m_pCppCadesImpl->GetInfo(Type, sInfo));
    return std::string(sInfo.GetString());
}

bool pre_rb_Certificate::has_private_key(void)
{
    BOOL has = 0;
    hr_method_check(m_pCppCadesImpl->HasPrivateKey(&has));
    return (has != FALSE);
}

std::string pre_rb_Certificate::crt_export(long type)
{
    CryptoPro::CBlob value;
    CAPICOM_ENCODING_TYPE Type = static_cast<CAPICOM_ENCODING_TYPE>(type);
    hr_method_check(m_pCppCadesImpl->Export(Type, value));
    return type == CAPICOM_ENCODE_BINARY ?
        std::string(reinterpret_cast<const char *>(value.pbData()), value.cbData()) :
        std::string(reinterpret_cast<const char *>(value.pbData()));
}
void pre_rb_Certificate::crt_import (std::string crt)
{
    CryptoPro::CBlob value;
    value.assign(reinterpret_cast<const BYTE *>(crt.c_str()), crt.length());
    hr_method_check(m_pCppCadesImpl->Import(value));
}

void pre_rb_Certificate::additional_store(pre_rb_Store& store)
{
    hr_method_check(m_pCppCadesImpl->AdditionalStore(store.m_pCppCadesImpl));
}

static Data_Type<pre_rb_Certificate> rb_cCertificate;
void pre_rb_Certificate::define_ruby_class(VALUE module)
{
    rb_cCertificate =
        define_class_under<pre_rb_Certificate>(module, "Certificate")
        .define_constructor(Constructor<pre_rb_Certificate>())
        .define_method("subject_name", &pre_rb_Certificate::get_subject_name)
        .define_method("issuer_name", &pre_rb_Certificate::get_issuer_name)
        .define_method("serial_number", &pre_rb_Certificate::get_serial_number)
        .define_method("thumbprint", &pre_rb_Certificate::get_thumbprint)
        .define_method("version", &pre_rb_Certificate::get_version)
        .define_method("valid_from_date", &pre_rb_Certificate::get_valid_from_date)
        .define_method("valid_to_date", &pre_rb_Certificate::get_valid_to_date)
        .define_method("private_key", &pre_rb_Certificate::get_private_key)
        .define_method("public_key", &pre_rb_Certificate::get_public_key)
        .define_method("key_usage", &pre_rb_Certificate::get_key_usage)
        .define_method("extended_key_usage", &pre_rb_Certificate::get_extended_key_usage)
        .define_method("basic_constraints", &pre_rb_Certificate::get_basic_constraints)
        .define_method("is_valid", &pre_rb_Certificate::get_certificate_status)
        .define_method("import", &pre_rb_Certificate::crt_import)
        .define_method("export", &pre_rb_Certificate::crt_export)
        .define_method("has_private_key?", &pre_rb_Certificate::has_private_key);
}
void pre_rb_Certificate::extend_ruby_class(void)
{
    rb_cCertificate.define_method("additional_store", &pre_rb_Certificate::additional_store);
}
}
