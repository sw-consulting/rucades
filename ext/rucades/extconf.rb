# frozen_string_literal: true

# Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
# All rights reserved.
# This file is a part of rucades

require "mkmf-rice"
require "fiddle"

# rubocop:disable Style/GlobalVars
PLATFROM_DARWIN = RUBY_PLATFORM =~ /darwin/
PLATFORM_DARWIN_ARM64 = RUBY_PLATFORM =~ /arm64-darwin/
PLATFORM_LINUX_ARM64 = RUBY_PLATFORM =~ /aarch64-linux/

LIBDIR = PLATFROM_DARWIN ? "/Applications/CryptoPro_ECP.app/Contents/Resources" : "/opt/cprocsp"
BOOSTDIR = if PLATFROM_DARWIN
             PLATFORM_DARWIN_ARM64 ? "/opt/homebrew/include" : "/usr/local/include"
           else
             "/usr/include"
           end

INCDIRS = [
  "#{BOOSTDIR}/boost",
  "/opt/cprocsp/include",
  "/opt/cprocsp/include/cpcsp",
  "/opt/cprocsp/include/pki/atl",
  "#{LIBDIR}/include/pki/cppcades",
  "#{LIBDIR}/include/pki/cplib",
  "/opt/cprocsp/include/pki",
  "#{LIBDIR}/include/pki",
  "#{__dir__}/cplib",
].freeze

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
ARM64_CXXDEFS.each { |df| $defs << df } if PLATFORM_LINUX_ARM64
$defs << " -DDARWIN" if PLATFROM_DARWIN

if PLATFROM_DARWIN
  $DLDFLAGS << " -L/Applications/CryptoPro_ECP.app/Contents/MacOS/lib"
  $DLDFLAGS << " -Wl,-rpath,/Applications/CryptoPro_ECP.app/Contents/MacOS/lib"
elsif PLATFORM_LINUX_ARM64
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
