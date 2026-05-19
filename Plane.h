#ifndef PLANE_H
#define PLANE_H
#include <graphics.h>

/**
 * 战机基类
 */
class Plane {
public:
    int x, y;              // 战机位置
    int speedX, speedY;    // 移动速度
    int size;              // 战机大小
    bool alive;            // 是否存活
    int hp;                // 战机血量
    int maxHp;             // 最大血量
    bool isExploding;      // 是否正在爆炸
    int explodeTimer;      // 爆炸计时
    Plane(int _x, int _y, int _size,int hp);

    virtual ~Plane() {}

    //绘制
    virtual void draw() = 0;
    
    //受伤害
    virtual void beShot(int damage);

    //爆炸
    virtual void explode();

    //移动
    virtual void move(int width, int height) = 0; 

    
    // 移动函数
    // void moveRandom(int width, int height);
};

#endif