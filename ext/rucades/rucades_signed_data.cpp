// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_signed_data.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_SignedData::pre_rb_SignedData(void):
    m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesSignedDataObject>(new CPPCadesSignedDataObject())) { }

long pre_rb_SignedData::get_content_encoding(void)
{
    CADESCOM_CONTENT_ENCODING_TYPE Type;
    hr_method_check(m_pCppCadesImpl->get_ContentEncoding(&Type));
    return static_cast<long>(Type);
}

void pre_rb_SignedData::set_content_encoding(long enc)
{
    CADESCOM_CONTENT_ENCODING_TYPE Type = static_cast<CADESCOM_CONTENT_ENCODING_TYPE>(enc);
    hr_method_check(m_pCppCadesImpl->put_ContentEncoding(Type));
}

std::string pre_rb_SignedData::get_content(void)
{

    CStringBlob strBlobValue;
    hr_method_check(m_pCppCadesImpl->get_Content(strBlobValue));
    CAtlString sValue = CAtlString(reinterpret_cast<const char *>(strBlobValue.GetString()), strBlobValue.GetLength());
    return std::string(sValue.GetString());
}

void pre_rb_SignedData::set_content(std::string content)
{
    CAtlString sContent = CAtlString(content.c_str());
    hr_method_check(m_pCppCadesImpl->put_Content(sContent.GetString(), sContent.GetLength()));
}

pre_rb_Signers pre_rb_SignedData::get_signers(void)
{
    pre_rb_Signers pSigners;
    hr_method_check(m_pCppCadesImpl->get_Signers(pSigners.m_pCppCadesImpl));
    return pSigners;
}

pre_rb_Certificates pre_rb_SignedData::get_certificates(void)
{
    pre_rb_Certificates pCertificates;
    hr_method_check(m_pCppCadesImpl->get_Certificates(pCertificates.m_pCppCadesImpl));
    return pCertificates;
}

std::string pre_rb_SignedData::sign_cades(pre_rb_Signer* signer, long type, bool detached, long enc)
{
    CAPICOM_ENCODING_TYPE EncodingType = static_cast<CAPICOM_ENCODING_TYPE>(enc);
    CADESCOM_CADES_TYPE CadesType = static_cast<CADESCOM_CADES_TYPE>(type);
    CryptoPro::CBlob blobSignedMessage;

    NS_SHARED_PTR::shared_ptr<CPPCadesCPSignerObject> pSignerCppCadesImpl;
    if (signer) {
        pSignerCppCadesImpl = signer->m_pCppCadesImpl;
    }

    hr_method_check(m_pCppCadesImpl->SignCades(pSignerCppCadesImpl,
                                               CadesType,
                                               detached ? TRUE : FALSE,
                                               EncodingType,
                                               &blobSignedMessage));
    return std::string(reinterpret_cast<const char *>(blobSignedMessage.pbData()), blobSignedMessage.cbData());
}

std::string pre_rb_SignedData::cosign_cades(pre_rb_Signer* signer, long type, long enc)
{
    CAPICOM_ENCODING_TYPE EncodingType = static_cast<CAPICOM_ENCODING_TYPE>(enc);
    CADESCOM_CADES_TYPE CadesType = static_cast<CADESCOM_CADES_TYPE>(type);
    CryptoPro::CBlob blobSignedMessage;

    NS_SHARED_PTR::shared_ptr<CPPCadesCPSignerObject> pSignerCppCadesImpl;
    if (signer) {
        pSignerCppCadesImpl = signer->m_pCppCadesImpl;
    }
    hr_method_check(m_pCppCadesImpl->CoSignCades(pSignerCppCadesImpl,
                                                 CadesType,
                                                 EncodingType,
                                                 &blobSignedMessage));
    return std::string(reinterpret_cast<const char *>(blobSignedMessage.pbData()), blobSignedMessage.cbData());
}

std::string pre_rb_SignedData::sign_hash(pre_rb_HashedData& hash, pre_rb_Signer* signer, long type, long enc)
{
    CAPICOM_ENCODING_TYPE EncodingType = static_cast<CAPICOM_ENCODING_TYPE>(enc);
    CADESCOM_CADES_TYPE CadesType = static_cast<CADESCOM_CADES_TYPE>(type);
    CryptoPro::CBlob blobSignedMessage;

    NS_SHARED_PTR::shared_ptr<CPPCadesCPSignerObject> pSignerCppCadesImpl;
    if (signer) {
        pSignerCppCadesImpl = signer->m_pCppCadesImpl;
    }
    hr_method_check(m_pCppCadesImpl->SignHash(pSignerCppCadesImpl,
                                              hash.m_pCppCadesImpl,
                                              CadesType,
                                              EncodingType,
                                              &blobSignedMessage));
    return std::string(reinterpret_cast<const char *>(blobSignedMessage.pbData()), blobSignedMessage.cbData());
}

