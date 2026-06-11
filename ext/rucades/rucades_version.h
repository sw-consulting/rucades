// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "CPPVersion.h"

namespace rucades {
class pre_rb_Version {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPVersionObject> m_pCppCadesImpl;
  public:
    pre_rb_Version(void);
    pre_rb_Version(NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPVersionObject> other);
    unsigned int major_version(void);
    unsigned int minor_version(void);
    unsigned int build_version(void);
    std::string to_s(void);

    static void define_ruby_class(VALUE module);
};
}
