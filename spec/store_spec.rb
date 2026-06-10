# frozen_string_literal: true

# Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
# All rights reserved.
# This file is a part of rucades

RSpec.describe Rucades do
  describe "Store" do
    it "has constructor" do
      store = Rucades::Store.new
      expect { store.add("") }.to raise_error(satisfy { |error| [RuntimeError, TypeError].any? { |klass| error.is_a?(klass) } })
    end

    it "can be opened" do
      store = Rucades::Store.new
      store.open(Rucades::CADESCOM_CONTAINER_STORE, Rucades::CAPICOM_MY_STORE, Rucades::CAPICOM_STORE_OPEN_MAXIMUM_ALLOWED)
      store.certificates
    end
  end
end
