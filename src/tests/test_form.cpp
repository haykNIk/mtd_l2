/*
 * @Author: hayknik
 *
 * Unit-тесты для ЛР2 (задание 4, штрафное): фреймворк doctest.
 * Заголовок doctest.h не хранится в репозитории — он скачивается в CI
 * (см. .github/workflows/ci.yml) и добавлен в .gitignore.
 * Локальный запуск:
 *   wget https://raw.githubusercontent.com/doctest/doctest/refs/heads/master/doctest/doctest.h
 *   cmake -S src -B build && cmake --build build && ctest --test-dir build --output-on-failure
 */
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

// По требованию ЛР2 функция fill должна оставаться ВНУТРЕННЕЙ для Form.cpp
// (она лежит в анонимном namespace), поэтому объявить её в Form.h нельзя.
// Чтобы всё-таки покрыть её тестами, подключаем сам файл реализации: тест и
// тестируемый код попадают в одну единицу трансляции, и fill становится
// доступна по имени. Именно поэтому в src/CMakeLists.txt Form.cpp НЕ указан
// в списке исходников цели tests — иначе символы продублировались бы.
#include "Form.cpp"

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace
{
    // Перехватывает всё, что функция печатает в std::cout, пока объект жив.
    // RAII: поток восстанавливается даже если draw() бросит исключение.
    class StreamCapture
    {
    public:
        explicit StreamCapture(std::ostringstream& sink)
            : m_old(std::cout.rdbuf(sink.rdbuf()))
        {
        }

        ~StreamCapture()
        {
            std::cout.rdbuf(m_old);
        }

    private:
        StreamCapture(const StreamCapture&);
        StreamCapture& operator=(const StreamCapture&);

        std::streambuf* m_old;
    };

    std::string captureDraw(const Form& form)
    {
        std::ostringstream sink;
        {
            StreamCapture capture(sink);
            form.draw();
        }
        return sink.str();
    }

    std::vector<std::string> splitLines(const std::string& text)
    {
        std::vector<std::string> lines;
        std::istringstream stream(text);
        std::string line;
        while (std::getline(stream, line))
            lines.push_back(line);
        return lines;
    }
}

// ---------------------------------------------------------------------------
// Функция fill
// ---------------------------------------------------------------------------

TEST_CASE("fill: заполняет len символов и дописывает терминальный ноль")
{
    char buffer[6];
    std::memset(buffer, '?', sizeof(buffer));

    fill(buffer, 5, 'x');

    CHECK(std::string(buffer) == "xxxxx");
    CHECK(buffer[5] == '\0');
    CHECK(std::strlen(buffer) == 5u);
}

TEST_CASE("fill: при len == 0 пишет только терминальный ноль")
{
    char buffer[4] = { 'a', 'b', 'c', '\0' };

    fill(buffer, 0, 'z');

    CHECK(buffer[0] == '\0');
    CHECK(std::strlen(buffer) == 0u);
}

TEST_CASE("fill: перезаписывает ранее записанное содержимое")
{
    char buffer[8];

    fill(buffer, 7, 'a');
    CHECK(std::string(buffer) == "aaaaaaa");

    fill(buffer, 7, 'b');
    CHECK(std::string(buffer) == "bbbbbbb");
}

TEST_CASE("fill: не трогает байты за пределами len + 1")
{
    char buffer[8];
    std::memset(buffer, '#', sizeof(buffer));

    fill(buffer, 4, 'x');

    CHECK(buffer[4] == '\0');
    // канарейки: байты после терминального нуля должны остаться нетронутыми
    CHECK(buffer[5] == '#');
    CHECK(buffer[6] == '#');
    CHECK(buffer[7] == '#');
}

TEST_CASE("fill: корректно работает с пробелом и дефисом")
{
    char spaces[4];
    char top[4];

    fill(spaces, 3, ' ');
    fill(top, 3, '-');

    CHECK(std::string(spaces) == "   ");
    CHECK(std::string(top) == "---");
}

// ---------------------------------------------------------------------------
// Иерархия класса Form
// ---------------------------------------------------------------------------

TEST_CASE("Form: наследников можно приводить к типу базового класса")
{
    Triangle triangle(0, 3);
    Circle circle(0, 3);

    // Неявное приведение наследника к указателю базового типа
    Form* forms[2];
    forms[0] = &triangle;
    forms[1] = &circle;

    CHECK(forms[0] != nullptr);
    CHECK(forms[1] != nullptr);

    // Обратное приведение корректно указывает на исходный объект
    CHECK(dynamic_cast<Triangle*>(forms[0]) == &triangle);
    CHECK(dynamic_cast<Circle*>(forms[1]) == &circle);

    // Приведение к «не своему» типу даёт nullptr
    CHECK(dynamic_cast<Triangle*>(forms[1]) == nullptr);
    CHECK(dynamic_cast<Circle*>(forms[0]) == nullptr);
}

