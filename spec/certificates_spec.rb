# frozen_string_literal: true

# Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
# All rights reserved.
# This file is a part of rucades

RSpec.describe Rucades do
  describe "Certificates" do
    it "has constructor and getters" do
      certificates = Rucades::Certificates.new
      expect(certificates.count).to eq(0)
      expect(certificates.any?).to be(false)
      expect { certificates[0] }.to raise_error(RuntimeError)
    end
  end
end
