/*
 * Screen.h
 *
 *  Created on: Aug 28, 2018
 *      Author: omykhron
 */

#ifndef SCREEN_H_
#define SCREEN_H_
#include <SDL2/SDL.h>

namespace omarkahol {

class Screen {

public:
	const static int SCREEN_WIDTH = 800;
	const static int SCREEN_HEIGHT = 600;

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	Uint32* m_buffer1;
	Uint32* m_buffer2;
	int t_x;
	int t_y;

	void close();
	bool init();

public:

	Screen();
	~Screen();
	void generateBaseTriangle();
	void fractalDraw(Uint8 red, Uint8 green, Uint8 blue);
	bool processEvents();

	void update();
	void boxBlur();
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);

};

} /* namespace omarkahol */

#endif /* SCREEN_H_ */
