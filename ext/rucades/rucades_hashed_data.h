// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "CPPCadesCPHashedData.h"

namespace rucades {
class pre_rb_HashedData {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPHashedDataObject> m_pCppCadesImpl;
  public:
    pre_rb_HashedData(void);
    std::string get_key(void);
    void set_key(std::string key);
    long get_algorithm(void);
    void set_algorithm(long alg);
    long get_data_encoding(void);
    void set_data_encoding(long enc);
    std::string get_value(void);
    void hash(std::string data);
    void set_hash_value(std::string data);

    static void define_ruby_class(VALUE module);

    friend class pre_rb_RawSignature;
    friend class pre_rb_SignedData;
};
}
