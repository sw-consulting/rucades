// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "rucades_attribute.h"
#include "CPPCadesCPAttributes.h"

namespace rucades {
class pre_rb_Attributes {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPAttributesObject> m_pCppCadesImpl;
  public:
    pre_rb_Attributes(void);
    pre_rb_Attributes(NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPAttributesObject> other);
    void add(pre_rb_Attribute& attrb);
    void clear(void);
    long get_count(void);
    pre_rb_Attribute get_item(long index);
    void remove(long index);

    static void define_ruby_class(VALUE module);

    friend class pre_rb_Signer;
};
}
