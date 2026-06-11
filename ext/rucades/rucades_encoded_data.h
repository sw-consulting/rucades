// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "CPPCadesCPEncodedData.h"

namespace rucades {
class pre_rb_EncodedData {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPEncodedDataObject> m_pCppCadesImpl;
  public:
    pre_rb_EncodedData(void);
    std::string value(long format);
    std::string format(bool multiline);

    static void define_ruby_class(VALUE module);

    friend class pre_rb_PublicKey;
};
}
