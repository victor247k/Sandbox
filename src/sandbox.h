#ifndef SANDBOX_H
#define SANDBOX_H

#include <list>
#include <vector>
#include <SDL2/SDL.h>
#include <map>

enum elements {empty, water, sand, wood, size};
static std::map<elements, std::vector<int>> colorMap = {
    {empty, {0, 0, 0}},
    {water, {0, 50, 200}},
    {sand, {194, 178, 128}},
    {wood, {139, 69, 19}},
};


class sandbox {
public:
    sandbox(int _width, int _height, int _scale, SDL_Window *_window, SDL_Renderer *_renderer);
    void update();
    void render();
    void placeElement(int x, int y, elements type);
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width, height, scale;
    std::vector<std::vector<elements>> grid;

};



#endif //SANDBOX_H
