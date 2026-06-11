// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "rucades_hashed_data.h"
#include "rucades_signer.h"
#include "rucades_signers.h"
#include "rucades_store.h"
#include "CPPCadesCPSignedData.h"

namespace rucades {
class pre_rb_SignedData {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesSignedDataObject> m_pCppCadesImpl;
  public:
    pre_rb_SignedData(void);
    long get_content_encoding(void);
    void set_content_encoding(long enc);
    std::string get_content(void);
    void set_content(std::string content);
    pre_rb_Signers get_signers(void);
    pre_rb_Certificates get_certificates(void);

    std::string sign_cades(pre_rb_Signer* signer, long type, bool detached, long enc);
    std::string cosign_cades(pre_rb_Signer* signer, long type, long enc);
    std::string sign_hash(pre_rb_HashedData& hash, pre_rb_Signer* signer, long type, long enc);
    std::string cosign_hash(pre_rb_HashedData& hash, pre_rb_Signer* signer, long type, long enc);
    std::string sign(pre_rb_Signer* signer, bool detached, long enc);
    std::string cosign(pre_rb_Signer* signer, long enc);
    std::string enhance_cades(long type, std::string addr, long enc);
    void verify(std::string msg, bool detached, long verify_flag);
    void verify_cades(std::string msg, long type, bool detached);
    void verify_hash(pre_rb_HashedData& hash, std::string msg, long type);
    void additional_store(pre_rb_Store& hash);

    static void define_ruby_class(VALUE module);
};
}
