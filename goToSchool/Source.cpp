#include <iostream>
#include <SDL.h>
#include <SDL_image.h> // Để làm việc với hình ảnh

int main(int argc, char* argv[])
{
    

    int screenWidth = 1920; // Kích thước màn hình ngang
    int screenHeight = 1080; // Kích thước màn hình dọc

    int windowWidth = 1110; // Kích thước cửa sổ ngang
    int windowHeight = 600; // Kích thước cửa sổ dọc

    int x = (screenWidth - windowWidth) / 2; // Tính toán vị trí x
    int y = (screenHeight - windowHeight) / 2; // Tính toán vị trí y

    SDL_Window* win = SDL_CreateWindow("Test", x, y, windowWidth, windowHeight, 0);
    if (!win)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // Tải ảnh bằng SDL_image

    bool quit = false;
    SDL_Event event;

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    quit = true;
                }
            }
        }

        // Xóa renderer
        SDL_RenderClear(renderer);

        // Cập nhật renderer
        SDL_RenderPresent(renderer);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