TEST_CASE("Form: наследника можно привязать к ссылке базового типа")
{
    Triangle triangle(0, 2);
    Circle circle(0, 2);

    const Form& asTriangle = triangle;
    const Form& asCircle = circle;

    CHECK(dynamic_cast<const Triangle*>(&asTriangle) == &triangle);
    CHECK(dynamic_cast<const Circle*>(&asCircle) == &circle);
}

TEST_CASE("Form: вызов draw через базовый указатель полиморфен")
{
    Triangle triangle(1, 3);
    Circle circle(1, 3);

    Form* forms[2] = { &triangle, &circle };

    // Через указатель базового типа вызывается реализация наследника
    const std::string viaBaseTriangle = captureDraw(*forms[0]);
    const std::string viaBaseCircle = captureDraw(*forms[1]);

    CHECK(viaBaseTriangle == captureDraw(triangle));
    CHECK(viaBaseCircle == captureDraw(circle));
    CHECK(viaBaseTriangle != viaBaseCircle);
}

TEST_CASE("Form: удаление наследника через указатель базового типа безопасно")
{
    Form* triangle = new Triangle(0, 2);
    Form* circle = new Circle(0, 2);

    // Работает только благодаря виртуальному деструктору в Form
    CHECK_NOTHROW(delete triangle);
    CHECK_NOTHROW(delete circle);
}

// ---------------------------------------------------------------------------
// Поведение наследников
// ---------------------------------------------------------------------------

TEST_CASE("Triangle::draw: первая строка содержит отступ и линию из дефисов")
{
    const unsigned int offset = 3;
    const unsigned int legLength = 4;
    Triangle triangle(offset, legLength);

    const std::vector<std::string> lines = splitLines(captureDraw(triangle));

    REQUIRE(lines.size() == legLength + 1u);
    CHECK(lines[0] == "   |----");
    CHECK(lines[1] == "   |   /");
    CHECK(lines[legLength] == "   |/");
}

TEST_CASE("Triangle::setOffset: меняет отступ во всех строках")
{
    Triangle triangle(0, 2);

    const std::vector<std::string> before = splitLines(captureDraw(triangle));
    REQUIRE(before.size() == 3u);
    CHECK(before[0] == "|--");

    triangle.setOffset(2);

    const std::vector<std::string> after = splitLines(captureDraw(triangle));
    REQUIRE(after.size() == 3u);
    CHECK(after[0] == "  |--");
    CHECK(after[1] == "  | /");
    CHECK(after[2] == "  |/");
}

TEST_CASE("Circle::draw: число строк равно диаметру, отступ соблюдён")
{
    const unsigned int offset = 2;
    const unsigned int radius = 3;
    const unsigned int diameter = 2 * radius;
    Circle circle(offset, radius);

    const std::vector<std::string> lines = splitLines(captureDraw(circle));

    REQUIRE(lines.size() == diameter);

    const std::string indent(offset, ' ');
    bool hasFilledRow = false;
    for (std::size_t i = 0; i < lines.size(); ++i)
    {
        // каждая строка начинается с отступа
        CHECK(lines[i].compare(0, offset, indent) == 0);
        // после отступа ширина равна диаметру
        CHECK(lines[i].size() == offset + diameter);

        const std::string body = lines[i].substr(offset);
        if (body.find(' ') == std::string::npos)
            hasFilledRow = true;
    }

    // средняя строка должна быть заполнена целиком
    CHECK(hasFilledRow);
}

TEST_CASE("Circle::setOffset: добавляет ровно столько пробелов, сколько задан отступ")
{
    Circle circle(0, 2);

    const std::vector<std::string> before = splitLines(captureDraw(circle));

    circle.setOffset(3);

    const std::vector<std::string> after = splitLines(captureDraw(circle));

    REQUIRE(after.size() == before.size());
    for (std::size_t i = 0; i < after.size(); ++i)
    {
        CHECK(after[i].size() == before[i].size() + 3u);
        CHECK(after[i].compare(0, 3, "   ") == 0);
        // сам рисунок не изменился — сдвинулся только отступ
        CHECK(after[i].substr(3) == before[i]);
    }
}
