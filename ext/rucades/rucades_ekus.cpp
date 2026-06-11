// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_ekus.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_EKUs::pre_rb_EKUs(void):
      m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesCPEKUsObject>(new CPPCadesCPEKUsObject())) { }

pre_rb_EKUs::pre_rb_EKUs(NS_SHARED_PTR::shared_ptr<CPPCadesCPEKUsObject> other):
      m_pCppCadesImpl(other) { }

long pre_rb_EKUs::get_count(void)
{
  unsigned int count = 0;
  hr_method_check(m_pCppCadesImpl->get_Count(&count));
  return count;
}

pre_rb_EKU pre_rb_EKUs::get_item(long index)
{
  NS_SHARED_PTR::shared_ptr<CPPCadesCPEKUObject> pCppCadesEKU = NS_SHARED_PTR::shared_ptr<CPPCadesCPEKUObject>(new CPPCadesCPEKUObject());
  hr_method_check(m_pCppCadesImpl->get_Item(index, pCppCadesEKU));
  return pre_rb_EKU(pCppCadesEKU);
}

void pre_rb_EKUs::define_ruby_class(VALUE module)
{
  Data_Type<pre_rb_EKUs> rb_cEKUs =
    define_class_under<pre_rb_EKUs>(module, "EKUs")
    .define_constructor(Constructor<pre_rb_EKUs>())
    .define_method("count", &pre_rb_EKUs::get_count)
    .define_method("[]", &pre_rb_EKUs::get_item);
}
}
