// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "CPPCadesCPBasicConstraints.h"

namespace rucades {
class pre_rb_BasicConstraints {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPBasicConstraintsObject> m_pCppCadesImpl;
  public:
    pre_rb_BasicConstraints(void);
    pre_rb_BasicConstraints(NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPBasicConstraintsObject> other);
    bool is_ceritficate_authority(void);
    bool is_critical(void);
    bool is_path_len_constraint_present(void);
    bool is_present(void);
    long get_path_len_constraint(void);

    static void define_ruby_class(VALUE module);

    friend class pre_rb_Certificate;
};
}
