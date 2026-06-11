// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_version.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_Version::pre_rb_Version(void):
      m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPVersionObject>(new CPPVersionObject())) { }

pre_rb_Version::pre_rb_Version(NS_SHARED_PTR::shared_ptr<CPPVersionObject> other):
      m_pCppCadesImpl(other) { }

unsigned int pre_rb_Version::major_version(void)
{
  unsigned int version = 0;
  hr_method_check(m_pCppCadesImpl->get_MajorVersion(&version));
  return version;
}

unsigned int pre_rb_Version::minor_version(void)
{
  unsigned int version = 0;
  hr_method_check(m_pCppCadesImpl->get_MinorVersion(&version));
  return version;
}

unsigned int pre_rb_Version::build_version(void)
{
  unsigned int version = 0;
  hr_method_check(m_pCppCadesImpl->get_BuildVersion(&version));
  return version;
}

std::string pre_rb_Version::to_s(void)
{
  CAtlString AtlVersion;
  hr_method_check(m_pCppCadesImpl->toString(AtlVersion));
  return AtlVersion.GetString();
}

void pre_rb_Version::define_ruby_class(VALUE module)
{
  Data_Type<pre_rb_Version> rb_cVersion =
    define_class_under<pre_rb_Version>(module, "Version")
    .define_constructor(Constructor<pre_rb_Version>())
    .define_method("major_version", &pre_rb_Version::major_version)
    .define_method("minor_version", &pre_rb_Version::minor_version)
    .define_method("build_version", &pre_rb_Version::build_version)
    .define_method("to_s", &pre_rb_Version::to_s);

}
}