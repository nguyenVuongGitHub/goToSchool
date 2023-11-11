#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include<SDL_image.h>
#include "Common.h"
#include <vector>
#include "FlatVector.h"
#include "Enemy.h"
#include "Player.h"
class Barrier : public Object
{
public:
    // Số ô x y
    int x, y;
    vector<FlatVector> vertices;
};


class Map {
private:
    SDL_Texture* tile_texture;
    SDL_FRect tile[32][32]; // Thông số vị trí các ô
    SDL_Rect select_tile[55]; // Lấy dữ liệu từ hình ảnh nguồn để render
    int tilemap[32][32]; // Dữ liệu map
    vector<Barrier> wall;
public:
    
    Map(){
        tile_texture = NULL;
    }
    ~Map();
    vector<Barrier> getWall()
    {
        return wall;
    }
    int getTilemap(int i, int j) { return tilemap[i][j]; }
    SDL_Texture* getTexture() { return tile_texture; }
    SDL_FRect getTile(int i, int j) { return tile[i][j]; }
    SDL_Rect getSelectTile(int i) { return select_tile[i]; }
    void loadTileTexture(SDL_Renderer* renderer, string filePath);
    void setmap();
    void loadTileSet();
    void InsertDataIntoTilemap(SDL_Renderer* renderer, string filePath);
    bool isWall(int tilemap);
    void loadMap(SDL_Renderer* renderer, QuadTree* qtree);
    void initWall(QuadTree* qtree);
    void render(SDL_Renderer* renderer, Player& player);
};
#endif
