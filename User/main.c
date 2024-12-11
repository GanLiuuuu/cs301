#include "stm32f10x.h"
#include "delay.h"
#include "motor.h"
#include "keysacn.h"
#include "ultrasonic.h"

#define GRID_SIZE 4
#define OBSTACLE_THRESHOLD 20
#define MOVE_SPEED 70
#define TURN_SPEED 70
#define MOVE_TIME 1000
#define TURN_TIME 500
#define BRAKE_TIME 200
#define MAX_QUEUE_SIZE 32

typedef enum {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
} Direction;

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    Position pos;
    Position parent;
    int distance;
} QueueNode;

typedef struct {
    QueueNode data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

int grid[GRID_SIZE][GRID_SIZE] = {0};
int visited[GRID_SIZE][GRID_SIZE] = {0};
Position current_pos = {0, 1};
Direction current_dir = NORTH;

const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};

void queue_init(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

int queue_is_empty(Queue* q) {
    return q->front == q->rear;
}

void queue_push(Queue* q, Position pos, Position parent, int distance) {
    if((q->rear + 1) % MAX_QUEUE_SIZE == q->front) return;
    q->data[q->rear].pos = pos;
    q->data[q->rear].parent = parent;
    q->data[q->rear].distance = distance;
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
}

QueueNode queue_pop(Queue* q) {
    QueueNode node = q->data[q->front];
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return node;
}

int is_valid_position(int x, int y) {
    return (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE);
}

int detect_obstacle(void) {
    //TODO: 接上超声波的探测方程
    int distance = get_ultrasonic_distance();
    if(distance < 0) return -1;
    return (distance < OBSTACLE_THRESHOLD);
}

void update_grid(int x, int y, int has_obstacle) {
    if(!is_valid_position(x, y)) return;
    grid[y][x] = has_obstacle ? 1 : -1;
}

void rotate_to_direction(Direction target) {
    //TODO: 现在是小车旋转，可以尝试用舵机旋转探测完270度后，小车再旋转
    int diff = (target - current_dir + 4) % 4;
    if(diff == 1 || diff == -3) {
        HJduino_Spin_Right(TURN_SPEED, TURN_TIME);
    } else if(diff == 2) {
        HJduino_Spin_Right(TURN_SPEED, TURN_TIME * 2);
    } else if(diff == 3 || diff == -1) {
        HJduino_Spin_Left(TURN_SPEED, TURN_TIME);
    }
    HJduino_brake(BRAKE_TIME);
    current_dir = target;
}

void explore_current_position(void) {
    for(int i = 0; i < 4; i++) {
        int next_x = current_pos.x + dx[current_dir];
        int next_y = current_pos.y + dy[current_dir];
        
        if(is_valid_position(next_x, next_y)) {
            int has_obstacle = detect_obstacle();
            if(has_obstacle >= 0) {
                update_grid(next_x, next_y, has_obstacle);
            }
        }
        rotate_to_direction((current_dir + 1) % 4);
    }
}

Position find_next_point_bfs(void) {
    Queue q;
    queue_init(&q);
    int bfs_visited[GRID_SIZE][GRID_SIZE] = {0};
    Position path[GRID_SIZE][GRID_SIZE];
    
    queue_push(&q, current_pos, current_pos, 0);
    bfs_visited[current_pos.y][current_pos.x] = 1;
    
    Position target = {-1, -1};
    Position next_step = current_pos;
    
    while(!queue_is_empty(&q)) {
        QueueNode node = queue_pop(&q);
        Position pos = node.pos;
        
        if(!visited[pos.y][pos.x] && grid[pos.y][pos.x] == -1) {
            target = pos;
            while(node.distance > 1) {
                path[pos.y][pos.x] = node.parent;
                pos = node.parent;
                for(int i = 0; i < MAX_QUEUE_SIZE; i++) {
                    if(q.data[i].pos.x == pos.x && q.data[i].pos.y == pos.y) {
                        node = q.data[i];
                        break;
                    }
                }
            }
            next_step = pos;
            break;
        }
        
        for(int i = 0; i < 4; i++) {
            int new_x = pos.x + dx[i];
            int new_y = pos.y + dy[i];
            
            if(is_valid_position(new_x, new_y) && !bfs_visited[new_y][new_x] && 
               grid[new_y][new_x] != 1) {
                Position new_pos = {new_x, new_y};
                queue_push(&q, new_pos, pos, node.distance + 1);
                bfs_visited[new_y][new_x] = 1;
            }
        }
    }
    
    return target.x == -1 ? current_pos : next_step;
}

void explore_and_follow_path(void) {
    for(int i = 0; i < GRID_SIZE; i++) {
        for(int j = 0; j < GRID_SIZE; j++) {
            visited[i][j] = 0;
        }
    }
    
    visited[current_pos.y][current_pos.x] = 1;
    
    while(1) {
        explore_current_position();
        Position next = find_next_point_bfs();
        
        if(next.x == current_pos.x && next.y == current_pos.y) {
            break;
        }
        
        visited[next.y][next.x] = 1;
        
        Direction target_dir;
        if(next.x > current_pos.x) target_dir = EAST;
        else if(next.x < current_pos.x) target_dir = WEST;
        else if(next.y > current_pos.y) target_dir = SOUTH;
        else target_dir = NORTH;
        
        rotate_to_direction(target_dir);
        HJduino_run(MOVE_SPEED, MOVE_TIME);
        HJduino_brake(BRAKE_TIME);
        current_pos = next;
    }
}

int main(void) {
    delay_init();
    KEY_Init();
    TIM4_PWM_Init(7199,0);
    init_ultrasonic();
    HJduino_brake(500);
    
    while(1) {
        HJduino_brake(500);
        keysacn();
        explore_and_follow_path();
        HJduino_brake(2000);
    }
}