// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_recipients.h"

using namespace Rice;
using namespace CryptoPro;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_Recipients::pre_rb_Recipients(void):
      m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesCPRecipientsObject>(new CPPCadesCPRecipientsObject())) { }

pre_rb_Recipients::pre_rb_Recipients(NS_SHARED_PTR::shared_ptr<CPPCadesCPRecipientsObject> other):
      m_pCppCadesImpl(other) { }

void pre_rb_Recipients::add(pre_rb_Certificate& attrb)
{
    hr_method_check(m_pCppCadesImpl->Add(attrb.m_pCppCadesImpl));
}

void pre_rb_Recipients::clear(void){
    hr_method_check(m_pCppCadesImpl->Clear());
}

long pre_rb_Recipients::get_count(void){
    DWORD count = 0;
    hr_method_check(m_pCppCadesImpl->get_Count(&count));
    return count;
}

pre_rb_Certificate pre_rb_Recipients::get_item(long index)
{
    pre_rb_Certificate cert;
    hr_method_check(m_pCppCadesImpl->get_Item(index, cert.m_pCppCadesImpl));
    return cert;
}

void pre_rb_Recipients::remove(long index)
{
    hr_method_check(m_pCppCadesImpl->Remove(index));
}

void pre_rb_Recipients::define_ruby_class(VALUE module)
{
  Data_Type<pre_rb_Recipients> rb_cRecipients =
    define_class_under<pre_rb_Recipients>(module, "Recipients")
    .define_constructor(Constructor<pre_rb_Recipients>())
    .define_method("clear", &pre_rb_Recipients::clear)
    .define_method("count", &pre_rb_Recipients::get_count)
    .define_method("remove", &pre_rb_Recipients::remove)
    .define_method("add", &pre_rb_Recipients::add)
    .define_method("<<", [](pre_rb_Recipients& self, pre_rb_Certificate& item) -> pre_rb_Recipients&
                  /* Allow chaining */  { self.add(item);  return self;  })
    .define_method("[]", &pre_rb_Recipients::get_item);
}

}
