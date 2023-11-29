#pragma once
#include <iostream>
#include <SDL.h>

class Canvas;
class Renderer
{
public:
	Renderer() = default;

	bool Initialize();
	void Shutdown();
	bool CreateWindow(const std::string& title, int width, int height);

	void PresentCanvas();
	void PresentCanvas(const Canvas& canvas);


private:
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
	friend class Canvas;

};