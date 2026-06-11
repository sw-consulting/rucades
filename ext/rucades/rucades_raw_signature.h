// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "rucades_hashed_data.h"
#include "rucades_certificate.h"
#include "CPPCadesRawSignature.h"

namespace rucades {

class pre_rb_RawSignature {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesRawSignatureObject> m_pCppCadesImpl;
  public:
    pre_rb_RawSignature(void);
    pre_rb_RawSignature(NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesRawSignatureObject> other);
    std::string sign_hash(pre_rb_HashedData& data, pre_rb_Certificate& cert);
    void verify_hash(pre_rb_HashedData& data, pre_rb_Certificate& cert, std::string signature);

    static void define_ruby_class(VALUE module);
};

}
