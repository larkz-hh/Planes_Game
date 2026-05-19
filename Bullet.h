#ifndef BULLET_H
#define BULLET_H
#include <graphics.h>

class Bullet {
public:
    int x, y;
    int speed;
    int damage; //子弹伤害
    bool alive; //子弹存在

    // 构造函数
    Bullet(int _x, int _y, int _speed, int _damage);
    virtual ~Bullet() {}

    virtual void move() = 0; 
    virtual void draw() = 0; 
};

// 玩家的子弹 (向上飞)
class PlayerBullet : public Bullet {
public:
    PlayerBullet(int _x, int _y);
    void move() override;
    void draw() override;
};

// 敌人的子弹 (向下飞)
class EnemyBullet : public Bullet {
public:
    EnemyBullet(int _x, int _y);
    void move() override;
    void draw() override;
};

#endif