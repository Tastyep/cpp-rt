#ifndef RT_COLOR_HH
#define RT_COLOR_HH
        
class Color
{
public:
    Color(unsigned int color);
    Color(unsigned int r, unsigned int g, unsigned int b);

    ~Color() = default;
    Color(const Color& other) = default;
    Color(Color&& other) = default;
    Color& operator=(const Color& other) = default;
    Color& operator=(Color&& other) = default;

    Color operator/(unsigned int number) {
        return Color(this->r / number, this->g / number, this->b / number);
    }
    
    bool operator!() const {
        return r || g || b;
    }
    
    void operator+=(const Color& color) {
        this->r += color.r;
        this->g += color.g;
        this->b += color.b;
    }
    
    Color operator*(double value) {
        Color tmp(this->r, this->g, this->b);
        
        tmp.r = static_cast<double>(tmp.r) * value;
        tmp.g = static_cast<double>(tmp.g) * value;
        tmp.b = static_cast<double>(tmp.b) * value;
        if (tmp.r > 255)
            tmp.r = 255;
        if (tmp.g > 255)
            tmp.g = 255;
        if (tmp.b > 255)
            tmp.b = 255;
        return tmp;
    }
    
    void operator*=(double value) {
        *this = *this * value;
    }
    
    Color& operator=(unsigned int color) {
        this->r = (color >> 16) & 0xFF;
        this->g = (color >> 8) & 0xFF;
        this->b = color & 0xFF;
    }

    unsigned int toInteger() const;
    void mix(const Color &color, double amount);
    void limit(unsigned int r = 255, unsigned int g = 255, unsigned int b = 255);
    
public:
    unsigned int r;
    unsigned int g;
    unsigned int b;
};

inline std::ostream& operator<<(std::ostream& os, const Color& c) {
    os << "[" << c.r << "," << c.g << "," << c.b << "]";
    return os;
}

#endif /* end of include guard: RT_COLOR_HH */
        