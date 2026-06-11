// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#pragma once

#include "rucades.h"
#include "rucades_basic_constraints.h"
#include "rucades_certificate_status.h"
#include "rucades_extended_key_usage.h"
#include "rucades_key_usage.h"
#include "rucades_private_key.h"
#include "rucades_public_key.h"
#include "CPPCadesCPCertificate.h"

namespace rucades {

class pre_rb_Store;

class pre_rb_Certificate {
  protected:
    NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPCertificateObject> m_pCppCadesImpl;
  public:
    pre_rb_Certificate(void);
    pre_rb_Certificate(NS_SHARED_PTR::shared_ptr<CryptoPro::PKI::CAdES::CPPCadesCPCertificateObject> other);

    std::string get_subject_name(void);
    std::string get_issuer_name(void);
    std::string get_serial_number(void);
    std::string get_thumbprint(void);
    long get_version(void);
    std::string get_valid_from_date(void);
    std::string get_valid_to_date(void);

    pre_rb_PrivateKey          get_private_key(void);
    pre_rb_PublicKey           get_public_key(void);
    pre_rb_KeyUsage            get_key_usage(void);
    pre_rb_ExtendedKeyUsage    get_extended_key_usage(void);
    pre_rb_BasicConstraints    get_basic_constraints(void);
    pre_rb_CertificateStatus   get_certificate_status(void);     //aka IsValid

    std::string get_info(long type);
    bool has_private_key(void);

    std::string crt_export(long type);
    void crt_import (std::string crt);
    void additional_store(pre_rb_Store& store);

    static void define_ruby_class(VALUE module);
    static void extend_ruby_class(void);

    friend class pre_rb_Certificates;
    friend class pre_rb_Recipients;
    friend class pre_rb_RawSignature;
    friend class pre_rb_Signer;
    friend class pre_rb_Store;
    friend class pre_rb_SymmetricAlgorithm;
};
}
