# 飞机大战

一个用 C++17 写的 2D 竖版卷轴射击小游戏。

## 玩法

控制屏幕底部的飞机，射击从上方出现的敌机。清完两波敌人后迎战 Boss，击败即可通关。

**操作方式：**

| 按键   | 功能     |
| ------ | -------- |
| 方向键 | 移动     |
| Z      | 射击     |
| R      | 重新开始 |
| N      | 下一关   |
| Q      | 退出     |

## 构建

需要 **Windows**、**MinGW-w64 (TDM-GCC)** 和 [EasyX](https://easyx.cn/) 图形库。

```powershell
g++ -g -leasyx -o main.exe *.cpp
```

## 运行

```powershell
./main.exe
```

游戏窗口为 480x800。

## 项目结构

```
├── main.cpp        # 游戏主循环、渲染、碰撞检测、关卡
├── Player.h/cpp    # 玩家飞机（移动、射击）
├── Enemy.h/cpp     # 小敌机、快速敌机、Boss
├── Plane.h/cpp     # 飞机抽象基类
├── Bullet.h/cpp    # 玩家子弹、敌机子弹
├── Weapon.h        # 玩家武器管理（冷却、子弹池）
└── res/            # 图片资源
```
