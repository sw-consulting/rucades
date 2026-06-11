// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "rucades_algorithm.h"
#include "rucades_recipients.h"
#include "CPPCadesCPEnvelopedData.h"

namespace rucades {
class pre_rb_EnvelopedData {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPEnvelopedDataObject> m_pCppCadesImpl;
  public:
    pre_rb_EnvelopedData(void);

    std::string get_content(void);
    void set_content(std::string content);
    long get_content_encoding(void);
    void set_content_encoding(long enc);
    pre_rb_Recipients get_recipients(void);
    pre_rb_Algorithm get_algorithm(void);

    std::string encrypt(long enc);
    void decrypt(std::string);
    std::string stream_encrypt(std::string content, int final);
    std::string stream_decrypt(std::string content, int final);

    static void define_ruby_class(VALUE module);
};
}
