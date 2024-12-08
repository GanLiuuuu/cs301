# 小车路径规划控制程序

实现task3，可以让小车按照预设的路径自动行走。

## 功能特点

- 支持4x4矩阵路径规划
- 自动行走和转向
- 按键触发启动
- 支持速度和时间参数调节

## 路径设置

在`main.c`中通过`PATH_MATRIX`矩阵设置路径：

```c
const int PATH_MATRIX[4][4] = {
    {0, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1}
};
```

- 矩阵中的1表示需要经过的路径点
- 1必须是连续的
- 小车起始位置固定在第二行第一列(坐标[0,1])，可以在`followPath()`函数中修改
- 小车初始朝向为正北方向(朝上)，建议这个一直作为我们的起始方向

## 参数说明

### 运动速度参数

在`followPath()`函数中：
```c
HJduino_run(70, 1000);  // 前进速度70，持续1000ms
```
- 第一个参数(70)：速度值，范围0-100
- 第二个参数(1000)：运行时间，单位为毫秒

### 转向参数

在`rotateToDirection()`函数中：
```c
HJduino_Spin_Right(speed, 500);  // 右转90度
HJduino_Spin_Right(speed, 1000); // 转180度
HJduino_Spin_Left(speed, 500);   // 左转90度
```
- speed参数：转向速度，建议与直行速度保持一致
- 时间参数：控制转向角度，可根据实际情况微调

### 刹车参数

```c
HJduino_brake(200);  // 转向后的停顿时间
HJduino_brake(500);  // 初始和循环开始的停顿时间
HJduino_brake(2000); // 路径完成后的等待时间
```
- 参数值单位为毫秒，可根据需要调整停顿时间







