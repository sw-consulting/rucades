# frozen_string_literal: true

# Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
# All rights reserved.
# This file is a part of rucades

RSpec.describe Rucades do
  describe "KeyUsage" do
    it "has constructor and getters" do
      kusage = Rucades::KeyUsage.new
      expect(kusage.present?).to be(false)
      expect(kusage.critical?).to be(false)
      expect(kusage.digital_signature_enabled?).to be(false)
      expect(kusage.non_repudiation_enabled?).to be(false)
      expect(kusage.key_encipherment_enabled?).to be(false)
      expect(kusage.key_agreement_enabled?).to be(false)
      expect(kusage.key_cert_sign_enabled?).to be(false)
      expect(kusage.data_encipherment_enabled?).to be(false)
      expect(kusage.crl_sign_enabled?).to be(false)
      expect(kusage.encipher_only_enabled?).to be(false)
      expect(kusage.decipher_only_enabled?).to be(false)
    end
  end
end
