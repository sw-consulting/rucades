// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_signature_status.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_SignatureStatus::pre_rb_SignatureStatus(void):
    m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesSignatureStatusObject>(new CPPCadesSignatureStatusObject())) { }

pre_rb_SignatureStatus::pre_rb_SignatureStatus(NS_SHARED_PTR::shared_ptr<CPPCadesSignatureStatusObject> other):
    m_pCppCadesImpl(other) { }

bool pre_rb_SignatureStatus::is_valid(void)
{
    bool valid;
    hr_method_check(m_pCppCadesImpl->IsValid(valid));
    return valid;
}

void pre_rb_SignatureStatus::define_ruby_class(VALUE module)
{
    Data_Type<pre_rb_SignatureStatus> rb_cSignatureStatus =
        define_class_under<pre_rb_SignatureStatus>(module, "SignatureStatus")
        .define_constructor(Constructor<pre_rb_SignatureStatus>())
        .define_method("valid?", &pre_rb_SignatureStatus::is_valid);
}
}
