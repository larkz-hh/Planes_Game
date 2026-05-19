#include "Player.h"

extern IMAGE img_player;
extern IMAGE img_explode;

//玩家hp30
Player::Player(int _x, int _y) : Plane(_x, _y, 30, 30) {}

void Player::draw() {
    if (!alive) return;
    
    if (isExploding) {
        putimage(x, y, &img_explode);
        explodeTimer--;
        if (explodeTimer <= 0) alive = false; 
    } else {
        putimage(x, y, &img_player);
    }
}

void Player::move(int width, int height) {
    // 死了或者爆炸中不能动
    if (isExploding || !alive) return; 
    if (GetAsyncKeyState(VK_LEFT) && x > 0) x -= 5;
    if (GetAsyncKeyState(VK_RIGHT) && x + size < width) x += 5;
    if (GetAsyncKeyState(VK_UP) && y > 0) y -= 5;
    if (GetAsyncKeyState(VK_DOWN) && y + size < height) y += 5;
}

void Player::shoot() {
    if (!isExploding && alive) {
        weapon.fire(x + size / 2 - 5, y); 
    }
}