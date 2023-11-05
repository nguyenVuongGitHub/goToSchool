#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include<SDL_image.h>
#include "Common.h"


class Map {
private:
    SDL_Texture* tile_texture;
    SDL_Rect tile[32][32];
    SDL_Rect select_tile[54];
    int tilemap[32][32];
public:
    Map() {

    }
    Map(SDL_Renderer* renderer);
    ~Map();

    void loadTileTexture(SDL_Renderer* renderer, string filePath);
    void setmap();
    void loadTileSet();
    void InsertDataIntoTilemap(string filePath);
    void loadMap(SDL_Renderer* map_renderer);

    void render(SDL_Renderer* renderer);
};
#endif
