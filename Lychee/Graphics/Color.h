#pragma once

#include <algorithm>
#include <cstdint>

/**
 * \brief Represents an ARGB color.
 */
struct Color
{
    /**
     * \brief The red component of this color.
     */
    uint8_t R = 255;
    /**
     * \brief The green component of this color.
     */
    uint8_t G = 255;
    /**
     * \brief The blue component of this color.
     */
    uint8_t B = 255;
    /**
     * \brief The alpha component of this color.
     */
    uint8_t A = 255;

    /**
     * \brief Constructs white color.
     */
    Color() = default;

    /**
     * \brief Constructs new color from the four ARGB component (alpha, red, green, and blue) values.
     * \param r The red component.
     * \param g The green component.
     * \param b The blue component.
     * \param a The alpha component.
     */
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        R = r;
        G = g;
        B = b;
        A = a;
    }

    /**
     * \brief Constructs new color from a 32-bit ARGB value.
     * \param hex 32-bit ARGB value.
     */
    Color(unsigned int hex)
    {
        R = (hex >> 24) & 0xFF;
        G = (hex >> 16) & 0xFF;
        B = (hex >> 8) & 0xFF;
        A = hex & 0xFF;
    }

    [[nodiscard]] Color Multiply(Color color) const
    {
        return
        {
            static_cast<uint8_t>(std::clamp(static_cast<float>(R) / 255.f * (static_cast<float>(color.R) / 255.f) * 255.f, 0.f, 255.f)),
            static_cast<uint8_t>(std::clamp(static_cast<float>(G) / 255.f * (static_cast<float>(color.G) / 255.f) * 255.f, 0.f, 255.f)),
            static_cast<uint8_t>(std::clamp(static_cast<float>(B) / 255.f * (static_cast<float>(color.B) / 255.f) * 255.f, 0.f, 255.f)),
            static_cast<uint8_t>(std::clamp(static_cast<float>(A) / 255.f * (static_cast<float>(color.A) / 255.f) * 255.f, 0.f, 255.f)),
        };
    }

    /**
     * \brief Gets the 32-bit ARGB value of this color.
     * \return 32-bit ARGB value.
     */
    [[nodiscard]] unsigned int ToHex() const
    {
        return ((R & 0xFF) << 24) + ((G & 0xFF) << 16) + ((B & 0xFF) << 8) + (A & 0xFF);
    }

    /**
     * \brief Gets the 32-bit ARGB value of this color, applying the specified alpha factor to it.
     * \param alpha Alpha factor.
     * \return 32-bit ARGB value.
     */
    [[nodiscard]] unsigned int ToHex(float alpha) const
    {
        alpha = std::clamp(alpha, 0.f, 1.f);

        return ((R & 0xFF) << 24) + ((G & 0xFF) << 16) + ((B & 0xFF) << 8) + (static_cast<unsigned char>(alpha * static_cast<float>(A)) & 0xFF);
    }

    /**
     * \brief Gets the ImGui-readable 32-bit ARGB value of this color.
     * \return ImGui-readable 32-bit ARGB value.
     */
    [[nodiscard]] unsigned int ToImGuiHex() const
    {
        return R << 0 | G << 8 | B << 16 | A << 24;
    }

    /**
     * \brief Gets the ImGui-readable 32-bit ARGB value of this color, applying the specified alpha factor to it.
     * \param alpha Alpha factor.
     * \return ImGui-readable 32-bit ARGB value.
     */
    [[nodiscard]] unsigned int ToImGuiHex(float alpha) const
    {
        alpha = std::clamp(alpha, 0.f, 1.f);

        return R << 0 | G << 8 | B << 16 | static_cast<unsigned char>(alpha * static_cast<float>(A)) << 24;
    }
};
