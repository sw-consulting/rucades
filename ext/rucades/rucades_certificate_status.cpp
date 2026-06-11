// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_certificate_status.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_CertificateStatus::pre_rb_CertificateStatus(void):
      m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificateStatusObject>(new CPPCadesCPCertificateStatusObject())) { }

pre_rb_CertificateStatus::pre_rb_CertificateStatus(NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificateStatusObject> other):
      m_pCppCadesImpl(other) { }

bool pre_rb_CertificateStatus::result(void)
{
    BOOL bResult = 0;
    hr_method_check(m_pCppCadesImpl->get_Result(&bResult));
    return (bResult != 0);
}

void pre_rb_CertificateStatus::define_ruby_class(VALUE module)
{
    Data_Type<pre_rb_CertificateStatus> rb_cCertificateStatus =
        define_class_under<pre_rb_CertificateStatus>(module, "CertificateStatus")
        .define_constructor(Constructor<pre_rb_CertificateStatus>())
        .define_method("result?", &pre_rb_CertificateStatus::result);
}

}