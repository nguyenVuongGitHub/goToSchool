#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include<SDL_image.h>
#include "Common.h"
#include <vector>
#include "FlatVector.h"
#include "Enemy.h"

struct Special
{
    // Số ô x y
    int x, y;
    vector<FlatVector> vertices;
    SDL_FRect r;
};


class Map {
private:
    SDL_Texture* tile_texture;
    SDL_FRect tile[32][32]; // Thông số vị trí các ô
    SDL_Rect select_tile[55]; // Lấy dữ liệu từ hình ảnh nguồn để render
    int tilemap[32][32]; // Dữ liệu map
    vector<Special> wall;
public:
    //vector<Enemy> enemyList;
    Map(){

        tile_texture = NULL;
    }
    ~Map();
    vector<Special> getWall()
    {
        return wall;
    }
    void loadTileTexture(SDL_Renderer* renderer, string filePath);
    void setmap();
    void loadTileSet();
    void InsertDataIntoTilemap(SDL_Renderer* renderer, string filePath);
    bool isWall(int tilemap);
    void loadMap(SDL_Renderer* renderer);
    void initWall();

    void render(SDL_Renderer* renderer, float scrollX, float scrollY);
};
#endif
