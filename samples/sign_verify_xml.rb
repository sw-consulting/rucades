# frozen_string_literal: true

require "rucades"

store = Rucades::Store.new
store.open(Rucades::CADESCOM_CONTAINER_STORE, Rucades::CAPICOM_MY_STORE,
           Rucades::CAPICOM_STORE_OPEN_MAXIMUM_ALLOWED)
certs = store.certificates

raise "Certificates with private key not found" unless certs.any?

signer = Rucades::Signer.new
signer.certificate = certs[1]

content_to_sign = <<~XML
  <?xml version="1.0" encoding="UTF-8"?>
      <!--
          "XML Security Library example: Original XML doc file for sign2 example. "
      -->
          <Envelope xmlns="urn:envelope">
              <Data>
                  Hello, World!
              </Data>
              <Node xml:id="nodeID">
              	Hello, Node!
              </Node>
          </Envelope>
XML

signed_xml = Rucades::SignedXML.new
signed_xml.content = content_to_sign
signed_xml.signature_type = Rucades::CADESCOM_XML_SIGNATURE_TYPE_ENVELOPED | Rucades::CADESCOM_XADES_BES
signature = signed_xml.sign(signer)

puts "============= Encrypted Message ============="
puts signature
puts "============================================="

signed_xml_dec = Rucades::SignedXML.new
signed_xml_dec.verify(signature)

raise "Incorrect value of SignedXML.verify result" unless signed_xml.content == content_to_sign

puts "=========== Verified successfully ==========="
