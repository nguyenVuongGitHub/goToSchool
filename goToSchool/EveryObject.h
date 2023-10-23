#pragma once
#ifndef EVERYOBJECT_H
#define EVERYOBJECT_H

#include "Obj.h"
class EveryObject :
    public Object
{
public:
    EveryObject() {}
    void init(SDL_Renderer* renderer, string pathImg) override;
    void render(SDL_Renderer* renderer) override;
};

#endif // !EVERYOBJECT_H


