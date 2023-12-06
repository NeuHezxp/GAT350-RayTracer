#pragma once
#include <iostream>
#include <SDL.h>

namespace ray
{
	class Canvas;
	class Renderer
	{
	public:
		Renderer() = default;

		bool Initialize();
		void Shutdown();
		bool CreateWindow(const std::string& title, int width, int height);

		void PresentCanvas(const Canvas& canvas);
		friend class Canvas;

	private:
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;
	};
}
