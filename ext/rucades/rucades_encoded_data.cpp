// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_encoded_data.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_EncodedData::pre_rb_EncodedData(void):
      m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesCPEncodedDataObject>(new CPPCadesCPEncodedDataObject())) { }

std::string pre_rb_EncodedData::value(long type)
{
    CAPICOM_ENCODING_TYPE Type = static_cast<CAPICOM_ENCODING_TYPE>(type);
    CryptoPro::CBlob data;
    hr_method_check(m_pCppCadesImpl->get_Value(Type, data));
    return std::string((const char *)data.pbData(), data.cbData());
}

std::string pre_rb_EncodedData::format(bool multiline)
{
    CAtlStringW sValue;
    hr_method_check(m_pCppCadesImpl->Format(multiline ? TRUE : FALSE, sValue));
    return std::string(CW2A(sValue.GetString(), CP_UTF8));
}

void pre_rb_EncodedData::define_ruby_class(VALUE module)
{
  Data_Type<pre_rb_EncodedData> rb_cEncodedData =
    define_class_under<pre_rb_EncodedData>(module, "EncodedData")
    .define_constructor(Constructor<pre_rb_EncodedData>())
    .define_method("format", &pre_rb_EncodedData::format, Arg("multiline") = false)
    .define_method("value", &pre_rb_EncodedData::value, Arg("type") = static_cast<long>(CAPICOM_ENCODE_BASE64));
}
}
