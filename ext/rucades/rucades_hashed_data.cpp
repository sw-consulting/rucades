// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_hashed_data.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_HashedData::pre_rb_HashedData(void)
      : m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesCPHashedDataObject>(new CPPCadesCPHashedDataObject())) { }

std::string pre_rb_HashedData::get_key(void)
{
    CAtlString sKey;
    hr_method_check(m_pCppCadesImpl->get_Key(sKey));
    return std::string(sKey.GetString());
}

void pre_rb_HashedData::set_key(std::string key)
{
    CAtlString sKey = CAtlString(key.c_str());
    hr_method_check(m_pCppCadesImpl->put_Key(sKey));
}

long pre_rb_HashedData::get_algorithm(void)
{
    CAPICOM_HASH_ALGORITHM Algorithm;
    hr_method_check(m_pCppCadesImpl->get_Algorithm(&Algorithm));
    return static_cast<long>(Algorithm);
}

void pre_rb_HashedData::set_algorithm(long alg)
{
    CAPICOM_HASH_ALGORITHM Algorithm = static_cast<CAPICOM_HASH_ALGORITHM>(alg);
    hr_method_check(m_pCppCadesImpl->put_Algorithm(Algorithm));
}

long pre_rb_HashedData::get_data_encoding(void)
{
    CADESCOM_CONTENT_ENCODING_TYPE Encoding;
    hr_method_check(m_pCppCadesImpl->get_DataEncoding(&Encoding));
    return static_cast<long>(Encoding);
}

void pre_rb_HashedData::set_data_encoding(long enc)
{
    CADESCOM_CONTENT_ENCODING_TYPE Encoding = static_cast<CADESCOM_CONTENT_ENCODING_TYPE>(enc);
    hr_method_check(m_pCppCadesImpl->put_DataEncoding(Encoding));
}

std::string pre_rb_HashedData::get_value(void)
{
    CAtlString sValue;
    hr_method_check(m_pCppCadesImpl->get_Value(sValue));
    return std::string(sValue.GetString());
}

void pre_rb_HashedData::hash(std::string data)
{
    CAtlString sValue = CAtlString(data.c_str());
    hr_method_check(m_pCppCadesImpl->put_Hash(sValue.GetString(), sValue.GetLength()));
}

void pre_rb_HashedData::set_hash_value(std::string data)
{
    CAtlString sValue = CAtlString(data.c_str());
    hr_method_check(m_pCppCadesImpl->put_HashValue(sValue));
}

void pre_rb_HashedData::define_ruby_class(VALUE module)
{
    define_class_under<pre_rb_HashedData>(module, "HashedData")
        .define_constructor(Constructor<pre_rb_HashedData>())
        .define_method("key", &pre_rb_HashedData::get_key)
        .define_method("key=", &pre_rb_HashedData::set_key)
        .define_method("algorithm", &pre_rb_HashedData::get_algorithm)
        .define_method("algorithm=", &pre_rb_HashedData::set_algorithm)
        .define_method("data_encoding", &pre_rb_HashedData::get_data_encoding)
        .define_method("data_encoding=", &pre_rb_HashedData::set_data_encoding)
        .define_method("value", &pre_rb_HashedData::get_value)
        .define_method("hash", &pre_rb_HashedData::hash)
        .define_method("hash_value=", &pre_rb_HashedData::set_hash_value);
}
}
