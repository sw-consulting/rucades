// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "CPPCadesCPOID.h"

namespace rucades {

class pre_rb_OID {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPOIDObject> m_pCppCadesImpl;
  public:
    pre_rb_OID(void);
    pre_rb_OID(NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPOIDObject> other);
    std::string get_value(void);
    void set_value(std::string& value);
    long get_name(void);
    void set_name (long name);
    std::string get_friendly_name(void);
    void set_friendly_name(std::string& sFriendlyName);

    static void define_ruby_class(VALUE module);

    friend class pre_rb_PublicKey;
};

}
