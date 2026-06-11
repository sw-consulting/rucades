// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_enveloped_data.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_EnvelopedData::pre_rb_EnvelopedData(void):
      m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesCPEnvelopedDataObject>(new CPPCadesCPEnvelopedDataObject())) { }

std::string pre_rb_EnvelopedData::get_content(void)
{
    CStringBlob content;
    hr_method_check(m_pCppCadesImpl->get_Content(content));
    return std::string(content);
}

void pre_rb_EnvelopedData::set_content(std::string content)
{
    CAtlString sContent = CAtlString(content.c_str());
    hr_method_check(m_pCppCadesImpl->put_Content(sContent.GetString(), sContent.GetLength()));
}

long pre_rb_EnvelopedData::get_content_encoding(void)
{
    CADESCOM_CONTENT_ENCODING_TYPE enc;
    hr_method_check(m_pCppCadesImpl->get_ContentEncoding(&enc));
    return static_cast<long>(enc);
}

void pre_rb_EnvelopedData::set_content_encoding(long enc)
{
    hr_method_check(m_pCppCadesImpl->put_ContentEncoding(static_cast<CADESCOM_CONTENT_ENCODING_TYPE>(enc)));
}

pre_rb_Recipients pre_rb_EnvelopedData::get_recipients(void)
{
    pre_rb_Recipients pRecipients;
    hr_method_check(m_pCppCadesImpl->get_Recipients(pRecipients.m_pCppCadesImpl));
    return pRecipients;
}

pre_rb_Algorithm pre_rb_EnvelopedData::get_algorithm(void)
{
    pre_rb_Algorithm pAlgorithm;
    hr_method_check(m_pCppCadesImpl->get_Algorithm(pAlgorithm.m_pCppCadesImpl));
    return pAlgorithm;
}

std::string pre_rb_EnvelopedData::encrypt(long enc)
{
    CAPICOM_ENCODING_TYPE EncodingType = static_cast<CAPICOM_ENCODING_TYPE>(enc);
    CryptoPro::CBlob blobData;
    hr_method_check(m_pCppCadesImpl->Encrypt(EncodingType, blobData));
    CAtlString sData = CAtlString(reinterpret_cast<const TCHAR *>(blobData.pbData()), blobData.cbData());
    return std::string(sData.GetString());
}

void pre_rb_EnvelopedData::decrypt(std::string data)
{
    CryptoPro::CBlob blobData;
    blobData.assign(reinterpret_cast<const unsigned char *>(data.c_str()), data.length());
    hr_method_check(m_pCppCadesImpl->Decrypt(blobData));
}

std::string pre_rb_EnvelopedData::stream_encrypt(std::string content, int final)
{
    int bIsFinal = final ? TRUE : FALSE;
    CAtlString sData = CAtlString(CA2CT(CAtlStringA(content.c_str()), CP_UTF8));
    CryptoPro::CBlob blobResult;
    hr_method_check(m_pCppCadesImpl->StreamEncrypt(
            sData.GetString(), sData.GetLength(), bIsFinal, blobResult));

    CAtlString sResult;
    if (blobResult.cbData())
    {
        sResult = CAtlString(reinterpret_cast<const TCHAR *>(blobResult.pbData()), blobResult.cbData());
    }
    return std::string(sResult.GetString());
}

std::string pre_rb_EnvelopedData::stream_decrypt(std::string content, int final)
{
    int bIsFinal = final ? TRUE : FALSE;
    CAtlString sData = CAtlString(CA2CT(CAtlStringA(content.c_str()), CP_UTF8));
    CryptoPro::CBlob blobResult;
    hr_method_check(m_pCppCadesImpl->StreamDecrypt(
            sData.GetString(), sData.GetLength(), bIsFinal, blobResult));

    CAtlString sResult;
    if (blobResult.cbData())
    {
        sResult = CAtlString((const char *)blobResult.pbData(), blobResult.cbData());
    }
    return std::string(sResult.GetString());
}

void pre_rb_EnvelopedData::define_ruby_class(VALUE module)
{
  Data_Type<pre_rb_EnvelopedData> rb_cEnvelopedData =
    define_class_under<pre_rb_EnvelopedData>(module, "EnvelopedData")
    .define_constructor(Constructor<pre_rb_EnvelopedData>())
    .define_method("content", &pre_rb_EnvelopedData::get_content)
    .define_method("content=", &pre_rb_EnvelopedData::set_content)
    .define_method("content_encoding", &pre_rb_EnvelopedData::get_content_encoding)
    .define_method("content_encoding=", &pre_rb_EnvelopedData::set_content_encoding)
    .define_method("recipients", &pre_rb_EnvelopedData::get_recipients)
    .define_method("algorithm", &pre_rb_EnvelopedData::get_algorithm)
    .define_method("encrypt", &pre_rb_EnvelopedData::encrypt,
                   Arg("enc") = static_cast<long>(CADESCOM_STRING_TO_UCS2LE))
    .define_method("decrypt", &pre_rb_EnvelopedData::decrypt)
    .define_method("stream_encrypt", &pre_rb_EnvelopedData::stream_encrypt)
    .define_method("stream_decrypt", &pre_rb_EnvelopedData::stream_decrypt);
}
}
