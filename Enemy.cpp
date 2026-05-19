#include "Enemy.h"

extern IMAGE img_enemy;    
extern IMAGE img_explode; 
extern IMAGE img_boss;
extern IMAGE img_fast;

Enemy::Enemy(int _x, int _y, int _size, int _hp, int _scoreValue) 
    : Plane(_x, _y, _size, _hp),scoreValue(_scoreValue) {}

Enemy::~Enemy() { for (auto b : bullets) delete b; }

void Enemy::updateBullets() {
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        (*it)->move();
        if (!(*it)->alive) {
            delete *it;
            it = bullets.erase(it);
        } else {
            ++it;
        }
    }
}

// 普通敌机 10血
SmallEnemy::SmallEnemy(int _x, int _y) : Enemy(_x, _y, 30, 10, 100)  {
    speedX = rand() % 3 + 1; speedY = rand() % 3 + 1;
}

void SmallEnemy::move(int w, int h) {
    if (isExploding) return;
    x += speedX; y += speedY;
    if (x <= 0 || x + size >= w) speedX = -speedX;
    if (y <= 0 || y + size >= h) speedY = -speedY;
}
void SmallEnemy::draw() {
    if (!alive) return;
    if (isExploding) {
        putimage(x, y, &img_explode);
        if (--explodeTimer <= 0) alive = false;
    } else putimage(x, y, &img_enemy);
}

// 快速敌机 10血
FastEnemy::FastEnemy(int _x, int _y) : Enemy(_x, _y, 20, 10, 200) {
    speedX = (rand() % 2 == 0 ? 5 : -5); speedY = 6;
}

void FastEnemy::move(int w, int h) {
    if (isExploding) return;
    x += speedX; y += speedY;
    if (x <= 0 || x + size >= w) speedX = -speedX;
    if (y > h) alive = false;
}
void FastEnemy::draw() {
    if (!alive) return;
    if (isExploding) {
        putimage(x, y, &img_explode);
        if (--explodeTimer <= 0) alive = false;
    } else putimage(x, y, &img_fast);
}

// Boss 50血
BossEnemy::BossEnemy(int _x, int _y) : Enemy(_x, _y, 60, 50, 500) {
    speedX = 4; speedY = 0;
    stateTimer = 50; 
    isMovingState = true;
    shootCooldown = 0;
}

void BossEnemy::move(int w, int h) {
    if (isExploding) return;
    
    updateBullets(); //更新子弹

    stateTimer--;
    //移动状态
    if (isMovingState) { 
        x += speedX;
        if (x <= 0 || x + size >= w) speedX = -speedX;
        if (stateTimer <= 0) {
            isMovingState = false; // 切换到射击状态
            stateTimer = 40;       // 停留射击40帧
        }
    } else { //射击状态
        if (shootCooldown > 0) shootCooldown--;
        if (shootCooldown <= 0) {
            
            bullets.push_back(new EnemyBullet(x + size / 2 - 5, y + size));
            shootCooldown = 10;
        }
        if (stateTimer <= 0) {
            isMovingState = true;  // 切换回移动状态
            stateTimer = 60;       // 移动60帧
        }
    }
}
void BossEnemy::draw() {
    for (auto b : bullets) b->draw(); 
    if (!alive) return;

    if (isExploding) {
        putimage(x, y, &img_explode);
        if (--explodeTimer <= 0) alive = false;
    } else {
        putimage(x, y, &img_boss);
        // 画血条
        // setlinecolor(RED);
        // rectangle(x, y - 5, x + size, y - 2);
        // setfillcolor(RED);
        // solidrectangle(x, y - 5, x + (size * hp / maxHp), y - 2);
         if (maxHp > 0 && hp > 0) { 

            setlinecolor(WHITE); 
            rectangle(x, y - 8, x + size, y - 4);
            setfillcolor(RED);
            
            int barWidth = (int)(size * ((float)hp / maxHp)); 
            solidrectangle(x, y - 8, x + barWidth, y - 4);
        }
    }
    

    
}