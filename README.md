# Rucades

Вас приветсвует Rucades - CAdESCOM Ruby binding!

Gem реализует интерфейс, аналогичный [CAdESCOM](https://docs.cryptopro.ru/cades/reference/cadescom)
и разработан путём повторения функциональности [pycades](https://docs.cryptopro.ru/cades/pycades)

[![Gem Version](https://badge.fury.io/rb/rucades.svg)](https://badge.fury.io/rb/rucades)
[![Build-and-test](https://github.com/maxirmx/rucades/actions/workflows/main.yml/badge.svg)](https://github.com/maxirmx/rucades/actions/workflows/main.yml)

## Совместимость

Gem тестировался в следующем окружении:
* Ubuntu 20, 22
* macOS: macos-latest (arm64), macos-15-intel (amd64)
* Ruby 2.7.8, 3.1.7, 3.2.11, 3.3.11, 3.4.9, 4.0.5

Вероятно, Gem совместим с другими вариантами Linux, однако КриптоПро ЭЦП SDK доступно только для Ubuntu.
После каждого релиза автоматически выполняется проверка работоспособности Gem на Ubuntu 22 и macOS-latest.

## Установка

### Зависимости

Перед установкой Gem подготовьте зависимости без привязки к конкретному дистрибутиву или пакетному менеджеру:

* Ruby и Bundler для Вашей платформы.
* Средства сборки C/C++ расширений Ruby для Вашей платформы.
* [CMake](https://cmake.org/) — необходим для сборки native extension.
* [Boost](https://www.boost.org/) — требуется при использовании КриптоПро ЭЦП SDK версии ниже 2.0.15700; начиная с версии 2.0.15700 Boost устанавливать отдельно не нужно.
* [КриптоПро CSP](https://cryptopro.ru/products/csp/downloads) и пакет разработки CSP (`cprocsp-devel` или аналогичный пакет для Вашей платформы).
* [КриптоПро ЭЦП SDK](https://cryptopro.ru/products/cades/downloads) с пакетом CAdES (`cprocsp-pki-cades` или аналогичный пакет для Вашей платформы), версия не ниже 2.0.14071.

Используйте официальные инструкции КриптоПро для выбранной операционной системы и архитектуры:

* [документация КриптоПро CSP](https://docs.cryptopro.ru/csp) описывает установку и особенности CSP на поддерживаемых платформах;
* [страница загрузки КриптоПро CSP](https://cryptopro.ru/products/csp/downloads) содержит дистрибутивы для разных платформ и архитектур;
* [документация КриптоПро ЭЦП SDK](https://docs.cryptopro.ru/cades/usage) описывает использование и требования SDK;
* [страница загрузки КриптоПро ЭЦП SDK](https://cryptopro.ru/products/cades/downloads) содержит актуальные пакеты SDK.

Начиная с КриптоПро CSP 5.0 R3, пакеты CAdES/SDK поставляются в составе основного дистрибутива CSP. Для более ранних версий CSP может потребоваться отдельная установка архива КриптоПро ЭЦП SDK.

### Установка опубликованного Gem из RubyGems.org

Добавьте Gem в Gemfile Вашего проекта:
```
gem 'rucades'
```

Затем выполните установку зависимостей проекта обычным для Bundler способом.

Для установки без Gemfile можно использовать опубликованный пакет RubyGems.org:
```
gem install rucades
```

Компиляция расширения может занять 10-15 минут. Во время компиляции Ruby может не выводить сообщений.

### Проверка установки

Скрипт _test.rb_
```
require 'rucades'
puts "CADES SDK version: #{Rucades::About.new.version.to_s}"
```
Запуск
```
ruby test.rb
```

Ожидаемый результат (или что-то похожее)
```
CADES SDK version: 2.0.14892
```

### Установка из исходного кода репозитория

Этот вариант нужен только для установки unreleased-версии из репозитория.

Добавьте в Gemfile Вашего проекта следующую строку:
```
gem 'rucades', git: 'https://github.com/maxirmx/rucades'
```

Затем выполните установку зависимостей проекта обычным для Bundler способом.

## Использование

В каталоге samples есть 4 примера, унаследованные от pycades:
* encrypt - decrypt
* sign - verify signature
* sign xml document - verify signature
* sign hash - verify signature

Для запуска примеров необходим сертификат с привязкой к закрытому ключу.
Тестовый сертификат можно установить с помощью команды:

_для amd64_
```
/opt/cprocsp/bin/amd64/cryptcp -createcert -dn "CN=test" -provtype 80 -cont '\\.\HDIMAGE\test' -ca https://cryptopro.ru/certsrv
```

_для arm64_
```
/opt/cprocsp/bin/aarch64/cryptcp -createcert -dn "CN=test" -provtype 80 -cont '\\.\HDIMAGE\test' -ca https://cryptopro.ru/certsrv
```

RSpec обеспечивает покрытие тестами всех классов и примерно 70% функций.
Однако, следует иметь в виду, что тестируются С++ --> Ruby bindings, а не функциональность.
То есть RSpec проверяет, что функция создалась с нужным именен и параметрами, но не правильность её работы.

## Разработка

Этот Gem использует
* [bundler](https://bundler.io/guides/getting_started.html) для управления зависимстями
* [rake](https://ruby.github.io/rake/) для управления сборкой
* [RSpec](https://rspec.info/) 'to make TDD productive and fun'
* [Rice](https://jasonroelofs.com/rice/4.x/introduction.html) для генерации Ruby bindings

Чтобы начать разработку нужно:
* прочитать документацию на Rice
* установить зависимости, как описано выше в разделе установка
* ```bundle install```
* ```rake --tasks```

## Лицензия

[MIT License](https://opensource.org/licenses/MIT).
