# frozen_string_literal: true

# Copyright (c) 2023 Maxim [maxirmx] Samsonov (https://sw.consulting)
# All rights reserved.
# This file is a part of rucades

require_relative "lib/rucades/version"

Gem::Specification.new do |spec|
  spec.name = "rucades"
  spec.version = Rucades::VERSION
  spec.authors = ["Maxim [maxirmx] Samsonov"]
  spec.email = ["maxirmx@sw.consulting"]

  spec.summary = "https://github.com/maxirmx/rucades"
  spec.description = "Ruby CaDes bindings"
  spec.homepage = "https://github.com/maxirmx/rucades"
  spec.license = "MIT"
  spec.required_ruby_version = ">= 2.7.8"

  spec.metadata["homepage_uri"] = spec.homepage
  spec.metadata["source_code_uri"] = "https://github.com/maxirmx/rucades"

  # Specify which files should be added to the gem when it is released.
  # The `git ls-files -z` loads the files in the RubyGem that have been added into git.
  spec.files = Dir.chdir(__dir__) do
    `git ls-files -z`.split("\x0").reject do |f|
      (f == __FILE__) || f.match(%r{\A(?:(?:bin|test|spec|features|sdk)/|\.(?:git|travis|circleci)|appveyor)})
    end
  end
  spec.bindir = "exe"
  spec.executables = spec.files.grep(%r{\Aexe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]
  spec.extensions = ["ext/rucades/extconf.rb"]

  spec.add_dependency "fiddle", "~> 1"
  spec.add_dependency "rice", "~> 4.1"
end
