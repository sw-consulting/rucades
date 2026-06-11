# frozen_string_literal: true

# Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
# All rights reserved.
# This file is a part of rucades

RSpec.describe Rucades do
  describe "OID" do
    it "maintains consistent name, value and friendly name" do
      # Можно задать любой из аттрибутов (name, friendly_name, value)
      # Два другие будут синхронизированы
      oid = Rucades::OID.new
      oid.name = Rucades::CAPICOM_OID_BASIC_CONSTRAINTS_EXTENSION
      expect(oid.value).to eq("2.5.29.10")
      expect(["Основные ограничения", "Basic Constraints"]).to include(oid.friendly_name)

      oid.friendly_name = "Проверка подлинности сервера"
      expect(oid.name).to eq(Rucades::CAPICOM_OID_SERVER_AUTH_EKU)
      expect(oid.value).to eq("1.3.6.1.5.5.7.3.1")

      oid.value = "2.5.29.10"
      expect(oid.name).to eq(Rucades::CAPICOM_OID_BASIC_CONSTRAINTS_EXTENSION)
      expect(["Основные ограничения", "Basic Constraints"]).to include(oid.friendly_name)
    end
    it "throws an exception on invalid attribute value" do
      oid = Rucades::OID.new
      expect { oid.name = 1234 }.to raise_error(RuntimeError)
      expect { oid.friendly_name = "Туфта какая-то" }.to raise_error(RuntimeError)

      oid.value = "Тоже туфта, но не ошибка"
      expect(oid.name).to eq(Rucades::CAPICOM_OID_OTHER)
      expect(oid.friendly_name).to eq(oid.value)
    end
  end
end
