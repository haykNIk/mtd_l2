# mtd_l2

modern technologies in development, Lab2

---

Мёржим, пушим, билдим, фиксим,<br>
Если не упало, то и фиг с ним<br>
&nbsp;&nbsp;&nbsp;&nbsp;[Арчет](https://www.youtube.com/watch?v=iWg6viDkHvI)

## Перед началом работы

1. Создайде ветку `develop`
1. Все боковые ветки ответвляйте от неё

## 1. .gitignore

1. Посетите сайт [toptal.com/developers/gitignore](https://www.toptal.com/developers/gitignore).
Сгенерируйте gitignore для C++ + VisualStudioCode + CLion + Linux + macOS и скопируйте этот текст в файл `.gitignore` в корне репозитория 
1. Соберите CMake-проект. Если ещё какие-то файлы или папки с артефактами сборки не игнроируются, добавьте и их в самый верх файла `.gitignore` до строки `# Created by ...`
1. сделайте commit (можно в отдельной ветке и потом влить PR в `develop`, можно прямо в `develop`)

## 2. GitHub Actions

1. Посмотрите документ: [CMake - Testing - CI/CD](https://github.com/zuevval/cpp_project_example/wiki/cmake-testing-cicd#ci---continuous-integration), раздел CI
1. Настройте в репозитории CI с помощью GitHub Actions. Он должен собирать cmake-проект и полученный бинарный файл выгружать в артефакты. CI должен запускаться на push или Pull Request в `main` или `develop`.
Рекомендуемые модули:
   - [Setup CMake](https://github.com/marketplace/actions/actions-setup-cmake)
   - [Upload Artifact](https://github.com/marketplace/actions/upload-a-build-artifact)
1. Проверьте, что CI корректно работает и артефакт сохраняется (например, вот [здесь](https://github.com/zuevval/cpp_project_example/actions/runs/21669438900) сохранился файл артефакта `test-output`)

<img src=artifactsExample.png width=600>

## 3. Нетривиальный merge

1. Создайте из ветки `develop` ветку `refactor/base_figure`
1. В этой ветке создайте общий класс-предок `Form` для `Triangle` и `Circle` с полем `m_offset` и чисто виртуальной (pure virtual) функцией `draw`.
Сделайте коммит и откройте Pull Request в `develop`, но не вливайте
1. Вернитесь в ветку `develop`. Создайте из неё ветку `feature/move_figures`
1. В новой ветке сделайте так, чтобы поле `m_offset` было не константным в обеих фигурах.
Сделайте метод `void setOffset(unsigned int)` в каждом классе и вызовите этот метод для треугольника `tr` в `main.cpp`. Откройте Pull Request в `develop`, но не вливайте
1. Вернитесь в `develop`. Сделайте ещё одну ветку `refactor/reduce_code_dup`
1. В этой ветке сделайте функцию `fill(char * str, unsigned int len, char c)` (внутреннюю для `Form.cpp`), которая заполняет `str` значением `c` (плюс терминальный ноль). Используйте её для заполнения переменных `spaces` и `top` в методе `Triangle::draw` и `spaces` в методе `Circle::draw`. Откройте Pull Request в `develop` и влейте его.
1. Влейте обновлённый `develop` (не забудьте сделать `git pull`) в ветку `refactor/base_figure` и затем влейте Pull Request из этой ветки
1. Влейте ещё более обновлённый `develop` в ветку `feature/move_figures` и влейте оставшийся Pull Request в `develop`

## По окончании работы

1. Сделайте Pull Request в `main`
1. Влейте его, но не удаляйте ветку `develop`


