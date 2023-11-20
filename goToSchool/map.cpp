#include "map.h"

Map::~Map() {
    if (tile_texture) {
        SDL_DestroyTexture(tile_texture);
    }
}

void Map::loadTileTexture(SDL_Renderer* map_renderer, string filePath) {
    
    SDL_Surface* tile_map_surface = IMG_Load(filePath.c_str());
    if (!tile_map_surface) {
        return;
    }

    tile_texture = SDL_CreateTextureFromSurface(map_renderer, tile_map_surface);
    if (!tile_texture) {
        return;
    }

    SDL_FreeSurface(tile_map_surface);

}

void Map::setmap() {


    for (int x = 0; x < 40; x++) {
        for (int y = 0; y < 40; y++) {
            tile[x][y].x = y * 64;
            tile[x][y].y = x * 64;
            tile[x][y].w = 64;
            tile[x][y].h = 64;
        }
    }
}

void Map::loadTileSet() {
    
    int tmp = 1;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 9; j++) {
            select_tile[tmp].x = j * 64;
            select_tile[tmp].y = i * 64;
            select_tile[tmp].w = 64;
            select_tile[tmp].h = 64;
            tmp++;
        }
   }
}

bool Map::isWall(int tilemap)
{
    vector<int> choose = {7};
    if (find(choose.begin(), choose.end(), tilemap) != choose.end())
    {
        return true;
    }
    return false;
}

void Map::InsertDataIntoTilemap(SDL_Renderer *renderer, string filePath) {
    ifstream inputFile;
    inputFile.open(filePath.c_str(), ios_base::in);
    if ( !inputFile) {
        cerr << "Không thể mở tệp đầu vào." << endl;
        return;
    }

    Special x;
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) { 
            inputFile >> tilemap[i][j];
            if (tilemap[i][j] == 7)
            {
                x.x = i;
                x.y = j;
                x.vertices = {};
                x.r = { (float)j * 64, (float)i * 64, 64 * 10,64 * 10};
                wall.push_back(x);
            }
        }
    }
    
    Special x1;
    x1.r = { -64,0,64,40 * 64 };
    x1.vertices.push_back({ x1.r.x, x1.r.y });
    x1.vertices.push_back({ x1.r.x + x1.r.w, x1.r.y });
    x1.vertices.push_back({ x1.r.x + x1.r.w, x1.r.y + x1.r.h});
    x1.vertices.push_back({ x1.r.x, x1.r.h + x1.r.y });
    wall.push_back(x1);
    x1.r = { 40*64, 0,64, 64*40 };
    x1.vertices[0] = { x1.r.x, x1.r.y };
    x1.vertices[1] = { x1.r.x + x1.r.w, x1.r.y };
    x1.vertices[2] = { x1.r.x + x1.r.w, x1.r.y + x1.r.h };
    x1.vertices[3] = { x1.r.x, x1.r.h + x1.r.y };
    wall.push_back(x1);
    x1.r = { 0,64*40,39*64,64 };
    x1.vertices[0] = { x1.r.x, x1.r.y };
    x1.vertices[1] = { x1.r.x + x1.r.w, x1.r.y };
    x1.vertices[2] = { x1.r.x + x1.r.w, x1.r.y + x1.r.h };
    x1.vertices[3] = { x1.r.x, x1.r.h + x1.r.y };
    wall.push_back(x1);
    x1.r = { 0,-64,64*39,64 };
    x1.vertices[0] = { x1.r.x, x1.r.y };
    x1.vertices[1] = { x1.r.x + x1.r.w, x1.r.y };
    x1.vertices[2] = { x1.r.x + x1.r.w, x1.r.y + x1.r.h };
    x1.vertices[3] = { x1.r.x, x1.r.h + x1.r.y };
    wall.push_back(x1);
    inputFile.close();
}

void Map::initWall()
{
    for (int i = 0; i < wall.size(); i++)
    {
        wall[i].vertices.push_back({ wall[i].r.x, wall[i].r.y });
        wall[i].vertices.push_back({ wall[i].r.x + wall[i].r.w, wall[i].r.y });
        wall[i].vertices.push_back({ wall[i].r.x + wall[i].r.w, wall[i].r.y + wall[i].r.h });
        wall[i].vertices.push_back({ wall[i].r.x, wall[i].r.y + wall[i].r.h });
    }
}

void Map::clear()
{
    wall.clear();
}

void Map::loadMap(SDL_Renderer* renderer) {
    InsertDataIntoTilemap(renderer, "map/final.txt");
    
    loadTileTexture(renderer, "map/map_final.png");
    loadTileSet();
    setmap();
    initWall();
}

void Map::render(SDL_Renderer* map_renderer, float scrollX, float scrollY)
{
    for (int x = 0; x < 40; x++) {
        for (int y = 0; y < 40; y++) {
            SDL_FRect tmp = { tile[x][y].x - scrollX, tile[x][y].y - scrollY, tile[x][y].w, tile[x][y].h };
            switch (tilemap[x][y]) {
            case 1:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[1], &tmp);
                break;
            case 2:
              SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[2], &tmp);
                break;
            case 3:
              SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[3], &tmp);
                break;
//              ... còn nữa
            case 4:
              SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[4], &tmp);
                break;
            case 5:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[5], &tmp);
                break;
            case 6:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[6], &tmp);
                break;
            case 7:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[7], &tmp);
                break;
            case 8:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[8], &tmp);
                break;
            case 9:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[9], &tmp);
                break;
            case 10:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[10], &tmp);
                break;
            case 11:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[11], &tmp);
                break;
            case 12:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[12], &tmp);
                break;
            case 13:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[13], &tmp);
                break;
            case 14:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[14], &tmp);
                break;
            case 15:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[15], &tmp);
                break;
            case 16:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[16], &tmp);
                break;
            case 17:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[17], &tmp);
                break;
            case 18:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[18], &tmp);
                break;
            case 19:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[19], &tmp);
                break;
            case 20:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[20], &tmp);
                break;
            case 21:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[21], &tmp);
                break;
            case 22:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[22], &tmp);
                break;
            case 23:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[23], &tmp);
                break;
            case 24:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[24], &tmp);
                break;
            case 25:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[25], &tmp);
                break;
            case 26:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[26], &tmp);
                break;
            case 27:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[27], &tmp);
                break;
            case 28:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[28], &tmp);
                break;
            case 29:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[29], &tmp);
                break;
            case 30:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[30], &tmp);
                break;
            case 31:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[31], &tmp);
                break;
            case 32:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[32], &tmp);
                break;
            case 33:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[33], &tmp);
                break;
            case 34:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[34], &tmp);
                break;
            case 35:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[35], &tmp);
                break;
            case 36:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[36], &tmp);
                break;
            case 37:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[37], &tmp);
                break;
            case 38:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[38], &tmp);
                break;
            case 39:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[39], &tmp);
                break;
            case 40:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[40], &tmp);
                break;
            case 41:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[41], &tmp);
                break;
            case 42:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[42], &tmp);
                break;
            case 43:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[43], &tmp);
                break;
            case 44:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[44], &tmp);
                break;
            case 45:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[45], &tmp);
                break;
            case 46:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[46], &tmp);
                break;
            case 47:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[47], &tmp);
                break;
            case 48:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[48], &tmp);
                break;
            case 49:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[49], &tmp);
                break;
            case 50:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[50], &tmp);
                break;
            case 51:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[51], &tmp);
                break;
            case 52:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[52], &tmp);
                break;
            case 53:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[53], &tmp);
                break;
            case 54:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[54], &tmp);
                break;
            }
        }
    }
}


