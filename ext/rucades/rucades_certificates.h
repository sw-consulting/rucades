// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "rucades_certificate.h"

#include "CPPCadesCPCertificates.h"

namespace rucades {
class pre_rb_Certificates {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPCertificatesObject> m_pCppCadesImpl;
  public:
    pre_rb_Certificates(void);
    pre_rb_Certificates(NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPCertificatesObject> pCppCadesCertificates);
    long get_count(void);
    bool has_any(void);
    pre_rb_Certificate get_item(long index);

    pre_rb_Certificates internal_find_query_long(long type, long query, bool valid_only);
    pre_rb_Certificates internal_find_query_string(long type, std::string query, bool valid_only);

    static void define_ruby_class(VALUE module);

    friend class pre_rb_SignedData;
    friend class pre_rb_Store;
};
}
