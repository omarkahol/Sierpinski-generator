#include <iostream>
#include "Screen.h"
#include <random>

namespace omarkahol {

Screen::Screen() {
	if (this->init()) {
		std::cout << "Program started..." << std::endl;
	} else {
		std::cout <<"Error, cannot start the program..." << std::endl;
		this->close();
	}
}

bool Screen::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}
	this->m_window = SDL_CreateWindow("SIERPINSKY TRIANGLE",
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (this->m_window == NULL) {
		SDL_Quit();
		return false;
	}
	this->m_renderer = SDL_CreateRenderer(this->m_window, -1,
			SDL_RENDERER_PRESENTVSYNC);
	this->m_texture = SDL_CreateTexture(this->m_renderer,
			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH,
			SCREEN_HEIGHT);

	if (this->m_renderer == NULL || this->m_texture == NULL) {
		SDL_DestroyWindow(this->m_window);
		SDL_DestroyRenderer(this->m_renderer);
		SDL_DestroyTexture(this->m_texture);
		SDL_Quit();
		return false;
	}

	this->m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	memset(this->m_buffer1, 0,
			this->SCREEN_HEIGHT * this->SCREEN_WIDTH * sizeof(Uint32));
	this->m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
		memset(this->m_buffer2, 0,
				this->SCREEN_HEIGHT * this->SCREEN_WIDTH * sizeof(Uint32));

	//
	return true;
}

void Screen::update() {
	SDL_UpdateTexture(this->m_texture, NULL, this->m_buffer1,
			SCREEN_WIDTH * sizeof(Uint32));

	SDL_RenderClear(this->m_renderer);
	SDL_RenderCopy(this->m_renderer, this->m_texture, NULL, NULL);
	SDL_RenderPresent(this->m_renderer);
}

bool Screen::processEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) == true) {
		if (event.type == SDL_QUIT) {
			return false;
		}
	}
	return true;
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

	if (x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT) {
		return;
	}

	Uint32 color = 0;
	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;
	color <<= 8;
	color += 0xff;
	m_buffer1[(y * SCREEN_WIDTH) + x] = color;
}


void Screen::generateBaseTriangle() {
	setPixel(Screen::SCREEN_WIDTH / 2, 0, 255, 255, 255);
	setPixel(0, Screen::SCREEN_HEIGHT - 300, 255, 255, 255);
	setPixel(Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT, 255, 255, 255);

}

void Screen::fractalDraw(Uint8 red, Uint8 green, Uint8 blue) {
	for (int i = 0; i < 10; i++) {
		int choice = (3 * (double) rand()) / RAND_MAX;

		if (choice == 0) {
			t_x += ((-t_x + SCREEN_WIDTH/2))/2;
			t_y += ((-t_y)/2);
			this->setPixel(t_x, t_y, red, green, blue);

		} else if (choice == 1) {

			t_x -= (t_x) / 2.0;
			t_y -= (t_y - SCREEN_HEIGHT) / 2.0;
			this->setPixel(t_x, t_y, red, green, blue);

		} else if (choice == 2) {

		t_x -= (t_x-SCREEN_WIDTH) / 2.0;
		t_y -= (t_y-SCREEN_HEIGHT)/2.0;
			this->setPixel(t_x, t_y, red, green, blue);
		}
	}

}

void Screen::boxBlur() {

	Uint32* temp = m_buffer1;
	m_buffer1 = m_buffer2;
	m_buffer2 = temp;

	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;

			for (int row = -1; row <= +1; row++) {
				for (int col = -1; col <= +1; col++) {

					int currentX = x + col;
					int currentY = y + row;

					if (currentX >= 0 && currentX < SCREEN_WIDTH
							&& currentY >= 0 && currentY < SCREEN_HEIGHT) {
						Uint32 color = m_buffer2[currentY * SCREEN_WIDTH
								+ currentX];
						Uint8 red = color >> 24;
						Uint8 green = color >> 16;
						Uint8 blue = color >> 8;

						redTotal += red;
						greenTotal += green;
						blueTotal += blue;
					}

				}
			}

			Uint8 red = redTotal/9;
			Uint8 green = greenTotal/9;
			Uint8 blue = blueTotal/9;

			setPixel(x,y,red,green,blue);
		}
	}

}

void Screen::close() {
	delete[] m_buffer1;
	delete[] m_buffer2;
	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
	std::cout<< "Program closing..."<<std::endl;

}

Screen::~Screen() {
	this->close();
}

} /* namespace omarkahol */
