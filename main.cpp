#include "src/include/SDL2/SDL.h"
#include <cmath>
int main(int argc, char* argv[]) {
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return -1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL2 Circle and Lines Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Renderer creation failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Main loop
    bool running = true;
    SDL_Event event;
    while (running) {
        // Event handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Clear the screen with a black background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
        SDL_RenderClear(renderer);

        // Set color for the circle and lines (Red for circle, White for lines)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for the circle
        // Draw a circle at (400, 300) with a radius of 100
        for (int w = 0; w < 360; w++) {
            double angle = w * 3.14159 / 180;  // Convert degrees to radians
            int x = 400 + 100 * cos(angle);   // X position based on radius
            int y = 300 + 100 * sin(angle);   // Y position based on radius
            SDL_RenderDrawPoint(renderer, x, y);
        }

        // Set color for lines (White)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color for lines
        // Draw lines from center (400, 300)
        SDL_RenderDrawLine(renderer, 400, 300, 600, 300); // Horizontal line
        SDL_RenderDrawLine(renderer, 400, 300, 400, 500); // Vertical line
        SDL_RenderDrawLine(renderer, 400, 300, 550, 200); // Diagonal line

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
