// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "rucades_encoded_data.h"
#include "rucades_oid.h"
#include "CPPCadesCPPublicKey.h"

namespace rucades {
class pre_rb_PublicKey {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPPublicKeyObject> m_pCppCadesImpl;
  public:
    pre_rb_PublicKey(void);
    pre_rb_PublicKey(NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPPublicKeyObject> other);
    pre_rb_OID* get_algorithm(void);
    pre_rb_EncodedData get_encoded_key(void);
    pre_rb_EncodedData get_encoded_parameters(void);
    long get_length(void);

    static void define_ruby_class(VALUE module);

    friend class pre_rb_Certificate;
};
}
