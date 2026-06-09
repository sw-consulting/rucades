# frozen_string_literal: true

require "rucades"

store = Rucades::Store.new
store.open(Rucades::CADESCOM_CONTAINER_STORE, Rucades::CAPICOM_MY_STORE,
           Rucades::CAPICOM_STORE_OPEN_MAXIMUM_ALLOWED)
certs = store.certificates

raise "Certificates with private key not found" unless certs.count != 0

signer = Rucades::Signer.new
signer.certificate = certs[1]
signer.check_certificate = true

signed_data = Rucades::SignedData.new
signed_data.content = "Test content to be signed"
signature = signed_data.sign_cades(signer, Rucades::CADESCOM_CADES_BES)
puts "============= Signature ============="
puts signature
puts "====================================="

signed_data2 = Rucades::SignedData.new
signed_data2.verify_cades(signature, Rucades::CADESCOM_CADES_BES)
puts "******* Verified successfully ******"
