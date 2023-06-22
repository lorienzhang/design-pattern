class Shape 
{
public:
    virtual ~Shape() {}
    Shape(const std::string& color) : color_(color) {}
    const std::string& color() const { return color_; }

private:
    std::string color_:
};

class Circle : public Shape
{
public:
    Circle(const std::string &color) : Shape(color) {}
};

class Triangle : public Shape
{
public:
    Triangle(const std::string &color) : Shape(color) {}
};