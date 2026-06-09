# frozen_string_literal: true

# Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
# All rights reserved.
# This file is a part of rucades

require "mkmf-rice"
require "fiddle"

# rubocop:disable Style/GlobalVars

INCDIRS = [
  "/opt/cprocsp/include",
  "/opt/cprocsp/include/cpcsp",
  "/opt/cprocsp/include/pki/atl",
  "/opt/cprocsp/include/pki"
]
if RUBY_PLATFORM =~ /darwin/
  INCDIRS.push("/Applications/CryptoPro_ECP.app/Contents/Resources/include/pki")
  INCDIRS.push("/Applications/CryptoPro_ECP.app/Contents/Resources/include/pki/cplib")
  INCDIRS.push("/Applications/CryptoPro_ECP.app/Contents/Resources/include/pki/cppcades")
else
  INCDIRS.push("/usr/include/boost")
  INCDIRS.push("/opt/cprocsp/include/pki/cplib")
  INCDIRS.push("/opt/cprocsp/include/pki/cppcades")
end

CXXDEFS = [
  " -DUNIX",
  " -fpermissive",
  " -Wno-narrowing",
  " -Wno-deprecated-declarations",
  " -Wno-write-strings",
  " -DLEGACY_FORMAT_MESSAGE_IMPL",
  " -D_LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR"
].freeze

ARM64_CXXDEFS = [
  "-DLINUX",
  "-DPROC_TYPE_ARM64=7",
  "-DPROCESSOR_TYPE=PROC_TYPE_ARM64",
  "-Wno-write-strings"
].freeze

INCDIRS.each { |dir| $INCFLAGS << " -I#{dir}" }

$defs << " -DSIZEOF_VOID_P=#{Fiddle::SIZEOF_VOIDP}"

CXXDEFS.each { |df| $defs << df }
ARM64_CXXDEFS.each { |df| $defs << df } if RUBY_PLATFORM =~ /aarch64-linux/
$defs << " -DDARWIN" if RUBY_PLATFORM =~ /darwin/

if RUBY_PLATFORM =~ /darwin/
  $DLDFLAGS << " -L/Applications/CryptoPro_ECP.app/Contents/MacOS/lib"
  $DLDFLAGS << " -Wl,-rpath,/Applications/CryptoPro_ECP.app/Contents/MacOS/lib"
  $DLDFLAGS << " -L/opt/cprocsp/lib/amd64"
  $DLDFLAGS << " -Wl,-rpath,/opt/cprocsp/lib/amd64"
elsif RUBY_PLATFORM =~ /aarch64-linux/
  $DLDFLAGS << " -L/opt/cprocsp/lib/aarch64"
else
  $DLDFLAGS << " -L/opt/cprocsp/lib/amd64"
end

$LOCAL_LIBS << " -lcppcades"

$srcs = [
  "rucades.cpp",
  "rucades_const.cpp",
  "rucades_tools.cpp",
  "rucades_about.cpp",
  "rucades_algorithm.cpp",
  "rucades_attribute.cpp",
  "rucades_attributes.cpp",
  "rucades_basic_constraints.cpp",
  "rucades_blobs.cpp",
  "rucades_certificate.cpp",
  "rucades_certificates.cpp",
  "rucades_certificate_status.cpp",
  "rucades_crl.cpp",
  "rucades_eku.cpp",
  "rucades_ekus.cpp",
  "rucades_encoded_data.cpp",
  "rucades_enveloped_data.cpp",
  "rucades_extended_key_usage.cpp",
  "rucades_hashed_data.cpp",
  "rucades_key_usage.cpp",
  "rucades_oid.cpp",
  "rucades_private_key.cpp",
  "rucades_public_key.cpp",
  "rucades_raw_signature.cpp",
  "rucades_recipients.cpp",
  "rucades_signature_status.cpp",
  "rucades_signed_data.cpp",
  "rucades_signed_xml.cpp",
  "rucades_signer.cpp",
  "rucades_signers.cpp",
  "rucades_store.cpp",
  "rucades_symmetric_algorithm.cpp",
  "rucades_version.cpp"
]

# rubocop:enable Style/GlobalVars
create_makefile("rucades/rucades")
