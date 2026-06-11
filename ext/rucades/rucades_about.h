// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "rucades_version.h"
#include "CPPCadesAbout.h"

namespace rucades {
class pre_rb_About {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesAboutObject> m_pCppCadesImpl;
  public:
    pre_rb_About(void);
    unsigned int major_version(void);
    unsigned int minor_version(void);
    unsigned int build_version(void);
    std::string version(void);
    pre_rb_Version plugin_version(void);
    pre_rb_Version csp_version(std::string prov_name, long prov_type);

    static void define_ruby_class(VALUE module);
};
}
