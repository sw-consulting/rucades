// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "CPPCadesCPCertificateStatus.h"

namespace rucades {
class pre_rb_CertificateStatus {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPCertificateStatusObject> m_pCppCadesImpl;
  public:
    pre_rb_CertificateStatus(void);
    pre_rb_CertificateStatus(NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPCertificateStatusObject> other);
    bool result(void);

    static void define_ruby_class(VALUE module);

    friend class pre_rb_Certificate;
};
}
