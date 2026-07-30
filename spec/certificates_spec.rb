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

    describe "#find" do
      let(:certificates) { Rucades::Certificates.new }

      context "without a query" do
        it "raises for a type that requires a query when the query is omitted or nil" do
          [[], [nil]].each do |query|
            expect { certificates.find(Rucades::CAPICOM_CERTIFICATE_FIND_SUBJECT_NAME, *query) }
              .to raise_error(ArgumentError, "Missing query")
          end
        end

        it "returns a collection for the time-based find types when the query is omitted or nil" do
          [
            Rucades::CAPICOM_CERTIFICATE_FIND_TIME_VALID,
            Rucades::CAPICOM_CERTIFICATE_FIND_TIME_NOT_YET_VALID,
            Rucades::CAPICOM_CERTIFICATE_FIND_TIME_EXPIRED
          ].each do |type|
            [[], [nil]].each do |query|
              result = certificates.find(type, *query)
              expect(result).to be_a(Rucades::Certificates)
              expect(result.count).to eq(0)
            end
          end
        end
      end

      context "with a string criteria" do
        it "dispatches to the string query with the criteria itself" do
          expect(certificates).to receive(:internal_find_query_string)
            .with(Rucades::CAPICOM_CERTIFICATE_FIND_SUBJECT_NAME, "Ivanov", false)
          certificates.find(Rucades::CAPICOM_CERTIFICATE_FIND_SUBJECT_NAME, "Ivanov")
        end

        it "returns a collection end-to-end" do
          result = certificates.find(Rucades::CAPICOM_CERTIFICATE_FIND_SUBJECT_NAME, "Ivanov")
          expect(result).to be_a(Rucades::Certificates)
          expect(result.count).to eq(0)
        end
      end

      context "with a long criteria" do
        it "dispatches to the long query with the criteria itself" do
          expect(certificates).to receive(:internal_find_query_long)
            .with(Rucades::CAPICOM_CERTIFICATE_FIND_KEY_USAGE, 128, false)
          certificates.find(Rucades::CAPICOM_CERTIFICATE_FIND_KEY_USAGE, 128)
        end

        it "returns a collection end-to-end" do
          result = certificates.find(Rucades::CAPICOM_CERTIFICATE_FIND_KEY_USAGE, 128)
          expect(result).to be_a(Rucades::Certificates)
          expect(result.count).to eq(0)
        end
      end

      context "valid_only coercion" do
        # CAPICOM's bFindValidOnly is a boolean; nil/false/0 must all mean false,
        # any other value must mean true (Rice maps even Integer 0 to true otherwise).
        {
          nil => false,
          false => false,
          0 => false,
          true => true,
          1 => true,
          -1 => true,
          "yes" => true
        }.each do |given, expected|
          it "maps #{given.inspect} to #{expected}" do
            expect(certificates).to receive(:internal_find_query_string)
              .with(Rucades::CAPICOM_CERTIFICATE_FIND_SUBJECT_NAME, "Ivanov", expected)
            certificates.find(Rucades::CAPICOM_CERTIFICATE_FIND_SUBJECT_NAME, "Ivanov", given)
          end
        end
      end
    end
  end
end
