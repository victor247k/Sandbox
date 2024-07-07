#include "sandbox.h"

sandbox::sandbox(int _width, int _height, int _scale, SDL_Window *_window, SDL_Renderer *_renderer) {
    scale = _scale;
    width = _width / scale;
    height = _height / scale;
    window = _window;
    renderer = _renderer;
    for (int i = 0; i < height; i++) {
        std::vector<elements> row(width, empty);
        grid.push_back(row);
    }
}

void sandbox::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            auto colors = colorMap[grid[r][c]];
            SDL_SetRenderDrawColor(renderer, colors[0], colors[1], colors[2], SDL_ALPHA_OPAQUE);
            SDL_Rect dest;
            dest.x = c * scale;
            dest.y = r * scale;
            dest.h = dest.w = scale;
            SDL_RenderFillRect(renderer, &dest);
        }
    }
    SDL_RenderPresent(renderer);
}
void sandbox::placeElement(int x, int y, elements type) {
    x /= scale;
    y /= scale;
    if (x >= 0 && x < width && y >= 0 && y < height)
        grid[y][x] = type;
}

void sandbox::update() {
    //std::vector<std::vector<elements>> updatedGrid = grid;
    for (int r = height - 1; r >= 0; r--) {
        for (int c = 0; c < width; c++) {
            switch (grid[r][c]) {
                case empty:
                    continue;
                case wood:
                    continue;
                break;
                case sand:
                    if (r + 1 < height && grid[r+1][c] == empty) {
                        grid[r+1][c] = sand;
                        grid[r][c] = empty;
                    } else if (r + 1 < height && c - 1 >= 0 && grid[r+1][c-1] == empty) {
                        grid[r+1][c-1] = sand;
                        grid[r][c] = empty;
                    } else if (r + 1 < height && c + 1 < width && grid[r+1][c+1] == empty) {
                        grid[r+1][c+1] = sand;
                        grid[r][c] = empty;
                    } else if (r + 1 < height && grid[r+1][c] == water) {
                        grid[r+1][c] = sand;
                        grid[r][c] = water;
                    } else if (r + 1 < height && c - 1 >= 0 && grid[r+1][c-1] == water) {
                        grid[r+1][c-1] = sand;
                        grid[r][c] = water;
                    } else if (r + 1 < height && c + 1 < width && grid[r+1][c+1] == water) {
                        grid[r+1][c+1] = sand;
                        grid[r][c] = water;
                    }
                    break;
                case water:
                    if (r + 1 < height && grid[r + 1][c] == empty) {
                        grid[r + 1][c] = water;
                        grid[r][c] = empty;
                    }
                    else if (r + 1 < height && c - 1 >= 0 && grid[r + 1][c - 1] == empty) {
                        grid[r + 1][c - 1] = water;
                        grid[r][c] = empty;
                    }
                    else if (r + 1 < height && c + 1 < width && grid[r + 1][c + 1] == empty) {
                        grid[r + 1][c + 1] = water;
                        grid[r][c] = empty;
                    }
                    else if (c + 1 < width && grid[r][c + 1] == empty) {
                        grid[r][c + 1] = water;
                        grid[r][c] = empty;
                    }
                    else if (c - 1 >= 0 && grid[r][c - 1] == empty) {
                        grid[r][c - 1] = water;
                        grid[r][c] = empty;
                    }
                    break;
            }
        }
    }
//    for (int r = height - 1; r >= 0; r--)
//        for (int c = 0; c < width; c++)
//            grid[r][c] = updatedGrid[r][c];
}
