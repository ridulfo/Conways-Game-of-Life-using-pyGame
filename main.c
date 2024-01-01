#include "shapes.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#define HEIGHT 400
#define WIDTH 400

void iterate(bool *grid, size_t width, size_t height) {
  bool *copy = malloc(width * height * sizeof(bool));
  memcpy(copy, grid, width * height * sizeof(bool));

  for (size_t y = 0; y < height; y++) {
    for (size_t x = 0; x < width; x++) {
      size_t neighbors = 0;
      for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
          if (dx == 0 && dy == 0) {
            continue;
          }
          size_t nx = x + dx;
          size_t ny = y + dy;
          if (nx >= width || ny >= height) {
            continue;
          }
          if (copy[ny * width + nx]) {
            neighbors++;
          }
        }
      }
      if (copy[y * width + x]) {
        if (neighbors < 2 || neighbors > 3) {
          grid[y * width + x] = false;
        }
      } else {
        if (neighbors == 3) {
          grid[y * width + x] = true;
        }
      }
    }
  }
  free(copy);
}

void draw_grid(SDL_Renderer *renderer, bool *grid, size_t width,
               size_t height, size_t cell_size) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  for (size_t y = 0; y < height; y++) {
    for (size_t x = 0; x < width; x++) {
      if (grid[y * width + x]) {
        SDL_Rect rect = {x * cell_size, y * cell_size, cell_size, cell_size};
        SDL_RenderFillRect(renderer, &rect);
      }
    }
  }

  SDL_RenderPresent(renderer);
}

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *window =
      SDL_CreateWindow("My Window", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

  if (!window) {
    SDL_Quit();
    return 2;
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (!renderer) {
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 3;
  }

  size_t grid_width = 200;
  size_t grid_height = 200;
  size_t cell_size = 2;

  bool grid[grid_width * grid_height];
  for(size_t i = 0; i < grid_width * grid_height; i++) {
    grid[i] = rand() % 2;
  }

  Uint32 frame_start, frame_time;

  int running = 1;
  while (running) {
    frame_start = SDL_GetTicks();
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        running = 0;
      }
    }

    iterate(grid, grid_width, grid_height);

    draw_grid(renderer, grid, grid_width, grid_height, cell_size);

    frame_time = SDL_GetTicks() - frame_start;
    printf("Frame rate: %f\n", 1000.0 / frame_time);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
