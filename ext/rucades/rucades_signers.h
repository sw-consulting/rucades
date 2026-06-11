// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "rucades_signers.h"
#include "rucades_signer.h"
#include "CPPCadesCollections.h"

namespace rucades {
class pre_rb_Signers {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPSignersObject> m_pCppCadesImpl;
  public:
    pre_rb_Signers(void);
    pre_rb_Signers(NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPSignersObject> other);
    void add(pre_rb_Signers& signer);
    long get_count(void);
    pre_rb_Signer get_item(long index);

    static void define_ruby_class(VALUE module);

    friend class pre_rb_SignedData;
};
}
