// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "rucades_certificate.h"
#include "CPPCadesSymmetricAlgorithm.h"

namespace rucades {
class pre_rb_SymmetricAlgorithm {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesSymmetricAlgorithmObject> m_pCppCadesImpl;
  public:
    pre_rb_SymmetricAlgorithm(void);
    pre_rb_SymmetricAlgorithm(NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesSymmetricAlgorithmObject> other);
    std::string get_divers_data(void);
    void set_divers_data(std::string data);
    std::string get_iv(void);
    void set_iv(std::string iv);
    std::string encrypt(std::string data, bool final);
    std::string decrypt(std::string data, bool final);
    pre_rb_SymmetricAlgorithm diversify_key(void);
    void generate_key(long alg);
    std::string export_key(pre_rb_Certificate& cert);
    void import_key(std::string key, pre_rb_Certificate& cert, std::string password);
    static void define_ruby_class(VALUE module);
};
}
