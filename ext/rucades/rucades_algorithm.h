// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "CPPCadesCPAlgorithm.h"

namespace rucades {

class pre_rb_Algorithm {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPAlgorithmObject> m_pCppCadesImpl;
  public:
    pre_rb_Algorithm(void);
    pre_rb_Algorithm(NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPAlgorithmObject> other);
    long get_name(void);
    void set_name(long name);
    long get_key_length(void);
    void set_key_length(long len);

    static void define_ruby_class(VALUE module);

    friend class pre_rb_EnvelopedData;
};

}
