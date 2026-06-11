// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_symmetric_algorithm.h"

using namespace Rice;
using namespace CryptoPro;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_SymmetricAlgorithm::pre_rb_SymmetricAlgorithm(void):
      m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesSymmetricAlgorithmObject>(new CPPCadesSymmetricAlgorithmObject())) { }

pre_rb_SymmetricAlgorithm::pre_rb_SymmetricAlgorithm(NS_SHARED_PTR::shared_ptr<CPPCadesSymmetricAlgorithmObject> other):
      m_pCppCadesImpl(other) { }

std::string pre_rb_SymmetricAlgorithm::get_divers_data(void)
{
    CBlob blobValue;
    hr_method_check(m_pCppCadesImpl->get_DiversData(blobValue));
    return std::string(reinterpret_cast<const char *>(blobValue.pbData()), blobValue.cbData());
}

void pre_rb_SymmetricAlgorithm::set_divers_data(std::string data)
{
    hr_method_check(m_pCppCadesImpl->put_DiversData(data.c_str(), data.length()));
}
std::string pre_rb_SymmetricAlgorithm::get_iv(void)
{
    CBlob blobValue;
    hr_method_check(m_pCppCadesImpl->get_IV(blobValue));
    return std::string(reinterpret_cast<const char *>(blobValue.pbData()), blobValue.cbData());
}
void pre_rb_SymmetricAlgorithm::set_iv(std::string iv)
{
    hr_method_check(m_pCppCadesImpl->put_IV(iv.c_str(), iv.length()));
}

std::string pre_rb_SymmetricAlgorithm::encrypt(std::string data, bool final)
{
    CAtlString sData = CAtlString(data.c_str());
    CStringProxy retval;
    hr_method_check(m_pCppCadesImpl->Encrypt(sData, sData.GetLength(), final ? TRUE : FALSE, retval));
    return std::string(retval.c_str());
}

std::string pre_rb_SymmetricAlgorithm::decrypt(std::string data, bool final)
{
    CAtlString sData = CAtlString(data.c_str());
    CBlob blobValue;
    hr_method_check(m_pCppCadesImpl->Decrypt(sData, sData.GetLength(), final ? TRUE : FALSE, blobValue));
    return std::string(reinterpret_cast<const char *>(blobValue.pbData()), blobValue.cbData());
}

pre_rb_SymmetricAlgorithm pre_rb_SymmetricAlgorithm::diversify_key(void)
{
    NS_SHARED_PTR::shared_ptr<CPPCadesSymmetricAlgorithmObject> pCPPCadesSymAlg;
    hr_method_check(m_pCppCadesImpl->DiversifyKey(pCPPCadesSymAlg));
    return pre_rb_SymmetricAlgorithm(pCPPCadesSymAlg);
}

void pre_rb_SymmetricAlgorithm::generate_key(long alg)
{
    CADESCOM_ENCRYPTION_ALGORITHM Algorithm = static_cast<CADESCOM_ENCRYPTION_ALGORITHM>(alg);
    hr_method_check(m_pCppCadesImpl->GenerateKey(Algorithm));
}

std::string pre_rb_SymmetricAlgorithm::export_key(pre_rb_Certificate& cert)
{
    CBlob blobValue;
    hr_method_check(m_pCppCadesImpl->ExportKey(cert.m_pCppCadesImpl, blobValue));
    return std::string(reinterpret_cast<const char *>(blobValue.pbData()), blobValue.cbData());
}

void pre_rb_SymmetricAlgorithm::import_key(std::string key, pre_rb_Certificate& cert, std::string password)
{
    CAtlString sData = CAtlString(key.c_str());
    CAtlString sPassword = CAtlString(password.c_str());
    hr_method_check(m_pCppCadesImpl->ImportKey(key.c_str(),key.length(), cert.m_pCppCadesImpl, password.c_str(), password.length()));
}

void pre_rb_SymmetricAlgorithm::define_ruby_class(VALUE module)
{
    Data_Type<pre_rb_SymmetricAlgorithm> rb_cSymmetricAlgorithm =
        define_class_under<pre_rb_SymmetricAlgorithm>(module, "SymmetricAlgorithm")
        .define_constructor(Constructor<pre_rb_SymmetricAlgorithm>())
        .define_method("divers_data", &pre_rb_SymmetricAlgorithm::get_divers_data)
        .define_method("divers_data=", &pre_rb_SymmetricAlgorithm::set_divers_data)
        .define_method("iv", &pre_rb_SymmetricAlgorithm::get_iv)
        .define_method("iv=", &pre_rb_SymmetricAlgorithm::set_iv)
        .define_method("encrypt", &pre_rb_SymmetricAlgorithm::encrypt,
                Arg("data"), Arg("final") = true)
        .define_method("decrypt", &pre_rb_SymmetricAlgorithm::decrypt,
                Arg("data"), Arg("final") = true)
        .define_method("diversify_key", &pre_rb_SymmetricAlgorithm::diversify_key)
        .define_method("generate_key", &pre_rb_SymmetricAlgorithm::generate_key,
                Arg("alg") = static_cast<long>(CADESCOM_ENCRYPTION_ALGORITHM_GOST_28147_89))
        .define_method("export_key", &pre_rb_SymmetricAlgorithm::export_key)
        .define_method("import_key", &pre_rb_SymmetricAlgorithm::import_key,
                Arg("key"), Arg("cert"), Arg("password") = std::string(""));
}
}
