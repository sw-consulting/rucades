# frozen_string_literal: true

require "rucades"

store = Rucades::Store.new
store.open(Rucades::CADESCOM_CONTAINER_STORE, Rucades::CAPICOM_MY_STORE,
           Rucades::CAPICOM_STORE_OPEN_MAXIMUM_ALLOWED)
certs = store.certificates

raise "Certificates with private key not found" unless certs.count != 0

# hashed_data = Rucades::HashedData.new

enveloped_data = Rucades::EnvelopedData.new
enveloped_data.content = "Message to encrypt с русскими буквами"
enveloped_data.recipients.add(certs[1])
encrypted_message = enveloped_data.encrypt(Rucades::CADESCOM_ENCODE_BASE64)
puts "============= Encrypted Message ============="
puts encrypted_message
puts "============================================="

enveloped_data_dec = Rucades::EnvelopedData.new
enveloped_data_dec.decrypt(encrypted_message)
content = enveloped_data_dec.content

raise "Incorrect value of EnvelopedData.decrypt result" unless content == "Message to encrypt с русскими буквами"

puts "=========== Decrypted successfully =========="
