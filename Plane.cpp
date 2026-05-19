#include "Plane.h" 


Plane::Plane(int _x, int _y, int _size,int _hp) {
    x = _x;
    y = _y;
    size = _size;
    hp = _hp;
    maxHp = _hp;
    speedX = 0;
    speedY = 0;
    alive = true;
    isExploding = false;
    explodeTimer = 0;
}

// // 绘制函数
// void Plane::draw() {
//     setfillcolor(WHITE);
//     fillrectangle(x, y, x + size, y + size);
// }


//受伤害
void Plane::beShot(int damage) {
    if (isExploding || !alive) return; 
    hp -= damage;
    if (hp <= 0) {
        hp = 0;
        explode();
    }
}
void Plane::explode() {
    isExploding = true;
    explodeTimer = 10; //爆炸动画持续约10帧
}