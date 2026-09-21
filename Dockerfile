# ---------------------------------------------------------------------------
# ЛР4, п. 4.2: Dockerfile для кода второй лабораторной по СТРПО (mtd_l2).
#
# Требование задания: компиляция должна происходить НА ЭТАПЕ СБОРКИ образа,
# а запуск программы — ПРИ СОЗДАНИИ КОНТЕЙНЕРА.
#
# Сборка:  docker build -t figures .
# Запуск:  docker run --rm figures
#
# @Author: hayknik
# ---------------------------------------------------------------------------

FROM debian:bookworm-slim

# Инструменты сборки ставим на этапе build образа.
# Один RUN: меньше слоёв. Чистим список пакетов apt — уменьшает размер образа.
RUN apt-get update \
 && apt-get install -y --no-install-recommends g++ cmake make \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Копируем только исходники и сборочный скрипт: каталог src/tests
# (unit-тесты и скачанный doctest.h) в образе не нужен, см. .dockerignore
COPY src/CMakeLists.txt ./src/CMakeLists.txt
COPY src/Form.h src/Form.cpp src/main.cpp ./src/

# Компиляция на этапе СБОРКИ образа: на выходе получаем /app/build/main
RUN cmake -S src -B build && cmake --build build

# Запуск программы при СОЗДАНИИ КОНТЕЙНЕРА
CMD ["./build/main"]
