# frozen_string_literal: true

# Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
# All rights reserved.
# This file is a part of rucades

# rubocop:disable Metrics/BlockLength
RSpec.describe Rucades do
  describe "Attribute" do
    it "has name and value properties" do
      attrb = Rucades::Attribute.new

      attrb.value_type = Rucades::CAPICOM_ENCODE_BINARY
      expect(attrb.value_type).to eq(Rucades::CAPICOM_ENCODE_BINARY)

      attrb.name = Rucades::CADESCOM_AUTHENTICATED_ATTRIBUTE_DOCUMENT_DESCRIPTION
      expect(attrb.name).to eq(Rucades::CADESCOM_AUTHENTICATED_ATTRIBUTE_DOCUMENT_DESCRIPTION)

      attrb.value = "Test description"
      expect(attrb.value).to eq("Test description")

      attrb.value_type = Rucades::CAPICOM_ENCODE_BASE64
      expect(attrb.value_type).to eq(Rucades::CAPICOM_ENCODE_BASE64)

      expect(attrb.value).to eq("VGVzdCBkZXNjcmlwdGlvbg==")
    end

    it "maintains encoding" do
      attrb = Rucades::Attribute.new

      attrb.name = Rucades::CADESCOM_AUTHENTICATED_ATTRIBUTE_DOCUMENT_DESCRIPTION
      attrb.value_type = Rucades::CAPICOM_ENCODE_BINARY
      attrb.value = "Test description"

      attrb.value_type = Rucades::CAPICOM_ENCODE_BASE64
      expect(attrb.value_type).to eq(Rucades::CAPICOM_ENCODE_BASE64)
      expect(attrb.value).to eq("VGVzdCBkZXNjcmlwdGlvbg==")
    end

    it "has OID property" do
      attrb = Rucades::Attribute.new
      attrb.oid.name = Rucades::CAPICOM_OID_BASIC_CONSTRAINTS2_EXTENSION

      expect(attrb.oid.value).to eq("2.5.29.19")
      expect(["Основные ограничения", "Basic Constraints"]).to include(attrb.oid.friendly_name)
    end

    it "throws an error if used in incorrevt state" do
      attrb = Rucades::Attribute.new
      expect { attrb.value = "Test description" }.to raise_error(RuntimeError)
    end
  end
end
# rubocop:enable Metrics/BlockLength
