// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "CPPCadesCPPrivateKey.h"

namespace rucades {

class pre_rb_PrivateKey {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPPrivateKeyObject> m_pCppCadesImpl;
  public:
    pre_rb_PrivateKey(void);
    pre_rb_PrivateKey(NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPPrivateKeyObject> other);
    std::string get_container_name(void);
    std::string get_unique_container_name(void);
    std::string get_provider_name(void);
    long get_provider_type(void);
    long get_key_spec(void);
    void set_cache_pin(int pin);
    void set_key_pin(std::string pin);
    void change_pin(void);

    static void define_ruby_class(VALUE module);

    friend class pre_rb_Certificate;
};
}
