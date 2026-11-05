#pragma once

class ColorPickerManager {
    std::vector< ImColor > saved_colors;
public:

    bool draw(const char* label, float col[4]);

    static ColorPickerManager& get() {
        static ColorPickerManager s{ };
        return s;
    }
};
