// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "rucades_ekus.h"

#include "CPPCadesCPExtendedKeyUsage.h"

namespace rucades {
class pre_rb_ExtendedKeyUsage {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPExtendedKeyUsageObject> m_pCppCadesImpl;
  public:
    pre_rb_ExtendedKeyUsage(void);
    pre_rb_ExtendedKeyUsage(NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPExtendedKeyUsageObject> other);
    bool is_present(void);
    bool is_critical(void);
    pre_rb_EKUs get_ekus(void);

    static void define_ruby_class(VALUE module);

    friend class pre_rb_Certificate;
};
}
