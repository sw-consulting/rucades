// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_signers.h"

using namespace Rice;
using namespace CryptoPro;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_Signers::pre_rb_Signers(void):
      m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesCPSignersObject>(new CPPCadesCPSignersObject())) { }

pre_rb_Signers::pre_rb_Signers(NS_SHARED_PTR::shared_ptr<CPPCadesCPSignersObject> other):
      m_pCppCadesImpl(other) { }

long pre_rb_Signers::get_count(void){
    unsigned int count = 0;
    hr_method_check(m_pCppCadesImpl->get_Count(&count));
    return count;
}

pre_rb_Signer pre_rb_Signers::get_item(long index)
{
    pre_rb_Signer attrb;
    hr_method_check(m_pCppCadesImpl->get_Item(index, attrb.m_pCppCadesImpl));
    return attrb;
}

void pre_rb_Signers::define_ruby_class(VALUE module)
{
  Data_Type<pre_rb_Signers> rb_cSigners =
    define_class_under<pre_rb_Signers>(module, "Signers")
    .define_constructor(Constructor<pre_rb_Signers>())
    .define_method("count", &pre_rb_Signers::get_count)
    .define_method("[]", &pre_rb_Signers::get_item);
}
}
