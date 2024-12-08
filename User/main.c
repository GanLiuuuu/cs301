// HJ-RC������ ��������С��ʵ�� 
//������߶��� ��1--��� ��2--�ں� ��1--�ں�  ��2--���
//ʵ�ֹ�����ʾ ����K1 С��������FMͬʱ�ᷢ������

#include "stm32f10x.h"
#include "delay.h"
#include "motor.h"
#include "keysacn.h"

// 1表示需要经过的路径点
const int PATH_MATRIX[4][4] = {
    {0, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1}
};
int visited[4][4] = {0};  // 已访问

typedef enum {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
} Direction;

void getNextPoint(int current_x, int current_y, int *next_x, int *next_y) {
    const int dx[] = {0, 1, 0, -1}; 
    const int dy[] = {-1, 0, 1, 0};
    int i;
    
    for(i = 0; i < 4; i++) {
        int new_x = current_x + dx[i];
        int new_y = current_y + dy[i];
        
        if(new_x >= 0 && new_x < 4 && new_y >= 0 && new_y < 4 && 
           PATH_MATRIX[new_y][new_x] == 1 && !visited[new_y][new_x]) {  // 检查是否已访问
            *next_x = new_x;
            *next_y = new_y;
            return;
        }
    }
    
    *next_x = current_x;
    *next_y = current_y;
}

// rotate according to the current direction and target direction
void rotateToDirection(Direction current, Direction target, int speed) {
    int diff = (target - current + 4) % 4;
    if(diff == 1 || diff == -3) {  // right 90 degree
        HJduino_Spin_Right(speed, 500);
    } else if(diff == 2) {  // 180 degree
        HJduino_Spin_Right(speed, 1000);
    } else if(diff == 3 || diff == -1) {  // left 90 degree
        HJduino_Spin_Left(speed, 500);
    }
    HJduino_brake(200);
}

// follow the path
void followPath(void) {
    int current_x = 0;
    int current_y = 1;  // 起始位置
    Direction current_direction = NORTH;  // 初始朝向
    Direction target_direction;
    int i, j;  // 将变量声明移到函数开始处which is required by C89 Standard

    // 重置visited数组
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            visited[i][j] = 0;
        }
    }
    
    // 标记起始位置为已访问
    visited[current_y][current_x] = 1;
    
    while(1) {
        int next_x, next_y;
        getNextPoint(current_x, current_y, &next_x, &next_y);
        
        // if there is no next point, the path is completed
        if(next_x == current_x && next_y == current_y) {
            break;
        }
        
        // 标记下一个点为已访问
        visited[next_y][next_x] = 1;
        
        ////////////////
        //rotate////////
        ////////////////
        if(next_x > current_x) target_direction = EAST;
        else if(next_x < current_x) target_direction = WEST;
        else if(next_y > current_y) target_direction = SOUTH;
        else target_direction = NORTH;
        
        rotateToDirection(current_direction, target_direction, 70);
        current_direction = target_direction;
        
        ////////////////
        //forward///////
        ////////////////
        HJduino_run(70, 1000);
        HJduino_brake(200);
        
        current_x = next_x;
        current_y = next_y;
    }
}

int main(void)
{    
    delay_init();
    KEY_Init();
    TIM4_PWM_Init(7199,0);  //初始化PWM
    HJduino_brake(500);
    
    while(1)
    {  
        HJduino_brake(500);
        keysacn();      // 等待按键按下
        
        // 执行路径移动
        followPath();
        
        // 完成一次路径后等待
        HJduino_brake(2000);
    }
}


