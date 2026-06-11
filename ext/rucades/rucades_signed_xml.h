// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "rucades_signer.h"
#include "rucades_signers.h"
#include "CPPCadesSignedXML.h"

namespace rucades {
class pre_rb_SignedXML {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesSignedXMLObject> m_pCppCadesImpl;
  public:
    pre_rb_SignedXML(void);
    std::string get_content(void);
    void set_content(std::string content);
    void set_signature_type(long type);
    void set_digest_method(std::string method);
    void set_signature_method(std::string method);
    pre_rb_Signers get_signers(void);
    std::string sign(pre_rb_Signer& signer, std::string xpath);
    void verify(std::string msg, std::string xpath);

    static void define_ruby_class(VALUE module);
};
}
