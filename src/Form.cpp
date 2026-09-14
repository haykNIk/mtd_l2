#include "Form.h"

#include <cmath>
#include <iostream>

void Triangle::draw() const
{
    char* spaces = new char[m_offset + 1];
    for (int i = 0; i < m_offset; ++i)
        spaces[i] = ' ';
    spaces[m_offset] = '\0';
    
    char* top = new char[m_leg_length + 1];
    for(int i=0; i < m_leg_length; ++i)
        top[i] = '-';
    top[m_leg_length] = '\0';
        
    
    std::cout << spaces << '|' << top << std::endl;
    
    for(int i=0; i < m_leg_length; i++)
    {
        std::cout << spaces;
        std::cout << '|';
        for (int j=0; j < m_leg_length - i - 1; ++j)
            std::cout << ' ';
        std::cout << '/' << std::endl;
    }
    delete[] spaces;
    delete[] top;
}

void Circle::draw() const
{
    char* spaces = new char[m_offset + 1];
    for (int i = 0; i < m_offset; ++i)
        spaces[i] = ' ';
    spaces[m_offset] = '\0';
    
    const unsigned int diameter = 2 * m_radius;
    const unsigned int radiusSquared = m_radius * m_radius;
    
    for(int iRow = 0; iRow < diameter; ++iRow)
    {
        std::cout << spaces;
        for(int iCol = 0; iCol < diameter; ++iCol)
        {
            int x = iCol - m_radius;
            int y = iRow - m_radius;
            bool isInside = (x*x + y*y) <= radiusSquared;
            std::cout << (isInside ? '*' : ' ');
        }
        std::cout << std::endl;
    }
    delete[] spaces;
}