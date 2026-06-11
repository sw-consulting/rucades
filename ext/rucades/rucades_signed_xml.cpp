// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_signed_xml.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_SignedXML::pre_rb_SignedXML(void):
    m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesSignedXMLObject>(new CPPCadesSignedXMLObject())) { }

std::string pre_rb_SignedXML::get_content(void)
{
    CStringBlob strBlobContent;
    hr_method_check(m_pCppCadesImpl->get_Content(strBlobContent));
    return std::string(strBlobContent.GetString());
}

void pre_rb_SignedXML::set_content(std::string content)
{
    CStringBlob strBlobContent(content.c_str());
    hr_method_check(m_pCppCadesImpl->put_Content(strBlobContent));
}

void pre_rb_SignedXML::set_signature_type(long type)
{
    CADESCOM_XML_SIGNATURE_TYPE SignatureType = static_cast<CADESCOM_XML_SIGNATURE_TYPE>(type);
    hr_method_check(m_pCppCadesImpl->put_SignatureType(SignatureType));
}

void pre_rb_SignedXML::set_digest_method(std::string method)
{
    CStringBlob strBlobMethod(method.c_str());
    hr_method_check(m_pCppCadesImpl->put_DigestMethod(strBlobMethod));
}

void pre_rb_SignedXML::set_signature_method(std::string method)
{
    CStringBlob strBlobMethod(method.c_str());
    hr_method_check(m_pCppCadesImpl->put_SignatureMethod(strBlobMethod));
}

pre_rb_Signers pre_rb_SignedXML::get_signers(void)
{
    NS_SHARED_PTR::shared_ptr<CPPCadesCPSignersObject> pSigners = NS_SHARED_PTR::shared_ptr<CPPCadesCPSignersObject>(new CPPCadesCPSignersObject());
    hr_method_check(m_pCppCadesImpl->get_Signers(pSigners));
    return pre_rb_Signers(pSigners);
}

std::string pre_rb_SignedXML::sign(pre_rb_Signer& signer, std::string xpath)
{
    CStringBlob strBlobXPath(xpath.c_str(), xpath.length());
    CStringBlob strBlobResult;
    hr_method_check(m_pCppCadesImpl->Sign(signer.m_pCppCadesImpl, strBlobXPath, strBlobResult));
    return std::string(strBlobResult.GetString(), strBlobResult.GetLength());
}

void pre_rb_SignedXML::verify(std::string msg, std::string xpath)
{
    CStringBlob strBlobMessage(msg.c_str(), msg.length());
    CStringBlob strBlobXPath(xpath.c_str(), xpath.length());
    hr_method_check(m_pCppCadesImpl->Verify(strBlobMessage, strBlobXPath));
}

void pre_rb_SignedXML::define_ruby_class(VALUE module)
{
    Data_Type<pre_rb_SignedXML> rb_cSignedXML =
        define_class_under<pre_rb_SignedXML>(module, "SignedXML")
        .define_constructor(Constructor<pre_rb_SignedXML>())
        .define_method("content", &pre_rb_SignedXML::get_content)
        .define_method("content=", &pre_rb_SignedXML::set_content)
        .define_method("signature_type=", &pre_rb_SignedXML::set_signature_type)
        .define_method("digest_method=", &pre_rb_SignedXML::set_digest_method)
        .define_method("signature_method=", &pre_rb_SignedXML::set_signature_method)
        .define_method("signers", &pre_rb_SignedXML::get_signers)
        .define_method("sign", &pre_rb_SignedXML::sign,
                  Arg("signer"), Arg("xpath") = std::string(""))
        .define_method("verify", &pre_rb_SignedXML::verify,
                  Arg("msg"), Arg("xpath") = std::string(""));
}
}
