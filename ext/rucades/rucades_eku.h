// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "CPPCadesCPEKU.h"

namespace rucades {
class pre_rb_EKU {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPEKUObject> m_pCppCadesImpl;
  public:
    pre_rb_EKU(void);
    pre_rb_EKU(NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPEKUObject> pCppCadesEKU);
    long get_name(void);
    void set_name (long name);
    std::string get_oid(void);
    void set_oid(std::string& sFriendlyName);

    static void define_ruby_class(VALUE module);

    friend class pre_rb_EKUs;
};
}
