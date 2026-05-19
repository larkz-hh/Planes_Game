#ifndef WEAPON_H
#define WEAPON_H

#include <vector>
#include "Bullet.h"

class Weapon {
public:
    std::vector<Bullet*> bullets;
    int cooldown; //控制射速

    Weapon() {
        cooldown = 0;
    }
    ~Weapon() {
        for (auto b : bullets) {
            delete b;
        }
    }
    // 发射子弹
    void fire(int spawnX, int spawnY) {
        if (cooldown <= 0) {
            bullets.push_back(new PlayerBullet(spawnX, spawnY));
            cooldown = 7; 
        }
    }

    // 更新所有子弹的状态
    void update() {
        if (cooldown > 0) cooldown--;

        for (auto it = bullets.begin(); it != bullets.end(); ) {
            (*it)->move();       
            if (!(*it)->alive) {
                delete *it; //释放内存       
                it = bullets.erase(it); 
            } else {
                ++it;
            }
        }
    }

    // 绘制所有子弹
    void draw() {
        for (auto b : bullets) {
            b->draw();           
        }
    }
};

#endif