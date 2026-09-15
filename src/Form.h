#pragma once

class Form
{
protected:
    unsigned int m_offset;

public:
    Form(unsigned int offset) : m_offset(offset) {}
    virtual ~Form() {}

    virtual void draw() const = 0;
};

class Triangle : public Form
{
    const unsigned int m_leg_length;

public:
    Triangle(unsigned int offset, unsigned int leg_length)
        : Form(offset), m_leg_length(leg_length) {}
    void draw() const override;
    void setOffset(unsigned int offset);
};

class Circle : public Form
{
    const unsigned int m_radius;

public:
    Circle(unsigned int offset, unsigned int radius)
        : Form(offset), m_radius(radius) {}
    void draw() const override;
    void setOffset(unsigned int offset);
};
