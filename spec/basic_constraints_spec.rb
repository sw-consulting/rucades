# frozen_string_literal: true

# Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
# All rights reserved.
# This file is a part of rucades

RSpec.describe Rucades do
  describe "BasicConstraints" do
    it "has constructor and getters" do
      constr = Rucades::BasicConstraints.new
      expect(constr.certificate_authority?).to be(false)
      expect(constr.critical?).to be(false)
      expect(constr.pathlen_constraint_present?).to be(false)
      expect(constr.present?).to be(false)
      expect(constr.path_len_constraint).to be(0)
    end
  end
end
