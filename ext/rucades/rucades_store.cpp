// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_store.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_Store::pre_rb_Store(void):
      m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesCPStoreObject>(new CPPCadesCPStoreObject())) { }

std::string pre_rb_Store::get_name(void)
{
    CAtlString sName;
    hr_method_check(m_pCppCadesImpl->get_Name(sName));
    return std::string(sName.GetString());
}

pre_rb_Certificates pre_rb_Store::get_certificates(void)
{
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPCertificatesObject> pCertificates;
    hr_method_check(m_pCppCadesImpl->get_Certificates(pCertificates));
    return pre_rb_Certificates(pCertificates);
}

long pre_rb_Store::get_location(void)
{
    CADESCOM_STORE_LOCATION Location;
    hr_method_check(m_pCppCadesImpl->get_Location(&Location));
    return static_cast<long>(Location);
}

void pre_rb_Store::open(long location, std::string& name, long mode)
{
    CADESCOM_STORE_LOCATION Location = static_cast<CADESCOM_STORE_LOCATION>(location);
    CAPICOM_STORE_OPEN_MODE Mode = static_cast<CAPICOM_STORE_OPEN_MODE>(mode);
    CAtlStringW sName = CAtlStringW(name.c_str());
    hr_method_check(m_pCppCadesImpl->Open(Location, sName, Mode));
}

void pre_rb_Store::close(void)
{
    hr_method_check(m_pCppCadesImpl->Close());
}

void pre_rb_Store::add(pre_rb_Certificate& cert)
{
    hr_method_check(m_pCppCadesImpl->Add(cert.m_pCppCadesImpl));
}

void pre_rb_Store::add_crl(pre_rb_CRL& crl)
{
    hr_method_check(m_pCppCadesImpl->AddCRL(crl.m_pCppCadesImpl));
}

void pre_rb_Store::define_ruby_class(VALUE module)
{
    Data_Type<pre_rb_Store> rb_cStore =
        define_class_under<pre_rb_Store>(module, "Store")
        .define_constructor(Constructor<pre_rb_Store>())
        .define_method("name", &pre_rb_Store::get_name)
        .define_method("certificates", &pre_rb_Store::get_certificates)
        .define_method("location", &pre_rb_Store::get_location)
        .define_method("open", &pre_rb_Store::open,
                        Arg("location") = static_cast<long>(CADESCOM_CURRENT_USER_STORE),
                        Arg("name") = std::string("My"),
                        Arg("mode") = static_cast<long>(CAPICOM_STORE_OPEN_READ_ONLY))
        .define_method("close", &pre_rb_Store::close)
        .define_method("add", &pre_rb_Store::add)
        .define_method("add_crl", &pre_rb_Store::add_crl);
}
}
