#include "Colour.hpp"

#include <algorithm>
#include <cmath>

namespace Palette {
    Colour::Colour() {
        this->value = 0;
    }

    Colour::Colour(int a, int r, int g, int b) {
        // Ensure values are within range
        a = (a < 0 ? 0 : a);
        a = (a > 255 ? 255 : a);
        r = (r < 0 ? 0 : r);
        r = (r > 255 ? 255 : r);
        g = (g < 0 ? 0 : g);
        g = (g > 255 ? 255 : g);
        b = (b < 0 ? 0 : b);
        b = (b > 255 ? 255 : b);

        // Encode value
        this->value = 0;
        this->setA(a);
        this->setR(r);
        this->setG(g);
        this->setB(b);
    }

    int Colour::a() const {
        return (this->value & 0xff000000) >> 24;
    }

    int Colour::r() const {
        return (this->value & 0x00ff0000) >> 16;
    }

    int Colour::g() const {
        return (this->value & 0x0000ff00) >> 8;
    }

    int Colour::b() const {
        return (this->value & 0x000000ff);
    }

    int Colour::raw() const {
        return this->value;
    }

    HSL Colour::hsl() const {
        // Struct to return
        HSL hsl;

        // Convert from [0, 255] to [0, 1]
        float fr = this->r()/255.0;
        float fg = this->g()/255.0;
        float fb = this->b()/255.0;

        // Calculate values used to computation
        float max = std::max(std::max(fr, fg), fb);
        float min = std::min(std::min(fr, fg), fb);
        float delta = max - min;

        // Determine HSL values
        if (delta > 0) {
            // Hue
            if (max == fr) {
                hsl.h = 60 * std::fmod(((fg - fb) / delta), 6);
            } else if (max == fg) {
                hsl.h = 60 * (((fb - fr)/delta) + 2);
            } else if (max == fb) {
                hsl.h = 60 * (((fr - fg)/delta) + 4);
            }

            // Saturation
            if (max > 0) {
                hsl.s = delta/max;
            } else {
                hsl.s = 0;
            }

            // Lightness
            hsl.l = max;

        } else {
            hsl.h = 0;
            hsl.s = 0;
            hsl.l = max;
        }

        // Ensure hue is positive
        if (hsl.h < 0) {
            hsl.h += 360;
        }

        return hsl;
    }

    void Colour::setA(int a) {
        this->value |= (a & 0xff) << 24;
    }

    void Colour::setR(int r) {
        this->value |= (r & 0xff) << 16;
    }

    void Colour::setG(int g) {
        this->value |= (g & 0xff) << 8;
    }

    void Colour::setB(int b) {
        this->value |= (b & 0xff);
    }

    void Colour::setRaw(int raw) {
        this->value = raw;
    }
};