std::string pre_rb_SignedData::cosign_hash(pre_rb_HashedData& hash, pre_rb_Signer* signer, long type, long enc)
{
    CAPICOM_ENCODING_TYPE EncodingType = static_cast<CAPICOM_ENCODING_TYPE>(enc);
    CADESCOM_CADES_TYPE CadesType = static_cast<CADESCOM_CADES_TYPE>(type);
    CryptoPro::CBlob blobSignedMessage;

    NS_SHARED_PTR::shared_ptr<CPPCadesCPSignerObject> pSignerCppCadesImpl;
    if (signer) {
        pSignerCppCadesImpl = signer->m_pCppCadesImpl;
    }
    hr_method_check(m_pCppCadesImpl->CoSignHash(pSignerCppCadesImpl,
                                                hash.m_pCppCadesImpl,
                                                CadesType,
                                                EncodingType,
                                                &blobSignedMessage));
    return std::string(reinterpret_cast<const char *>(blobSignedMessage.pbData()), blobSignedMessage.cbData());
}

std::string pre_rb_SignedData::sign(pre_rb_Signer* signer, bool detached, long enc)
{
    CAPICOM_ENCODING_TYPE EncodingType = static_cast<CAPICOM_ENCODING_TYPE>(enc);
    CryptoPro::CBlob blobSignedMessage;

    NS_SHARED_PTR::shared_ptr<CPPCadesCPSignerObject> pSignerCppCadesImpl;
    if (signer) {
        pSignerCppCadesImpl = signer->m_pCppCadesImpl;
    }
    hr_method_check(m_pCppCadesImpl->Sign(pSignerCppCadesImpl,
                                          detached ? TRUE : FALSE,
                                          EncodingType,
                                          &blobSignedMessage));
    return std::string(reinterpret_cast<const char *>(blobSignedMessage.pbData()), blobSignedMessage.cbData());
}

std::string pre_rb_SignedData::cosign(pre_rb_Signer* signer, long enc)
{
    CAPICOM_ENCODING_TYPE EncodingType = static_cast<CAPICOM_ENCODING_TYPE>(enc);
    CryptoPro::CBlob blobSignedMessage;

    NS_SHARED_PTR::shared_ptr<CPPCadesCPSignerObject> pSignerCppCadesImpl;
    if (signer) {
        pSignerCppCadesImpl = signer->m_pCppCadesImpl;
    }
    hr_method_check(m_pCppCadesImpl->CoSign(pSignerCppCadesImpl,
                                            EncodingType,
                                            &blobSignedMessage));
    return std::string(reinterpret_cast<const char *>(blobSignedMessage.pbData()), blobSignedMessage.cbData());
}

std::string pre_rb_SignedData::enhance_cades(long type, std::string addr, long enc)
{
    CryptoPro::CBlob blobValue;
    CADESCOM_CADES_TYPE CadesType = static_cast<CADESCOM_CADES_TYPE>(type);
    CAPICOM_ENCODING_TYPE EncodingType = static_cast<CAPICOM_ENCODING_TYPE>(enc);

    hr_method_check(m_pCppCadesImpl->EnhanceCades(CadesType, CAtlString(addr.c_str()), EncodingType, &blobValue));
    return std::string(reinterpret_cast<const char *>(blobValue.pbData()), blobValue.cbData());
}

void pre_rb_SignedData::verify(std::string msg, bool detached, long verify_flag)
{
    CAPICOM_SIGNED_DATA_VERIFY_FLAG VerifyFlag = static_cast<CAPICOM_SIGNED_DATA_VERIFY_FLAG>(verify_flag);
    CryptoPro::CBlob blobSignedMessage;
    blobSignedMessage.assign(reinterpret_cast<const unsigned char *>(msg.c_str()), msg.length());
    hr_method_check(m_pCppCadesImpl->Verify(blobSignedMessage, detached ? TRUE : FALSE, VerifyFlag));
}
void pre_rb_SignedData::verify_cades(std::string msg, long type, bool detached)
{
    CADESCOM_CADES_TYPE CadesType = static_cast<CADESCOM_CADES_TYPE>(type);
    CryptoPro::CBlob blobSignedMessage;
    blobSignedMessage.assign(reinterpret_cast<const unsigned char *>(msg.c_str()), msg.length());
    hr_method_check(m_pCppCadesImpl->VerifyCades(blobSignedMessage, CadesType, detached ? TRUE : FALSE));
}

