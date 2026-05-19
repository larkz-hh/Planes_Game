#ifndef PLAYER_H
#define PLAYER_H

#include "Plane.h"      
#include "Bullet.h"   
#include <vector>   
#include <conio.h> 
#include "Weapon.h"

class Player : public Plane {
public:
    Weapon weapon;

    Player(int _x, int _y);

    // 重写绘制
    void draw() override;

    // 玩家控制
    void move(int width, int height) override;

    // 发射子弹
    void shoot();
};

#endif