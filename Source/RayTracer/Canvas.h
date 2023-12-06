#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Renderer.h"  // Include the Renderer header
#include "Color.h"

namespace ray
{
    class Canvas
    {
    public:
        Canvas(int width, int height, const Renderer& renderer);
        ~Canvas();

        void Update();

        void Clear(const color4_t& color);
        void DrawPoint(const glm::ivec2& point, const color4_t& color);

        glm::vec2 GetSize() const { return m_size; }

        friend class Renderer;  // Allow Renderer to access Canvas private data

    private:
        SDL_Texture* m_texture = nullptr;
        std::vector<rgba_t> m_buffer;
        glm::ivec2 m_size{ 0 };
    };
}