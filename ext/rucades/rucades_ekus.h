// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "rucades_eku.h"

#include "CPPCadesCollections.h"
#include "CPPCadesCPEKU.h"

namespace rucades {
class pre_rb_EKUs {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPEKUsObject> m_pCppCadesImpl;
  public:
    pre_rb_EKUs(void);
    pre_rb_EKUs(NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPEKUsObject> pCppCadesEKUs);
    long get_count(void);
    pre_rb_EKU get_item(long index);

    static void define_ruby_class(VALUE module);

    friend class pre_rb_ExtendedKeyUsage;
};
}
