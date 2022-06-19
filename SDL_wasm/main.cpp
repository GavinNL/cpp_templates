#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/fetch.h>
#endif
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <future>
#include <thread>
#include <iostream>

SDL_Window   *window;
SDL_Renderer *renderer;
SDL_Surface  *surface;

#ifdef __EMSCRIPTEN__
void downloadSucceeded(emscripten_fetch_t *fetch) {
  printf("Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);
  // The data is now available at fetch->data[0] through fetch->data[fetch->numBytes-1];
  emscripten_fetch_close(fetch); // Free data associated with the fetch.
}

void downloadFailed(emscripten_fetch_t *fetch) {
  printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);
  emscripten_fetch_close(fetch); // Also free data on failure.
}
#endif

bool doInputs()
{
    SDL_Event event;

    bool dontQuit = true;

    // Events management
    while (SDL_PollEvent(&event))
    {
        switch (event.type) {

        case SDL_QUIT:
            // handling of close button
            //close = 1;
            dontQuit = false;
            break;
        case SDL_MOUSEMOTION:
            std::cout << "Mouse Motion: " << event.motion.x << std::endl;
            break;
        default:
                break;
            }
    }
    return dontQuit;
}

void drawRandomPixels() 
{
    doInputs();
    if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);

    Uint8 * pixels = static_cast<Uint8*>(surface->pixels);
    
    for (int i=0; i < 1048576; i++)

    {
        char randomByte = rand() % 255;
        pixels[i] = randomByte;
    }

    if (SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);

    SDL_Texture *screenTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);
    //SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
    {

        SDL_Rect r{40,40,50,50};
        SDL_RenderCopyEx(renderer, screenTexture, NULL, &r,0.0, NULL,SDL_FLIP_NONE);
    }
    {
        SDL_Rect r{10,10,50,50};
        SDL_SetRenderDrawColor(renderer, 255,0,0,255);
        SDL_RenderFillRect(renderer,&r);
    }

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(screenTexture);
}

int main(int argc, char* argv[]) 
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(512, 512, 0, &window, &renderer);
    surface = SDL_CreateRGBSurface(0, 512, 512, 32, 0, 0, 0, 0);
    
    #ifdef __EMSCRIPTEN__
        emscripten_fetch_attr_t attr;
        emscripten_fetch_attr_init(&attr);
        strcpy(attr.requestMethod, "GET");
        attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
        attr.onsuccess = downloadSucceeded;
        attr.onerror = downloadFailed;

        emscripten_fetch(&attr, "/home/gavin/file.html");

        emscripten_set_main_loop(drawRandomPixels, 0, 1);
    #else
        while(doInputs())
        {
            drawRandomPixels();
            SDL_Delay(16);
        }
    #endif 
}
