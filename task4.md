## 4 (штраф). Автотесты в CI

В каждом из заданий необходимо добавить в Ваш конвейер CI несколько unit-тестов, используя один из предложенных фреймворков для тестирования.
Убедитесь, что CI успешно проходит.

Тесты должны покрывать как минимум функцию `fill` и классовую иерархию класса `Form` (убедитесь, что наследники этого класса можно приводить к типу базового класса).

## 4.1. Google Test

См. раздел "Google Test" статьи [CMake / Testing / CI/CD](https://github.com/zuevval/cpp_project_example/wiki/cmake-testing-cicd#google-test)



## 4.2. MinUnit

В прошлом семестре мы говорили про фреймворк [minunit](https://github.com/siu/minunit).
Напишите тесты, используя этот фреймворк.
Сам файл **не храните в Git** (рекомендую добавить его в `.gitignore`), а вместо этого всякий раз при запуске CI скачивайте его.

Это можно делать с помощью утилит `curl` или `wget`, например,
```bash
wget https://raw.githubusercontent.com/siu/minunit/refs/heads/master/minunit.h
```
или склонировав весь репозиторий по HTTPS

## 4.3. MinUnit как подмодуль

Добавьте репозиторий [MinUnit](https://github.com/siu/minunit) в свой репозиторий, используя [git submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules).
Напишите тесты согласно общему заданию

## 4.4. Doctest

[Doctest](https://github.com/doctest/doctest) - ещё один single-header фреймворк для тестирования.
Обратите внимание, у них есть простая и понятная [вводная инструкция](https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md).

Выполните задание, аналогичное 4.2, используя репозиторий doctest или файл https://raw.githubusercontent.com/doctest/doctest/refs/heads/master/doctest/doctest.h

## 4.5. Doctest как подмодуль

Добавьте репозиторий [doctest](https://github.com/doctest/doctest) в свой репозиторий, используя [git submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules).
Напишите тесты согласно общему заданию
