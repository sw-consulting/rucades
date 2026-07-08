# frozen_string_literal: true

# Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
# All rights reserved.
# This file is a part of rucades

require_relative "rucades/version"
require_relative "rucades/rucades"

# Rucades module
# Some staff on top of C++ bindings
module Rucades
  # Polyfill for Certificates.find
  class Certificates
    def find(type, *args)
      return find_no_query(type) if args.empty?

      criteria = args[0]
      # CAPICOM's bFindValidOnly is a boolean (default false). Coerce to a real boolean so
      # nil/0/false all mean "false" — Rice maps any other Ruby value (incl. Integer 0) to true.
      valid_only = ![ nil, false, 0 ].include?(args[1])
      return internal_find_query_string(type, criteria, valid_only) if criteria.is_a?(String)

      internal_find_query_long(type, criteria, valid_only)
    end

    private

    def find_no_query(type)
      if type != Rucades::CAPICOM_CERTIFICATE_FIND_TIME_VALID &&
         type != Rucades::CAPICOM_CERTIFICATE_FIND_TIME_NOT_YET_VALID &&
         type != Rucades::CAPICOM_CERTIFICATE_FIND_TIME_EXPIRED
        raise ArgumentError, "Missing query"
      end

      internal_find_query_string(type, "", false)
    end
  end
end
