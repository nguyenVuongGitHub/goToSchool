
#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>
#include <math.h>
#include <random>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
using namespace std;

// các định nghĩa chung khác
// 
// type bullet
#define T_556mm 0
#define T_762mm 1
#define T_900mm 2

#define USP 0
#define AK 1
#define MP5 2

#define SPEED_USP 25
#define SPEED_AK 30
#define SPEED_MP5 40


#define DISTANCE_USP 20
#define DISTANCE_AK 25
#define DISTANCE_MP5 22

#define NUMBER_BULLET_USP 2
#define NUMBER_BULLET_AK 5
#define NUMBER_BULLET_MP5 9

#define DAMAGE_USP 3
#define DAMAGE_AK 10
#define DAMAGE_MP5 7

// từ khóa để người chơi di chuyển
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SLOW 4
#define FAST 5



#endif // !COMMON_H
