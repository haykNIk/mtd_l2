cmake_minimum_required(VERSION 3.10)

project(figures)

set(CMAKE_CXX_STANDARD 11)

add_executable(main
    Form.cpp main.cpp
)

# ---------------------------------------------------------------------------
# Unit-тесты (задание 4, штрафное). Фреймворк — doctest (single header).
# Сам заголовок в репозитории не хранится: он скачивается при каждом запуске
# CI (см. .github/workflows/ci.yml) и добавлен в .gitignore.
# Локальный запуск:
#   wget https://raw.githubusercontent.com/doctest/doctest/refs/heads/master/doctest/doctest.h \
#        -O src/tests/doctest.h
#   cmake -S src -B build && cmake --build build
#   ctest --test-dir build --output-on-failure
# ---------------------------------------------------------------------------
enable_testing()

set(DOCTEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

if(EXISTS ${DOCTEST_DIR}/doctest.h)
    # Form.cpp НЕ добавляем в список исходников: по требованию ЛР2 функция fill
    # должна оставаться внутренней для Form.cpp, поэтому тест подключает этот
    # файл напрямую (#include "Form.cpp") и работает с ним в одной единице
    # трансляции. Если указать Form.cpp ещё и здесь, символы продублируются.
    add_executable(tests
        tests/test_form.cpp
    )

    target_include_directories(tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${DOCTEST_DIR}
    )

    add_test(NAME unit_tests COMMAND tests)

    message(STATUS "doctest.h найден — цель tests добавлена")
else()
    message(WARNING "doctest.h не найден в ${DOCTEST_DIR} — цель tests пропущена "
                    "(скачайте заголовок, см. комментарий выше)")
endif()
