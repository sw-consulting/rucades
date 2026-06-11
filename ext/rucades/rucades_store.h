// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "rucades_certificate.h"
#include "rucades_certificates.h"
#include "rucades_crl.h"

#include "CPPCadesCPStore.h"

namespace rucades {
class pre_rb_Store {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPStoreObject> m_pCppCadesImpl;
  public:
    pre_rb_Store(void);

    std::string get_name(void);
    pre_rb_Certificates get_certificates(void);
    long get_location(void);
    void open(long location, std::string& name, long mode);
    void close(void);
    void add(pre_rb_Certificate& cert);
    void add_crl(pre_rb_CRL& crl);

    static void define_ruby_class(VALUE module);

    friend class pre_rb_Certificate;
    friend class pre_rb_SignedData;
};
}
