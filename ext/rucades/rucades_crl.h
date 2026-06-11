// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "CPPCadesCPCRL.h"

namespace rucades {

class pre_rb_CRL {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPCRLObject> m_pCppCadesImpl;
  public:
    pre_rb_CRL(void);
    std::string get_auth_key_id(void);
    std::string get_issuer_name(void);
    std::string get_next_update(void);
    std::string get_this_update(void);
    std::string get_thumbprint(void);
    void crl_import(std::string& crl);
    std::string crl_export(long type);

    static void define_ruby_class(VALUE module);

    friend class pre_rb_Store;
};
}
