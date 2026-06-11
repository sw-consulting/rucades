// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "rucades_oid.h"
#include "CPPCadesCPAttribute.h"

namespace rucades {
class pre_rb_Attribute {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPAttributeObject> m_pCppCadesImpl;
  public:
    pre_rb_Attribute(void);
    pre_rb_Attribute(NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPAttributeObject> other);
    pre_rb_OID get_OID(void);
    std::string get_value(void);
    void set_value(std::string val);
    long get_name(void);
    void set_name(long name);
    long get_value_encoding(void);
    void set_value_encoding(long enc);

    static void define_ruby_class(VALUE module);

    friend class pre_rb_Attributes;
};
}
