// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_private_key.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_PrivateKey::pre_rb_PrivateKey(void):
          m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesCPPrivateKeyObject>(new CPPCadesCPPrivateKeyObject())) { }

pre_rb_PrivateKey::pre_rb_PrivateKey(NS_SHARED_PTR::shared_ptr<CPPCadesCPPrivateKeyObject> other):
      m_pCppCadesImpl(other) { }

std::string pre_rb_PrivateKey::get_container_name(void)
{
    CAtlString sContName;
    hr_method_check(m_pCppCadesImpl->get_ContainerName(sContName));
    return std::string(sContName.GetString());
}

std::string pre_rb_PrivateKey::get_unique_container_name(void)
{
    CAtlString sUniqueContName;
    hr_method_check(m_pCppCadesImpl->get_UniqueContainerName(sUniqueContName));
    return std::string(sUniqueContName.GetString());
}

std::string pre_rb_PrivateKey::get_provider_name(void)
{
    CAtlString sProvName;
    hr_method_check(m_pCppCadesImpl->get_ProviderName(sProvName));
    return std::string(sProvName.GetString());
}

long pre_rb_PrivateKey::get_provider_type(void)
{
    CAPICOM_PROV_TYPE Type;
    hr_method_check(m_pCppCadesImpl->get_ProviderType(&Type));
    return static_cast<long>(Type);
}

long pre_rb_PrivateKey::get_key_spec(void)
{
    CAPICOM_KEY_SPEC spec;
    hr_method_check(m_pCppCadesImpl->get_KeySpec(&spec));
    return static_cast<long>(spec);
}

void pre_rb_PrivateKey::set_cache_pin(int pin)
{
    hr_method_check(m_pCppCadesImpl->set_CachePin(pin));
}

void pre_rb_PrivateKey::set_key_pin(std::string pin)
{
    CAtlString sKeyPin = CAtlString(pin.c_str());
    hr_method_check(m_pCppCadesImpl->set_KeyPin(sKeyPin));
}

void pre_rb_PrivateKey::change_pin(void)
{
    hr_method_check(m_pCppCadesImpl->ChangePin());
}

void pre_rb_PrivateKey::define_ruby_class(VALUE module)
{
  Data_Type<pre_rb_PrivateKey> rb_cPrivateKey =
    define_class_under<pre_rb_PrivateKey>(module, "PrivateKey")
    .define_constructor(Constructor<pre_rb_PrivateKey>())
    .define_method("container_name", &pre_rb_PrivateKey::get_container_name)
    .define_method("unique_container_name", &pre_rb_PrivateKey::get_unique_container_name)
    .define_method("provider_name", &pre_rb_PrivateKey::get_provider_name)
    .define_method("provider_type", &pre_rb_PrivateKey::get_provider_type)
    .define_method("key_spec", &pre_rb_PrivateKey::get_key_spec)
    .define_method("cache_pin=", &pre_rb_PrivateKey::set_cache_pin)
    .define_method("key_pin=", &pre_rb_PrivateKey::set_key_pin)
    .define_method("change_pin", &pre_rb_PrivateKey::change_pin);
}
}
