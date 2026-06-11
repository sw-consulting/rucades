// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "rucades_certificate.h"
#include "CPPCadesCollections.h"

namespace rucades {
class pre_rb_Recipients {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPRecipientsObject> m_pCppCadesImpl;
  public:
    pre_rb_Recipients(void);
    pre_rb_Recipients(NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPRecipientsObject> other);
    void add(pre_rb_Certificate& attrb);
    void clear(void);
    long get_count(void);
    pre_rb_Certificate get_item(long index);
    void remove(long index);

    static void define_ruby_class(VALUE module);

    friend class pre_rb_EnvelopedData;
};
}
