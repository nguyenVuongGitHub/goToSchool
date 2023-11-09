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


    for (int x = 0; x < 32; x++) {
        for (int y = 0; y < 32; y++) {
            tile[x][y].x = y * 64;
            tile[x][y].y = x * 64;
            tile[x][y].w = 64;
            tile[x][y].h = 64;
        }
    }
}

void Map::loadTileSet() {
    
    //int tam1, tam2, tam3, tam4;
    //tam1 = tilemap[0][0];
    //tam2 = tilemap[0][1];
    //tam3 = tilemap[0][2];
    //tam4 = tilemap[0][3];
    //int* p = &tilemap[0][0];
    int tmp = 1;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 9; j++) {
            select_tile[tmp].x = j * 64;
            select_tile[tmp].y = i * 64;
            select_tile[tmp].w = 64;
            select_tile[tmp].h = 64;
            tmp++;

        }
        //cout << "i = " << i << " p = " << p << "    *p =" << *p << endl;
    }
    /*tilemap[0][0] = tam1;
    tilemap[0][1] = tam2;
    tilemap[0][2] = tam3;
    tilemap[0][3] = tam4;*/

    //cout << "sau cung : tilemap: " << tilemap[0][0] << "\n"; //512
    //cout << "sau cung : tilemap: " << tilemap[0][1] << "\n"; //320
    //cout << "sau cung : tilemap: " << tilemap[0][2] << "\n"; //64
    //cout << "sau cung : tilemap: " << tilemap[0][3] << "\n"; //64

}

bool Map::isWall(int tilemap)
{
    vector<int> choose = {7,8,9,16,18,25,26,27};
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
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            inputFile >> tilemap[i][j];
            //cout << tilemap[i][j] << " ";
            if (isWall(tilemap[i][j]))
            {
                x.x = i;
                x.y = j;
                x.vertices = {};
                x.r = { (float)i * 64, (float)j * 64, 64, 64 };
                wall.push_back(x);
            }
            if (tilemap[i][j] == 15)
            {
                Enemy e;
                e.init(j,i,renderer,"img/ball.png");
                enemyList.push_back(e);
            }
        }
    }
    inputFile.close();
}

void Map::initWall()
{
    for (int i = 0; i < wall.size(); i++)
    {
        wall[i].vertices.push_back({ tile[wall[i].x][wall[i].y].x, tile[wall[i].x][wall[i].y].y });
        wall[i].vertices.push_back({ tile[wall[i].x][wall[i].y].x + tile[wall[i].x][wall[i].y].w, tile[wall[i].x][wall[i].y].y });
        wall[i].vertices.push_back({ tile[wall[i].x][wall[i].y].x + tile[wall[i].x][wall[i].y].w, tile[wall[i].x][wall[i].y].y + tile[wall[i].x][wall[i].y].h });
        wall[i].vertices.push_back({ tile[wall[i].x][wall[i].y].x, tile[wall[i].x][wall[i].y].y + tile[wall[i].x][wall[i].y].h });
    }
}

void Map::loadMap(SDL_Renderer* renderer) {
    InsertDataIntoTilemap(renderer, "map/final.txt");
    
    loadTileTexture(renderer, "map/map_final.png");
    loadTileSet();
    setmap();
    initWall();
}

void Map::render(SDL_Renderer* map_renderer)
{
    for (int x = 0; x < 32; x++) {
        for (int y = 0; y < 32; y++) {
            switch (tilemap[x][y]) {
            case 1:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[1], &tile[x][y]);
                break;
            case 2:
              SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[2], &tile[x][y]);
                break;
            case 3:
              SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[3], &tile[x][y]);
                break;
            case 4:
              SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[4], &tile[x][y]);
                break;
            case 5:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[5], &tile[x][y]);
                break;
            case 6:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[6], &tile[x][y]);
                break;
            case 7:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[7], &tile[x][y]);
                break;
            case 8:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[8], &tile[x][y]);
                break;
            case 9:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[9], &tile[x][y]);
                break;
            case 10:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[10], &tile[x][y]);
                break;
            case 11:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[11], &tile[x][y]);
                break;
            case 12:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[12], &tile[x][y]);
                break;
            case 13:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[13], &tile[x][y]);
                break;
            case 14:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[14], &tile[x][y]);
                break;
            case 15:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[15], &tile[x][y]);
                break;
            case 16:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[16], &tile[x][y]);
                break;
            case 17:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[17], &tile[x][y]);
                break;
            case 18:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[18], &tile[x][y]);
                break;
            case 19:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[19], &tile[x][y]);
                break;
            case 20:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[20], &tile[x][y]);
                break;
            case 21:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[21], &tile[x][y]);
                break;
            case 22:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[22], &tile[x][y]);
                break;
            case 23:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[23], &tile[x][y]);
                break;
            case 24:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[24], &tile[x][y]);
                break;
            case 25:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[25], &tile[x][y]);
                break;
            case 26:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[26], &tile[x][y]);
                break;
            case 27:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[27], &tile[x][y]);
                break;
            case 28:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[28], &tile[x][y]);
                break;
            case 29:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[29], &tile[x][y]);
                break;
            case 30:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[30], &tile[x][y]);
                break;
            case 31:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[31], &tile[x][y]);
                break;
            case 32:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[32], &tile[x][y]);
                break;
            case 33:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[33], &tile[x][y]);
                break;
            case 34:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[34], &tile[x][y]);
                break;
            case 35:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[35], &tile[x][y]);
                break;
            case 36:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[36], &tile[x][y]);
                break;
            case 37:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[37], &tile[x][y]);
                break;
            case 38:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[38], &tile[x][y]);
                break;
            case 39:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[39], &tile[x][y]);
                break;
            case 40:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[40], &tile[x][y]);
                break;
            case 41:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[41], &tile[x][y]);
                break;
            case 42:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[42], &tile[x][y]);
                break;
            case 43:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[43], &tile[x][y]);
                break;
            case 44:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[44], &tile[x][y]);
                break;
            case 45:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[45], &tile[x][y]);
                break;
            case 46:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[46], &tile[x][y]);
                break;
            case 47:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[47], &tile[x][y]);
                break;
            case 48:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[48], &tile[x][y]);
                break;
            case 49:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[49], &tile[x][y]);
                break;
            case 50:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[50], &tile[x][y]);
                break;
            case 51:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[51], &tile[x][y]);
                break;
            case 52:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[52], &tile[x][y]);
                break;
            case 53:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[53], &tile[x][y]);
                break;
            case 54:
               SDL_RenderCopyF(map_renderer, tile_texture, &select_tile[54], &tile[x][y]);
                break;
            }
        }
    }
}


