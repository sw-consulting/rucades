# Rucades

Вас приветсвует Rucades - CAdESCOM Ruby binding!

Gem реализует интерфейс, аналогичный [CAdESCOM](https://docs.cryptopro.ru/cades/reference/cadescom)
и разработан путём повторения функциональности [pycades](https://docs.cryptopro.ru/cades/pycades)

[![Build-and-test](https://github.com/maxirmx/rucades/actions/workflows/main.yml/badge.svg)](https://github.com/maxirmx/rucades/actions/workflows/main.yml)

## Совместимость

Gem тестировался в следующем окружении:
* Ububtu 20, 22
* Ruby 2.7.8, 3.1.7, 3.2.11, 3.3.11, 3.4.9, 4.0.5

Вероятно, Gem совместим с другими вариантами Linux, однако КриптоПро ЭЦП SDK доступно только для Ubuntu.

## Установка

* Установите пакеты  для сборки
```
    sudo apt update
    sudo apt install cmake build-essential libboost-all-dev ruby-dev tar git wget libffi-dev
    sudo gem install bundler
```
* Скачайте архив с [КриптоПро CSP](https://cryptopro.ru/products/csp/downloads) для Вашей архитектуры, распакуйте его и установите КриптоПро CSP
  Например,

_для amd64_
```
    wget -O  linux-arm64_deb.tgz https://cryptopro.ru/sites/default/files/private/csp/50/11455/linux-arm64_deb.tgz
    tar xvf linux-arm64_deb.tgz
    cd linux-arm64_deb
    sudo ./install.sh
```

_для arm64_
```
    wget -O  linux-arm64_deb.tgz https://cryptopro.ru/sites/default/files/private/csp/50/11455/linux-arm64_deb.tgz
    tar xvf linux-arm64_deb.tgz
    cd linux-arm64_deb
    sudo ./install.sh
```
* Установите пакет cprocsp-devel
```
sudo apt install ./lsb-cprocsp-devel_5.0*.deb
```
* Скачайте архив с [КриптоПро ЭЦП SDK](https://cryptopro.ru/products/cades/downloads), распакуйте его и установите пакет cprocsp-pki-cades (версия не ниже 2.0.14071)

_для amd64_
```
   tar xvf cades-linux-amd64.tar.gz
   cd cades-linux-amd64
   sudo apt install ./cprocsp-pki-cades*.deb
```

_для arm64_
```
   tar xvf cades-linux-arm64.tar.gz
   cd cades-linux-arm64
   sudo apt install ./cprocsp-pki-cades*.deb
```
* Добавьте в Gemfile Вашего проекта следующую строку:
```
gem 'rucades', git: 'https://github.com/maxirmx/rucades'
```

* Выполните
```
bundle install
```
!!! Компиляция расширения может занять 10-15 минут. Во время компиляции Ruby не выводит никаких сообщений. !!!

* Проверка установки

Скрипт _test.rb_
```
require 'rucades'
puts "CADES SDK version: #{Rucades::About.new.version.to_s}"
```
Запуск
```
bundle exec ruby test.rb
```

Ожидаемый результат (или что-то похожее)
```
CADES SDK version: 2.0.14892
```

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
То есть RSpec проверяет, что функция создалась с нужным имененм и параметрами, но не правильность её работы.

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
