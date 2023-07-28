#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define WIDTH 720
#define HEIGHT WIDTH
#define CAPACITY WIDTH / RECTANGLE_WIDTH
#define SHUFFLE 200
#define RECTANGLE_WIDTH 6

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
size_t sortSpace[CAPACITY] = {  };
size_t selectedElement = 0;

void swap(size_t i, size_t j)
{
	size_t num1 = sortSpace[i];
	size_t num2 = sortSpace[j];
	sortSpace[i] = num2;
	sortSpace[j] = num1;
}

void initSortSpace()
{
	for (size_t i = 0; i < CAPACITY; ++i) sortSpace[i] = i + 1;
	for (size_t i = 0; i < SHUFFLE; ++i) {
		size_t randomIndex1 = rand() % CAPACITY;
		size_t randomIndex2 = rand() % CAPACITY;
		if (randomIndex1 == randomIndex2) {
			i--;
			continue;
		}
		swap(randomIndex1, randomIndex2);
	}
}

void doBubbleSort()
{
	if (selectedElement == CAPACITY - 1) return;
	if (sortSpace[selectedElement] > sortSpace[selectedElement + 1]) swap(selectedElement, selectedElement + 1);
}

int isSorted()
{
	size_t lookBehind = 0;
	size_t lookAhead = 0;
	for (size_t i = 0; i < CAPACITY; ++i) {
		lookBehind = sortSpace[i];
		lookAhead = sortSpace[i];
		if (i > 0) {
			lookBehind = sortSpace[i - 1];
		}
		if (i < CAPACITY - 1) {
			lookAhead = sortSpace[i + 1];
		}
		if (sortSpace[i] < lookBehind || sortSpace[i] > lookAhead) return 0;
	}
	return 1;
}

void nextElement()
{
	if (++selectedElement > CAPACITY) selectedElement = 0;
}

int main(void)
{
	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_HIDDEN);
	SDL_SetWindowPosition(window, 0, 0);
	SDL_SetWindowSize(window, WIDTH, HEIGHT);
	SDL_SetWindowTitle(window, "Sorter");
	SDL_ShowWindow(window);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_Event event;
	initSortSpace();
	int running = 1;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT){
				running = 0;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				running = 0;
			}
		}
		nextElement();
		doBubbleSort();
		SDL_RenderClear(renderer);
		for (size_t i = 0; i < CAPACITY; ++i) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			if (i == selectedElement) SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_Rect rectangle;
			rectangle.x = i * RECTANGLE_WIDTH;
			rectangle.y = (HEIGHT / 1.2) - (sortSpace[i] * 3);
			rectangle.w = RECTANGLE_WIDTH;
			rectangle.h = sortSpace[i] * 3;
			SDL_RenderDrawRect(renderer, &rectangle);
			SDL_RenderFillRect(renderer, &rectangle);
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderPresent(renderer);
		SDL_Delay(2);
		if (isSorted()) running = 0;
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
