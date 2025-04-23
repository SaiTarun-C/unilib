#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace unilib {
namespace gui {

class SDLWindow {
public:
    SDLWindow(const std::string& title, int width, int height);
    ~SDLWindow();

    void PollEvents();
    void Clear();
    void Present();
    bool IsRunning() const;

    SDL_Window* GetWindow() const;
    SDL_Renderer* GetRenderer() const;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
};

} // namespace gui
} // namespace unilib