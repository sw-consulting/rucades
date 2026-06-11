// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "CPPCadesCPKeyUsage.h"

namespace rucades {
class pre_rb_KeyUsage {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPKeyUsageObject> m_pCppCadesImpl;
  public:
    pre_rb_KeyUsage(void);
    pre_rb_KeyUsage(NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPKeyUsageObject> other);
    bool is_present(void);
    bool is_critical(void);
    bool is_digital_signature_enabled(void);
    bool is_non_repudiation_enabled(void);
    bool is_key_encipherment_enabled(void);
    bool is_key_agreement_enabled(void);
    bool is_key_cert_sign_enabled(void);
    bool is_data_encipherment_enabled(void);
    bool is_crl_sign_enabled(void);
    bool is_encipher_only_enabled(void);
    bool is_decipher_only_enabled(void);

    static void define_ruby_class(VALUE module);

    friend class pre_rb_Certificate;
};
}
