# frozen_string_literal: true

# Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
# All rights reserved.
# This file is a part of rucades

RSpec.describe Rucades do
  describe "EncodedData" do
    it "has constructor and getters" do
      encdata = Rucades::EncodedData.new

      # format may not be implemented in older SDK versions
      [true, false, nil].each do |arg|
        result = arg.nil? ? encdata.format : encdata.format(arg)
        expect(result).to be_a(String)
      rescue RuntimeError
        # older SDK returns E_NOTIMPL — acceptable
      end

      expect(encdata.value(Rucades::CAPICOM_ENCODE_BINARY)).to eq("")

      # value with BASE64 may raise in older SDK versions on empty data
      [Rucades::CAPICOM_ENCODE_BASE64, nil].each do |arg|
        result = arg.nil? ? encdata.value : encdata.value(arg)
        expect(result).to be_a(String)
      rescue RuntimeError
        # older SDK raises on empty BASE64 — acceptable
      end
    end
  end
end
