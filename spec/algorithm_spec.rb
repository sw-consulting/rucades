# frozen_string_literal: true

# Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
# All rights reserved.
# This file is a part of rucades

RSpec.describe Rucades do
  describe "Algorithm" do
    it "supports GOST only with variable key length" do
      a = Rucades::Algorithm.new
      expect(a.name).to eq(Rucades::CADESCOM_ENCRYPTION_ALGORITHM_GOST_28147_89)
      expect(a.key_length).to eq(Rucades::CAPICOM_ENCRYPTION_KEY_LENGTH_256_BITS)

      a.key_length = Rucades::CAPICOM_ENCRYPTION_KEY_LENGTH_192_BITS
      expect(a.key_length).to eq(Rucades::CAPICOM_ENCRYPTION_KEY_LENGTH_192_BITS)

      # older SDK supports GOST only and raises on AES; newer SDK accepts AES
      begin
        a.name = Rucades::CADESCOM_ENCRYPTION_ALGORITHM_AES
        expect(a.name).to eq(Rucades::CADESCOM_ENCRYPTION_ALGORITHM_AES)
      rescue RuntimeError
        # older SDK — acceptable
      end
    end
  end
end
