#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Color.h" 
#include <SDL.h> // Required for SDL_Texture

// Forward declarations
class Renderer; 
struct SDL_Texture;

class Canvas {
public:
    // Constructor and Destructor
    Canvas(int width, int height, const Renderer& renderer);
    ~Canvas();

    // Member functions
    void Update();
    void Clear(const Color::color4_t& color);
    void DrawPoint(const glm::ivec2& point, const Color::color4_t& color);

    // Get size of the canvas
    const glm::ivec2& GetSize() const { return m_size; }

    // Allow Renderer to access Canvas' private data
    friend class Renderer;

private:    
    // SDL Texture pointer
    SDL_Texture* m_texture = nullptr;

    // Buffer to store canvas data
    std::vector<Color::rgba_t> m_buffer;

    // Canvas size
    glm::ivec2 m_size = glm::ivec2(0, 0);
};
