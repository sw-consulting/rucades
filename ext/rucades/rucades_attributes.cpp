// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_attributes.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_Attributes::pre_rb_Attributes(void):
      m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesCPAttributesObject>(new CPPCadesCPAttributesObject())) { }

pre_rb_Attributes::pre_rb_Attributes(NS_SHARED_PTR::shared_ptr<CPPCadesCPAttributesObject> other):
      m_pCppCadesImpl(other) { }

void pre_rb_Attributes::add(pre_rb_Attribute& attrb)
{
    hr_method_check(m_pCppCadesImpl->Add(attrb.m_pCppCadesImpl));
}

void pre_rb_Attributes::clear(void){
    hr_method_check(m_pCppCadesImpl->Clear());
}

long pre_rb_Attributes::get_count(void){
    long count = 0;
    hr_method_check(m_pCppCadesImpl->get_Count(&count));
    return count;
}

pre_rb_Attribute pre_rb_Attributes::get_item(long index)
{
    pre_rb_Attribute attrb;
    hr_method_check(m_pCppCadesImpl->get_Item(index, attrb.m_pCppCadesImpl));
    return attrb;
}

void pre_rb_Attributes::remove(long index)
{
    hr_method_check(m_pCppCadesImpl->Remove(index));
}

void pre_rb_Attributes::define_ruby_class(VALUE module)
{
  Data_Type<pre_rb_Attributes> rb_cAttributes =
    define_class_under<pre_rb_Attributes>(module, "Attributes")
    .define_constructor(Constructor<pre_rb_Attributes>())
    .define_method("clear", &pre_rb_Attributes::clear)
    .define_method("count", &pre_rb_Attributes::get_count)
    .define_method("remove",&pre_rb_Attributes::remove)
    .define_method("add", &pre_rb_Attributes::add)
    .define_method("<<", [](pre_rb_Attributes& self, pre_rb_Attribute& item) -> pre_rb_Attributes&
                  /* Allow chaining */  { self.add(item);  return self;  })
    .define_method("[]", &pre_rb_Attributes::get_item);
}

}
