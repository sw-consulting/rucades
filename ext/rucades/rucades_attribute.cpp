// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_attribute.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {

pre_rb_Attribute::pre_rb_Attribute(void):
      m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesCPAttributeObject>(new CPPCadesCPAttributeObject())) { }

pre_rb_Attribute::pre_rb_Attribute(NS_SHARED_PTR::shared_ptr<CPPCadesCPAttributeObject> other):
      m_pCppCadesImpl(other) { }

pre_rb_OID pre_rb_Attribute::get_OID(void)
{
    NS_SHARED_PTR::shared_ptr<CPPCadesCPOIDObject> pCPPCadesCPOID(new CPPCadesCPOIDObject());
    hr_method_check(m_pCppCadesImpl->get_OID(pCPPCadesCPOID));

    return pre_rb_OID(pCPPCadesCPOID);
}

std::string pre_rb_Attribute::get_value(void)
{
    CryptoPro::CBlob blobValue;
    CADESCOM_ATTRIBUTE Name;
    hr_method_check(m_pCppCadesImpl->get_Value(blobValue));
    hr_method_check(m_pCppCadesImpl->get_Name(&Name));

    DWORD dwLen = blobValue.cbData();
    std::vector<BYTE> vbValue(dwLen + 1, 0);
    if (Name != CADESCOM_AUTHENTICATED_ATTRIBUTE_SIGNING_TIME)
    {
        memcpy(&vbValue[0], blobValue.pbData(), dwLen);
    }
    else
    {
        FILETIME fTime;
        DWORD fTimeSize = sizeof(FILETIME);
        CryptStringToBinary(reinterpret_cast<TCHAR *>(blobValue.pbData()), dwLen,
                            CRYPT_STRING_BASE64, &vbValue[0], &dwLen, NULL, NULL);
        CryptDecodeObject(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
                          (LPCSTR)szOID_RSA_signingTime, &vbValue[0], dwLen, 0, &fTime,
                          &fTimeSize);
        CryptoPro::CDateTime Time(fTime);
        CryptoPro::CStringProxy strProxyTime = Time.tostring();
        return std::string(strProxyTime.c_str());
    }
    return reinterpret_cast<TCHAR *>(vbValue.data());
}

void pre_rb_Attribute::set_value(std::string val){
    CADESCOM_ATTRIBUTE name;
    hr_method_check(m_pCppCadesImpl->get_Name(&name));
    if (name == CADESCOM_AUTHENTICATED_ATTRIBUTE_SIGNING_TIME)
    {
        CryptoPro::CDateTime time(val.c_str());
        hr_method_check(m_pCppCadesImpl->put_DateTimeValue(time));
    }
    else
    {
        CryptoPro::CBlob blobValue;
        blobValue.assign(reinterpret_cast<const BYTE*>(val.c_str()), val.length());
        hr_method_check(m_pCppCadesImpl->put_Value(blobValue));
    }
}

long pre_rb_Attribute::get_name(void)
{
      CADESCOM_ATTRIBUTE name;
      hr_method_check(m_pCppCadesImpl->get_Name(&name));
      return static_cast<long>(name);
}

void pre_rb_Attribute::set_name(long name)
{
      hr_method_check(m_pCppCadesImpl->put_Name(static_cast<CADESCOM_ATTRIBUTE>(name)));
}

long pre_rb_Attribute::get_value_encoding(void)
{
      CAPICOM_ENCODING_TYPE type;
      hr_method_check(m_pCppCadesImpl->get_ValueEncoding(&type));
      return static_cast<long>(type);
}

void pre_rb_Attribute::set_value_encoding(long type)
{
    hr_method_check(m_pCppCadesImpl->put_ValueEncoding(static_cast<CAPICOM_ENCODING_TYPE>(type)));
}

void pre_rb_Attribute::define_ruby_class(VALUE module)
{
  Data_Type<pre_rb_Attribute> rb_cAttribute =
    define_class_under<pre_rb_Attribute>(module, "Attribute")
    .define_constructor(Constructor<pre_rb_Attribute>())
    .define_method("oid", &pre_rb_Attribute::get_OID)
    .define_method("name", &pre_rb_Attribute::get_name)
    .define_method("name=", &pre_rb_Attribute::set_name)
    .define_method("value", &pre_rb_Attribute::get_value)
    .define_method("value=", &pre_rb_Attribute::set_value)
    .define_method("value_type", &pre_rb_Attribute::get_value_encoding)
    .define_method("value_type=", &pre_rb_Attribute::set_value_encoding);
}
}
