#include "Bullet.h"
extern IMAGE img_bullet;

Bullet::Bullet(int _x, int _y, int _speed, int _damage) {
    x = _x; 
    y = _y; 
    speed = _speed;  
    damage = _damage; 
    alive = true; 
}


// 玩家子弹 伤害10
PlayerBullet::PlayerBullet(int _x, int _y) : Bullet(_x, _y, 10, 10) {}
void PlayerBullet::move() {
    y -= speed;
    if (y < 0) alive = false;
}

void PlayerBullet::draw() {
    putimage(x, y, &img_bullet);
}

// 敌人子弹 伤害10
EnemyBullet::EnemyBullet(int _x, int _y) : Bullet(_x, _y, 8, 10) {}
void EnemyBullet::move() {
    y += speed; 
    if (y > 800) alive = false; //飞出屏幕底端
}

void EnemyBullet::draw() {
    putimage(x, y, &img_bullet);
    // setfillcolor(RED);
    // solidcircle(x + 5, y + 10, 6);
}