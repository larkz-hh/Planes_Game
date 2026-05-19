#ifndef ENEMY_H
#define ENEMY_H

#include "Plane.h"   
#include "Bullet.h"
#include <cstdlib>     
#include <vector>

class Enemy : public Plane {
public:
    std::vector<Bullet*> bullets; //子弹
    int scoreValue; //分数

    Enemy(int _x, int _y, int _size, int _hp, int _scoreValue);
    virtual ~Enemy();

    // 清理子弹
    void updateBullets();

};


class SmallEnemy : public Enemy {
public:
    SmallEnemy(int _x, int _y);

    void draw() override;

    void move(int width, int height) override;
};

class FastEnemy : public Enemy {
public:
    FastEnemy(int _x, int _y);

    void draw() override;

    void move(int width, int height) override;
};

class BossEnemy : public Enemy {
public:
    int stateTimer;      // 状态倒计时
    bool isMovingState;  // true:移动状态, false:射击状态
    int shootCooldown;   // 射击冷却

    BossEnemy(int _x, int _y);
    
    void draw() override;
    void move(int width, int height) override;
};

#endif