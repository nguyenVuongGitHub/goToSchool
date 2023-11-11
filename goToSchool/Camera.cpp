//#include "Camera.h"
//
//Camera::Camera()
//{
//	camera = { 0,0,0,0 };
//}
//
//Camera::Camera(SDL_FRect camera)
//{
//	this->camera = camera;
//}
//
//void Camera::init(SDL_Renderer* renderer)
//{
//    map.loadMap(renderer,);
//	camera = { 0,0,1920,1080};
//}
//
//void Camera::cameraFolowingPlayer(Player& p)
//{
//	camera.x = p.getRect().x - camera.w / 2;
//	camera.y = p.getRect().y - camera.h / 2;
//    if (camera.x < 0) {
//        camera.x = 0;
//    }
//    if (camera.y < 0) {
//        camera.y = 0;
//    }
//    if (camera.x > 2048 - camera.w) {
//        camera.x = 2048 - camera.w;
//    }
//    if (camera.y > 2048 - camera.h) {
//        camera.y = 2048 - camera.h;
//    }
//
//}
//
//void Camera::update(Player &p)
//{
//    
//	cameraFolowingPlayer(p);
//}
//
//void Camera::render(SDL_Renderer* renderer)
//{
//    for (int i = 0; i < 32; i++)
//    {
//        for (int j = 0; j < 32; j++)
//        {
//            int x = map.getTilemap(i, j);
//            src = map.getSelectTile(x);
//            SDL_FRect newr = map.getTile(i, j);
//            newr.x = map.getTile(i, j).x - camera.x;
//            newr.y = map.getTile(i, j).y - camera.y;
//            SDL_RenderCopyF(renderer, map.getTexture(), &src,&newr );
//        }
//    }
//}
//
//SDL_FRect Camera::getCamera()
//{
//	return camera;
//}
