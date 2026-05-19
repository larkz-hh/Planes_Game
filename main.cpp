#include <graphics.h> // 引入EasyX图形库
#include <cstdio>
#include <conio.h>  // 引入键盘输入库
#include <vector>   // 引入动态数组
#include <ctime>    // 引入时间库
#include "Plane.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include <tchar.h>

using namespace std;
IMAGE img_player;
IMAGE img_enemy;
IMAGE img_boss;
IMAGE img_explode;
IMAGE img_bullet;
IMAGE img_fast;


//碰撞检测
bool checkCollision(int x1, int y1, int s1, int x2, int y2, int s2) {
    return !(x1 > x2 + s2 || x1 + s1 < x2 || y1 > y2 + s2 || y1 + s1 < y2);
}

int main() {
    initgraph(480, 800);      
    srand((unsigned)time(0)); 
    
    //加载图片
    loadimage(&img_player, _T("res/me1.png"), 30, 30, true);
    loadimage(&img_enemy, _T("res/enemy1.png"), 30, 30, true); 
    loadimage(&img_fast, _T("res/enemy1.png"), 20, 20, true);
    loadimage(&img_boss, _T("res/boss.png"), 100, 100, true);
    loadimage(&img_explode, _T("res/explode1.png"), 30, 30, true);
    loadimage(&img_bullet, _T("res/bullet1.png"), 10, 20, true);

    BeginBatchDraw(); 

    bool playAgain = true; // 循环控制
    int currentLevel = 1;  // 当前关卡
    int totalScore = 0;    // 累计总分

    // ================== 游戏循环 ==================
    while (playAgain) {
        //初始化
        Player player(200, 700);  
        vector<Enemy*> enemies;    
        int score = totalScore; //玩家分数

        if (currentLevel == 1) {
            enemies.push_back(new SmallEnemy(100, 100));
            enemies.push_back(new SmallEnemy(300, 100));
            enemies.push_back(new FastEnemy(240, 50)); 
        } 
        else if (currentLevel == 2) {
            enemies.push_back(new SmallEnemy(80, 100));
            enemies.push_back(new SmallEnemy(240, 100));
            enemies.push_back(new SmallEnemy(400, 100));
            enemies.push_back(new FastEnemy(150, 50)); 
            enemies.push_back(new FastEnemy(330, 50)); 
        }

        bool bossSpawned = false; 
        bool win = false;         
        bool lose = false;

        // ================== 单局游戏的主循环 ==================
        while (true) {
            cleardevice();  

        
            if (!win && !lose) {
                //玩家操作
                player.move(480, 800); 
                if (GetAsyncKeyState('Z') & 0x8000) player.shoot();
                player.weapon.update();
                player.weapon.draw();
                player.draw();  
                
                // 左上角 UI
                if (player.alive) {
                    TCHAR uiText[50];
                    _stprintf(uiText, _T("LEVEL %d  HP: %d  SCORE: %d"), currentLevel, player.hp > 0 ? player.hp : 0, score);
                    settextcolor(WHITE);
                    settextstyle(16, 0, _T("Consolas"));
                    outtextxy(10, 10, uiText);
                }

                // 敌人更新
                for (auto e : enemies) {
                    e->move(480, 800); 
                    e->draw();             
                }      

                //玩家子弹打敌人
                for (auto b : player.weapon.bullets) {
                    if (!b->alive) continue;
                    for (auto e : enemies) {
                        if (e->alive && !e->isExploding && checkCollision(b->x, b->y, 10, e->x, e->y, e->size)) {
                            bool wasAlive = (e->hp > 0); 
                            e->beShot(b->damage); 
                            b->alive = false; 
                            if (wasAlive && e->hp <= 0) {
                                score += e->scoreValue;
                            }
                        }
                    }
                }

                //敌人子弹打玩家
                if (player.alive && !player.isExploding) {
                    for (auto e : enemies) {
                        for (auto b : e->bullets) {
                            if (b->alive && checkCollision(b->x, b->y, 10, player.x, player.y, player.size)) {
                                player.beShot(b->damage); 
                                b->alive = false;
                            }
                        }
                    }
                }
                
                // 玩家本体撞敌人
                if (player.alive && !player.isExploding) {
                    for (auto e : enemies) {
                        if (e->alive && !e->isExploding) {
                            if (checkCollision(player.x, player.y, player.size, e->x, e->y, e->size)) {
                                player.beShot(15);      
                                e->beShot(9999);        
                            }
                        }
                    }
                }

                //清理死亡敌人
                bool allEnemyDead = true;
                for (auto it = enemies.begin(); it != enemies.end(); ) {
                    if (!(*it)->alive && (*it)->bullets.empty()) {
                        delete *it; 
                        it = enemies.erase(it);
                    } else {
                        if (!(*it)->isExploding && (*it)->alive) allEnemyDead = false;
                        ++it;
                    }
                }

                //生成 Boss
                if (allEnemyDead && !bossSpawned) {
                    enemies.push_back(new BossEnemy(190, 50)); 
                    bossSpawned = true;
                }

                //胜负判定
                if (!player.alive) {
                    lose = true;
                } else if (bossSpawned) {
                    bool bossAndOthersDead = true;
                    for (auto e : enemies) {
                        if (e->alive) {
                            bossAndOthersDead = false;
                            break;
                        }
                    }
                    if (bossAndOthersDead) {
                        win = true; // 真正胜利
                    }
                }
            } 
            else {
                // 绘制结算界面
                player.weapon.draw();
                if (player.alive || player.isExploding) player.draw();
                for (auto e : enemies) e->draw();

                settextstyle(40, 0, _T("Consolas"));
                if (lose) {
                    settextcolor(RED);
                    outtextxy(140, 300, _T("GAME OVER"));
                } else if (currentLevel == 1) {
                    settextcolor(YELLOW);
                    outtextxy(90, 300, _T("LEVEL 1 CLEARED!"));
                } else {
                    settextcolor(YELLOW);
                    outtextxy(140, 300, _T("YOU WIN THE GAME!"));
                }
                
                // 显示当前得分
                TCHAR finalScore[50];
                _stprintf(finalScore, _T("SCORE: %d"), score);
                settextcolor(WHITE);
                settextstyle(24, 0, _T("Consolas"));
                outtextxy(160, 360, finalScore);

                settextstyle(20, 0, _T("Consolas"));

                // ============= 按键逻辑 =============
                if (lose) {
                    outtextxy(130, 420, _T("Press R to Restart"));
                    outtextxy(130, 450, _T("Press Q to Quit"));
                    if (GetAsyncKeyState('R') & 0x8000) { totalScore = 0; currentLevel = 1; break; }
                    if (GetAsyncKeyState('Q') & 0x8000) { playAgain = false; break; }
                } 
                else if (currentLevel == 1 && win) {
                    outtextxy(110, 420, _T("Press N to Next Level"));
                    outtextxy(130, 450, _T("Press Q to Quit"));
                    if (GetAsyncKeyState('N') & 0x8000) { totalScore = score; currentLevel = 2; break; }
                    if (GetAsyncKeyState('Q') & 0x8000) { playAgain = false; break; }
                } 
                else if (currentLevel == 2 && win) {
                    outtextxy(130, 420, _T("Press R to Restart"));
                    outtextxy(130, 450, _T("Press Q to Quit"));
                    if (GetAsyncKeyState('R') & 0x8000) { totalScore = 0; currentLevel = 1; break; }
                    if (GetAsyncKeyState('Q') & 0x8000) { playAgain = false; break; }
                }
            }

            FlushBatchDraw(); //刷新双缓冲
            Sleep(30); 
        }
        // ================== 结束单局循环 ==================

        // 清理上一局残余内存
        for (auto e : enemies) delete e;
        enemies.clear();
    }
    // ================== 游戏循环结束 ==================

    EndBatchDraw();
    closegraph(); 
    return 0;
}