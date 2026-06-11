// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "rucades_attributes.h"
#include "rucades_blobs.h"
#include "rucades_certificates.h"
#include "CPPCadesCPSigner.h"

namespace rucades {
class pre_rb_Signer {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPSignerObject> m_pCppCadesImpl;
  public:
    pre_rb_Signer(void);
    pre_rb_Signer(NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPSignerObject> other);

    pre_rb_Certificate* get_certificate(void);
    void set_certificate(pre_rb_Certificate& crt);
    bool get_check_certificate(void);
    void set_check_certificate(bool value);
    long get_options(void);
    void set_options(long opts);
    std::string get_tsa_address(void);
    void set_tsa_address(std::string addr);
    pre_rb_Attributes get_unauthenticated_attributes(void);
    void set_unauthenticated_attributes(pre_rb_Attributes& attrb);
    pre_rb_Attributes get_authenticated_attributes(void);
    void set_authenticated_attributes(pre_rb_Attributes& attrb);
    pre_rb_Blobs get_crls(void);
    pre_rb_Blobs get_ocsp_responses(void);
    std::string get_signing_time(void);
    std::string get_signature_time_stamp_time(void);
    void set_key_pin(std::string pin);

    static void define_ruby_class(VALUE module);

    friend class pre_rb_SignedData;
    friend class pre_rb_Signers;
    friend class pre_rb_SignedXML;
};
}
