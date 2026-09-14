#pragma once

class Triangle
{
    const unsigned int m_offset;
    const unsigned int m_leg_length;

public:
    Triangle(unsigned int offset, unsigned int leg_length) : m_offset(offset), m_leg_length(leg_length) {}
    void draw() const;
};

class Circle
{
    const unsigned int m_offset;
    const unsigned int m_radius;

public:
    Circle(unsigned int offset, unsigned int radius) : m_offset(offset), m_radius(radius) {}
    void draw() const;
};