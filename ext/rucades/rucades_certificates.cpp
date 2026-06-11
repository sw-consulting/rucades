// Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
// All rights reserved.
// This file is a part of rucades

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "rucades.h"
#include "rucades_certificate.h"
#include "rucades_certificates.h"
#include "rucades_store.h"

using namespace Rice;
using namespace CryptoPro::PKI::CAdES;

namespace rucades {
pre_rb_Certificates::pre_rb_Certificates(void):
      m_pCppCadesImpl(NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificatesObject>(new CPPCadesCPCertificatesObject())) { }

pre_rb_Certificates::pre_rb_Certificates(NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificatesObject> other):
      m_pCppCadesImpl(other) { }

long pre_rb_Certificates::get_count(void)
{
  unsigned int count = 0;
  hr_method_check(m_pCppCadesImpl->Count(&count));
  return count;
}

bool pre_rb_Certificates::has_any(void)
{
  return get_count() > 0;
}

pre_rb_Certificate pre_rb_Certificates::get_item(long index)
{
  NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificateObject> pCppCadesCertificate =
                    NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificateObject>(new CPPCadesCPCertificateObject());
  hr_method_check(m_pCppCadesImpl->Item(index, pCppCadesCertificate));
  return pre_rb_Certificate(pCppCadesCertificate);
}

pre_rb_Certificates pre_rb_Certificates::internal_find_query_long(long type, long query, bool valid_only)
{
    CAPICOM_CERTIFICATE_FIND_TYPE Type = static_cast<CAPICOM_CERTIFICATE_FIND_TYPE>(type);
    pre_rb_Certificates res = pre_rb_Certificates();

    switch (Type) {
      case CAPICOM_CERTIFICATE_FIND_EXTENDED_PROPERTY:
      case CAPICOM_CERTIFICATE_FIND_KEY_USAGE:
      case CAPICOM_CERTIFICATE_FIND_EXTENSION:
      case CAPICOM_CERTIFICATE_FIND_APPLICATION_POLICY:
        {
          BOOL bValidOnly = valid_only ? TRUE:FALSE;
          FindCriteria findCriteria;
          findCriteria.dwCriteriaFlag = FIND_CRITERIA_DWORD;
          findCriteria.dword = query;
          NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificatesObject> pCppCadesCertificates =
                    NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificatesObject>(new CPPCadesCPCertificatesObject());
          hr_method_check(m_pCppCadesImpl->Find(Type, &findCriteria, bValidOnly, pCppCadesCertificates));
          res = pre_rb_Certificates(pCppCadesCertificates);
        }
        break;
      case CAPICOM_CERTIFICATE_FIND_SHA1_HASH:
      case CAPICOM_CERTIFICATE_FIND_SUBJECT_NAME:
      case CAPICOM_CERTIFICATE_FIND_ISSUER_NAME:
      case CAPICOM_CERTIFICATE_FIND_ROOT_NAME:
      case CAPICOM_CERTIFICATE_FIND_TEMPLATE_NAME:
      case CAPICOM_CERTIFICATE_FIND_CERTIFICATE_POLICY:
      case CAPICOM_CERTIFICATE_FIND_TIME_VALID:
      case CAPICOM_CERTIFICATE_FIND_TIME_NOT_YET_VALID:
      case CAPICOM_CERTIFICATE_FIND_TIME_EXPIRED:
          break;
      default:
        throw std::invalid_argument("Invalid CERTIFICATE_FIND_TYPE");
        break;
    }
    return res;
}

pre_rb_Certificates pre_rb_Certificates::internal_find_query_string(long type, std::string query, bool valid_only)
{
    CAPICOM_CERTIFICATE_FIND_TYPE Type = static_cast<CAPICOM_CERTIFICATE_FIND_TYPE>(type);
    BOOL bValidOnly = valid_only ? TRUE:FALSE;
    FindCriteria findCriteria;
    CryptoPro::CDateTime utcDate;

    switch (Type) {
      case CAPICOM_CERTIFICATE_FIND_SHA1_HASH:
      case CAPICOM_CERTIFICATE_FIND_SUBJECT_NAME:
      case CAPICOM_CERTIFICATE_FIND_ISSUER_NAME:
      case CAPICOM_CERTIFICATE_FIND_ROOT_NAME:
      case CAPICOM_CERTIFICATE_FIND_TEMPLATE_NAME:
      case CAPICOM_CERTIFICATE_FIND_CERTIFICATE_POLICY:
      case CAPICOM_CERTIFICATE_FIND_EXTENSION:
      case CAPICOM_CERTIFICATE_FIND_APPLICATION_POLICY:
        findCriteria.dwCriteriaFlag = FIND_CRITERIA_STRING;
        findCriteria.str = CAtlString(query.c_str());
        break;
      case CAPICOM_CERTIFICATE_FIND_TIME_VALID:
      case CAPICOM_CERTIFICATE_FIND_TIME_NOT_YET_VALID:
      case CAPICOM_CERTIFICATE_FIND_TIME_EXPIRED:
        if (query != "") {
          try {
            utcDate = CryptoPro::CDateTime(query.c_str());
          }
          catch (...) {
            throw std::invalid_argument("Invalid Date/Time");
          }
        }
        else {
          utcDate = CryptoPro::CDateTime::Now();
        }
        findCriteria.dwCriteriaFlag = FIND_CRITERIA_DATE;
        findCriteria.date = utcDate;
      case CAPICOM_CERTIFICATE_FIND_EXTENDED_PROPERTY:
      case CAPICOM_CERTIFICATE_FIND_KEY_USAGE:
        return pre_rb_Certificates();
      default:
        throw std::invalid_argument("Invalid CERTIFICATE_FIND_TYPE");
    }

    NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificatesObject> pCppCadesCertificates =
                    NS_SHARED_PTR::shared_ptr<CPPCadesCPCertificatesObject>(new CPPCadesCPCertificatesObject());
    hr_method_check(m_pCppCadesImpl->Find(Type, &findCriteria, bValidOnly, pCppCadesCertificates));
    return pre_rb_Certificates(pCppCadesCertificates);
}

void pre_rb_Certificates::define_ruby_class(VALUE module)
{
  Data_Type<pre_rb_Certificates> rb_cCertificates =
    define_class_under<pre_rb_Certificates>(module, "Certificates")
    .define_constructor(Constructor<pre_rb_Certificates>())
    .define_method("count", &pre_rb_Certificates::get_count)
    .define_method("any?", &pre_rb_Certificates::has_any)
    .define_method("[]", &pre_rb_Certificates::get_item)
    .define_method("internal_find_query_long", &pre_rb_Certificates::internal_find_query_long)
    .define_method("internal_find_query_string", &pre_rb_Certificates::internal_find_query_string);
}
}
