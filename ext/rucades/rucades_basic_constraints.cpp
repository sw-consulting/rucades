// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_basic_constraints.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_BasicConstraints::pre_rb_BasicConstraints(void):
      m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesCPBasicConstraintsObject>(new CPPCadesCPBasicConstraintsObject())) { }

pre_rb_BasicConstraints::pre_rb_BasicConstraints(NS_SHARED_PTR::shared_ptr<CPPCadesCPBasicConstraintsObject> other):
      m_pCppCadesImpl(other) { }

bool pre_rb_BasicConstraints::is_ceritficate_authority(void)
{
    BOOL bIsCA = 0;
    hr_method_check(m_pCppCadesImpl->get_IsCertificateAuthority(&bIsCA));
    return (bIsCA != 0);
}

bool pre_rb_BasicConstraints::is_critical(void)
{
    BOOL bIsCritical = 0;
    hr_method_check(m_pCppCadesImpl->get_IsCritical(&bIsCritical));
    return (bIsCritical != 0);
}

bool pre_rb_BasicConstraints::is_path_len_constraint_present(void)
{
    BOOL bIsPathLenConstr = 0;
    hr_method_check(m_pCppCadesImpl->get_IsPathLenConstraintPresent(&bIsPathLenConstr));
    return (bIsPathLenConstr != 0);
}

bool pre_rb_BasicConstraints::is_present(void)
{
    BOOL bIsPresent = 0;
    hr_method_check(m_pCppCadesImpl->get_IsPresent(&bIsPresent));
    return (bIsPresent != 0);
}

long pre_rb_BasicConstraints::get_path_len_constraint(void)
{
    DWORD dwPathLenConst;
    hr_method_check(m_pCppCadesImpl->get_PathLenConstraint(&dwPathLenConst));
    return dwPathLenConst;
}

void pre_rb_BasicConstraints::define_ruby_class(VALUE module)
{
    Data_Type<pre_rb_BasicConstraints> rb_cBasicConstraints =
        define_class_under<pre_rb_BasicConstraints>(module, "BasicConstraints")
        .define_constructor(Constructor<pre_rb_BasicConstraints>())
        .define_method("certificate_authority?", &pre_rb_BasicConstraints::is_ceritficate_authority)
        .define_method("critical?", &pre_rb_BasicConstraints::is_critical)
        .define_method("pathlen_constraint_present?", &pre_rb_BasicConstraints::is_path_len_constraint_present)
        .define_method("present?", &pre_rb_BasicConstraints::is_present)
        .define_method("path_len_constraint", &pre_rb_BasicConstraints::get_path_len_constraint);
}
}