void pre_rb_SignedData::verify_hash(pre_rb_HashedData& hash, std::string msg, long type)
{
    CADESCOM_CADES_TYPE CadesType = static_cast<CADESCOM_CADES_TYPE>(type);
    CryptoPro::CBlob blobSignedMessage;
    blobSignedMessage.assign(reinterpret_cast<const unsigned char *>(msg.c_str()), msg.length());

    hr_method_check(m_pCppCadesImpl->VerifyHash(hash.m_pCppCadesImpl, blobSignedMessage, CadesType));
}

void pre_rb_SignedData::additional_store(pre_rb_Store& store)
{
    hr_method_check(m_pCppCadesImpl->AdditionalStore(store.m_pCppCadesImpl));
}

void pre_rb_SignedData::define_ruby_class(VALUE module)
{
    Data_Type<pre_rb_SignedData> rb_cSignedData = define_class_under<pre_rb_SignedData>(module, "SignedData")
        .define_constructor(Constructor<pre_rb_SignedData>())
        .define_method("content_encoding", &pre_rb_SignedData::get_content_encoding)
        .define_method("content_encoding=", &pre_rb_SignedData::set_content_encoding)
        .define_method("content", &pre_rb_SignedData::get_content)
        .define_method("content=", &pre_rb_SignedData::set_content)
        .define_method("signers", &pre_rb_SignedData::get_signers)
        .define_method("certificates", &pre_rb_SignedData::get_certificates)
        .define_method("sign_cades", &pre_rb_SignedData::sign_cades,
                      Arg("signer") =  nullptr,
                      Arg("type") = static_cast<long>(CADESCOM_CADES_DEFAULT),
                      Arg("detached") = false,
                      Arg("enc") = static_cast<long>(CAPICOM_ENCODE_BASE64))
        .define_method("cosign_cades", &pre_rb_SignedData::cosign_cades,
                      Arg("signer") =  nullptr,
                      Arg("type") = static_cast<long>(CADESCOM_CADES_DEFAULT),
                      Arg("enc") = static_cast<long>(CAPICOM_ENCODE_BASE64))
        .define_method("sign_hash", &pre_rb_SignedData::sign_hash,
                      Arg("hash"),
                      Arg("signer") =  nullptr,
                      Arg("type") = static_cast<long>(CADESCOM_CADES_DEFAULT),
                      Arg("enc") = static_cast<long>(CAPICOM_ENCODE_BASE64))
        .define_method("cosign_hash", &pre_rb_SignedData::cosign_hash,
                      Arg("hash"),
                      Arg("signer") =  nullptr,
                      Arg("type") = static_cast<long>(CADESCOM_CADES_DEFAULT),
                      Arg("enc") = static_cast<long>(CAPICOM_ENCODE_BASE64))
        .define_method("sign", &pre_rb_SignedData::sign,
                      Arg("signer") =  nullptr,
                      Arg("detached") = false,
                      Arg("enc") = static_cast<long>(CAPICOM_ENCODE_BASE64))
        .define_method("cosign", &pre_rb_SignedData::cosign,
                      Arg("signer") =  nullptr,
                      Arg("enc") = static_cast<long>(CAPICOM_ENCODE_BASE64))
        .define_method("enhance_cades", &pre_rb_SignedData::enhance_cades,
                      Arg("type") = static_cast<long>(CADESCOM_CADES_DEFAULT),
                      Arg("addr") = std::string(""),
                      Arg("enc") = static_cast<long>(CAPICOM_ENCODE_BASE64))
        .define_method("verify", &pre_rb_SignedData::verify,
                      Arg("msg"),
                      Arg("detached") = false,
                      Arg("verify_flag") = static_cast<long>(CAPICOM_VERIFY_SIGNATURE_ONLY))
        .define_method("verify_cades", &pre_rb_SignedData::verify_cades,
                      Arg("msg"),
                      Arg("type") = static_cast<long>(CADESCOM_CADES_DEFAULT),
                      Arg("detached") = false)
        .define_method("verify_hash", &pre_rb_SignedData::verify_hash)
        .define_method("additional_store", &pre_rb_SignedData::additional_store);
}
}
