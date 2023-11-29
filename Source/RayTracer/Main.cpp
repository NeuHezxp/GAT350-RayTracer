#include <iostream>
#include <ctime>
#include "Random.h"
#include "Ray.h"
#include "Renderer.h"
#include "Canvas.h"
int main(int argc, char* argv[])
{
	std::cout << "Hello World" << std::endl;
	Random random;
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", 400, 300);
	Canvas canvas(400, 300, renderer);
	random.seedRandom(static_cast<unsigned int>(time(nullptr)));
	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		canvas.Clear({ 0, 0, 0, 1 });
		for (int i = 0; i < 1000; i++) {
			glm::ivec2 randomPoint = glm::ivec2(random.random(0, 399), random.random(0, 299));
			Color::color4_t randomColor = Color::color4_t(random.random(0,244), random.random(0, 244), random.random(0, 244), 1.0f);
			canvas.DrawPoint(randomPoint, randomColor);
		}
		canvas.Update();

		renderer.PresentCanvas(canvas);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
	}

	renderer.Shutdown();

	return 0;
}
/*
 * (RGBA >> 24)
 * red = (0 - 255) - > (0.0 - 1.0)
 * red = 255/255.0f -> 1.0
 * red = (rgba >> 24) / 255.0f;
 *
 *
 *green = rgba >> 16
 *
 *color.r = (rgba >> 24) & 0xff) / 255.0f;
 *color.g = (rgba >> 16) & 0xff) / 255.0f;
 *color.b = (rgba >> 8) & 0xff) / 255.0f;
 *
 *color conversion------
 *color = 1.0 1.0 1.0 1.0
 *red = 1.0 * 255
 *green = 1.0 * 255
 *blue = 1.0 * 255
 *std::clamp(color, 0.0f, 1.0f)
 *
 *Shift it ^
 *rgba |= uint8_t(1.0 * 255) << 24
 *rgba |= uint8_t(1.0 * 255) << 16
 *rgba |= uint8_t(1.0 * 255) << 8
 *--------------------------------------
 *lerp(a,b,t) = a+t*(b-a)
 *
 *
 *--------Canvas--------
 *Texture RGBA8888
 *sdl_texture*
 *
 *needs a buffer
 *rgba_t or uint32_t --> std::vector<rgba_t>
 *
 *void DrawPoint(const glm::ivec2& point, const color4_t& color);
 *buffer[pointx + (point.y * m_size.x)] = ColorToRGBA(color);
 *<= width reject the point
 *
 *void Canvas::Clear(Const color$_t& color);
 *for (int i = 0; i < m_size.x * m_size.y; i++)
 *{
 *	rgba_t rgba = ColorToRGBA(color);
 *	m_buffer[i] = rgba;
 *} BRUTE FORCE METHOD
 *rgba_t rgba = ColorToRGBA(color);
 *std::fill(m_buffer.begin(),)
 *
 *pitch = width of buffer in bytes
 */
