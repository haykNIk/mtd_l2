/*
 * @Author: hayknik
 */
#include "Form.h"

int main()
{
    Triangle tr(5, 10);
    tr.draw();

    Circle c(3, 7);
    c.draw();

    Triangle smallTr(7, 4);
    smallTr.draw();

    tr.setOffset(2);
    tr.draw();

    // Демонстрация изменения радиуса окружности
    c.setRadius(9);
    c.draw();
    return 0;
}
