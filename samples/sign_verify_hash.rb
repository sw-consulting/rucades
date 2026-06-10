# frozen_string_literal: true

require "rucades"

store = Rucades::Store.new
store.open(Rucades::CADESCOM_CONTAINER_STORE, Rucades::CAPICOM_MY_STORE,
           Rucades::CAPICOM_STORE_OPEN_MAXIMUM_ALLOWED)
certs = store.certificates

raise "Certificates with private key not found" unless certs.any?

signer = Rucades::Signer.new
signer.certificate = certs[1]
signer.check_certificate = true

hashed_data = Rucades::HashedData.new
hashed_data.algorithm = Rucades::CADESCOM_HASH_ALGORITHM_CP_GOST_3411_2012_256
hashed_data.hash("test data")

signed_data = Rucades::SignedData.new
signature = signed_data.sign_hash(hashed_data, signer, Rucades::CADESCOM_CADES_BES)

puts "============= Encrypted Message ============="
puts signature
puts "============================================="

signed_data_dec = Rucades::SignedData.new
signed_data_dec.verify_hash(hashed_data, signature, Rucades::CADESCOM_CADES_BES)

puts "=========== Verified successfully ==========="
