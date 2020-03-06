#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include <string.h>
#include <limits.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int SElemType;

typedef struct {
	SElemType* base;
	SElemType* top;
	int stacksize;
} SqStack;


int initStack(SqStack* s);
int destroyStack(SqStack* s);
int clearStack(SqStack* s);
int stackEmpty(SqStack s);
int stackLength(SqStack s);
int push(SqStack* s, SElemType e);
int pop(SqStack* s, SElemType* e);
SElemType getTop(SqStack s);
int stackTraverse(SqStack s, void(visit)(SElemType));
void printElem(SElemType e);

// 进制转换：将指定的非负十进制整数，转换为八进制后输出
void conversion(int i);

// 行编辑程序，模拟编辑文本时的退格与清空行的操作
void lineEdit(const char buffer[]);


// 迷宫寻路	
#define M 15	// 迷宫的行数
#define N 30	// 迷宫的列数
#define X 4 	// X指示迷宫障碍出现的概率。例如，X=4，意味着遍历迷宫时遇到障碍的概率是1/4=25%
#define SleepTime 3 // SleepTime代表打印地图时的时间间隔

/* 迷宫类型定义 */
typedef enum {
	Wall, 						// 外墙
	Obstacle, 					// 迷宫内部的障碍
	Way, 						// 通路
	Impasse, 					// 死胡同
	East, South, West, North 	// 当前探索方向:东南西北
} MazeNode;
// 迷宫通道块的坐标
typedef struct {
    int x;      // 通道块的横、纵坐标定义
    int y;
} PosType;

/* 通道块信息，用于迷宫算法 */
typedef struct {
    int ord;        // 通道块的“序号”
    PosType seat;   // 通道块的“坐标位置”
    int di;         // 下一个应当访问的“方向”
} SElemType;
typedef int MazeType[M][N]; 	// 迷宫类型
void mazeMain();
int mazePath(MazeType maze, PosType start, PosType end);
void initMaze(MazeType maze, PosType* start, PosType* end);
int pass(MazeType maze, PosType seat);
PosType nextPos(PosType seat, int di);
void footPrint(MazeType maze, PosType seat);
void markPrint(MazeType maze, PosType seat, int mark);
SElemType construct(int ord, PosType seat, int di);
int equals(PosType a, PosType b);
void paintMaze(MazeType maze);




// 表达式计算
typedef SElemType OperatorType;
typedef SElemType OperandType;
static const char OP[] = {'+', '-', '*', '/', '(', ')', '#'};
static const char PrecedeTable[7][7] = {{'>', '>', '<', '<', '<', '>', '>'},
                                        {'>', '>', '<', '<', '<', '>', '>'},
                                        {'>', '>', '>', '>', '<', '>', '>'},
                                        {'>', '>', '>', '>', '<', '>', '>'},
                                        {'<', '<', '<', '<', '<', '=', ' '},
                                        {'>', '>', '>', '>', ' ', '>', '>'},
                                        {'<', '<', '<', '<', '<', ' ', '='}};

OperandType EvaluateExpression(const char exp[]);
int in(SElemType c, const char OP[]);
OperatorType precede(OperatorType o1, OperatorType o2);
OperandType operate(OperandType a, OperatorType theta, OperandType b);


// 汉诺塔
typedef struct {
	int** plates;// 汉诺塔中的圆盘信息
	int high[3]; // 三座塔各自持有盘子的数量
} Tower;

Tower T;
int hanoiStep;
void hanoi(int n, char x, char y, char z);
void move(char x, int n, char z);
void initHanoi(int n);
void printHanoi(char t1, int n, char t2);



int main(int argc, char const *argv[])
{
	// SqStack s;
	// initStack(&s);
	// conversion(842);
	
	 char x = 'x';
    char y = 'y';
    char z = 'z';
    
    printf("作为示例，假设圆盘个数为 %d ，操作步骤如下...\n", N);
    
    init(9);
    
    hanoi(9, x, y, z);

	return 0;
}


int initStack(SqStack* s) {
	if (s == NULL) {
		return 0;
	}
	(*s).base = (SElemType*) malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if ((*s).base == NULL) {
		exit(-2);
	}
	(*s).top = (*s).base;
	(*s).stacksize = STACK_INIT_SIZE;
	return 1;
}
int destroyStack(SqStack* s) {
	if (s == NULL) {
		return 0;
	}
	free((*s).base);
	(*s).base = NULL;
	(*s).top = NULL;
	(*s).stacksize = 0;
	return 1;
}

int clearStack(SqStack* s) {
	if (s == NULL || (*s).base == NULL) {
		return 0;
	}
	(*s).top = (*s).base;
	return 1;
}
int stackEmpty(SqStack s) {
	return s.top == s.base ? 1 : 0;
}
int stackLength(SqStack s) {
	if (s.base == NULL) {
		return 0;
	}

	return (int)(s.top - s.base);
}
int push(SqStack* s, SElemType e) {
	if (s == NULL || (*s).base == NULL) {
		return 0;
	}
	if ((*s).top - (*s).base >= (*s).stacksize - 1) {
		(*s).base = (SElemType*) realloc((*s).base, ((*s).stacksize + STACKINCREMENT) * sizeof(SElemType));
		if ((*s).base == NULL) {
			exit(-2);
		}
		(*s).top = (*s).base + (*s).stacksize - 1;
		(*s).stacksize += STACKINCREMENT;
	}
	*(s->top++) = e;
	return 1;
}
int pop(SqStack* s, SElemType* e) {
	if (s == NULL || (*s).base == NULL) {
		return 0;
	}

	if ((*s).top == (*s).base) {
		return 0;
	}
	*e = *(--(*s).top);
	return 1;
}
SElemType getTop(SqStack s) {
	SElemType e;
	if (s.base == NULL || s.top == s.base) {
		return '\0';
	}
	e = *(s.top - 1);
	return e;
}
int stackTraverse(SqStack s, void(visit)(SElemType)) {
	SElemType *p = s.base;
	if (s.base == NULL) {
		return 0;
	}
	while(p < s.top) {
		visit(*p++);
	}
	printf("\n");
	return 1;
}

void printElem(SElemType e) {
	printf("%d\n", e);
}

void conversion(int i) {
	SqStack s;
	initStack(&s);

	int n = 0;
	while(i != 0) {
		n = i % 8;
		i = i / 8;
		push(&s, n);
	}

	SElemType e;
	printf("%d的八进制值为：", i);
	while(!stackEmpty(s)) {
		pop(&s, &e);
		printf("%d", e);
	}
}

void lineEdit(const char buffer[]) {
	SqStack s;
	SElemType e;
	int i = 0;
	char ch = buffer[i++];

	initStack(&s);
	while(ch != EOF) {
		while(ch != EOF && ch != '\n') {
			switch(ch) {
				case '#':
					pop(&s, &e);
					break;
				case '@':
					clearStack(&s);
					break;
				default:
					push(&s, ch);
			}
			ch = buffer[i++];
		}
		stackTraverse(s, printElem);
		clearStack(&s);
		if (ch != EOF)	{
			ch = buffer[i++];
		}
	}
	stackTraverse(s, printElem);
	destroyStack(&s);
}




void mazeMain() {

}
int mazePath(MazeType maze, PosType start, PosType end) {
	SqStack s;
	SElemType e;
	PosType curPos;
	int curStep;

	initStack(&s);
	curPos = start;
	curStep = 1;
	do {
		if (pass(maze, curPos)) {
			footPrint(maze, curPos);
			e = construct(curStep, curPos, East);
			push(&s, e);
			if (equals(curPos, end)) {
				printf("\n寻路成功\n");
				return 1;
			}
			curPos = nextPos(curPos, East);
			curStep++;
		} else {
			if (!stackEmpty(s)) {
				pop(&s, &e);
				while(e.di == North && !stackEmpty(s)) {
					markPrint(maze, e.seat, Impasse);
					pop(&s, &e);
				}
				if (e.di < North) {
					++e.di;
					MarkPrint(maze, e.seat, e.di);
					push(&s, e);
					curPos = nextPos(e.seat, e.di);
					push(&s, e);
					curPos = nextPos(e.seat, e.di);
				}
			}
		}
	} while(!stackEmpty(s));
	printf("\n寻路失败\n");
	return 0;
}
void initMaze(MazeType maze, PosType* start, PosType* end) {
	int i, j, tmp;
	srand((unsigned) time(NULL));
	for (i = 0; i < M; ++i) {
		for (j = 0; j < N; ++j) {
			if (i == 0 || j == 0 || i == M - 1 || j == N - 1) {
				maze[i][j] = Wall;
			} else {
				tmp = rand() % X;
				if (tmp == 0) {
					maze[i][j] = Obstacle;
				} else {
					maze[i][j] = Way;
				}
			}
		}
	}
	(*start).x = 1;
	(*start).y = 0;

	(*end).x = M - 2;
    (*end).y = N - 1;

    maze[1][0] = maze[M - 2][N - 1] = Way;
    maze[1][1] = maze[M - 2][N - 2] = Way;

    paintMaze(maze);
}
int pass(MazeType maze, PosType seat) {
	int x = seat.x;
	int y = seat.y;
	if (x < 0 || y < 0 || x > M - 1 || y > N - 1) {
		return 0;
	}
	if (maze[x][y] != Way) {
		return 0;
	}
	return 1;
}
PosType nextPos(PosType seat, int di) {
	PosType tmp = seat;
	switch(di) {
		case East:
			tmp.y++;
			break;
		case South:
			tmp.x++;
			break;
		case West:
			tmp.y--;
			break;
		case North:
			tmp.x--;
			break;
	}
	return tmp;
}
void footPrint(MazeType maze, PosType seat) {
	markPrint(maze, seat, East);
}
void markPrint(MazeType maze, PosType seat, int mark) {
	int x = seat.x;
	int y = seat.y;
	maze[x][y] = mark;
	paintMaze(maze);
}
SElemType construct(int ord, PosType seat, int di) {
	SElemType e;
	e.ord = ord;
	e.seat = seat;
	e.di = di;
	return e;
}
int equals(PosType a, PosType b) {
	return (a.x == b.x && a.y == b.y) ? 1 : 0;
}
void paintMaze(MazeType maze) {
	int i, j;
	Wait(SleepTime);

	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			if(maze[i][j] == Wall) {                   // 外墙
                printf("*");
            } else if(maze[i][j] == Obstacle) {        // 迷宫内部的障碍
                printf("●");
            } else if(maze[i][j] == East) {            // 正在朝东探索
                printf("▷");
            } else if(maze[i][j] == South) {           // 正在朝南探索
                printf("▽");
            } else if(maze[i][j] == West) {            // 正在朝西探索
                printf("◁");
            } else if(maze[i][j] == North) {           // 正在朝北探索
                printf("△");
            } else if(maze[i][j] == Impasse) {         // 死胡同，即四个方向都探索过，但无法通过的位置
                printf("x");
            } else {                                   // 还未探索过的路径结点
                printf(" ");
            }
            if (j != 0 && j % (N - 1) == 0) {
            	printf("\n");
            }
		}
	}
	printf("\n");
}



OperandType EvaluateExpression(const char exp[]) {
	SElemType c;
	SqStack OPTR;
	SqStack OPND;

	OperatorType theta, x;
	OperandType a, b;

	int i = 0;

	initStack(&OPTR);
	push(&OPTR, '#');

	initStack(&OPND);
	c = exp[i++];

	while(c != '#' || getTop(OPTR) != '#') {
		if (!in(c, OP)) {
			push(&OPND, c);
		} else {
			switch(precede(getTop(OPTR), c)) {
				case '<':
					push(&OPTR, c);
					c = exp[i++];
					break;
				case '=':
					pop(&OPTR, &x);
					c = exp[i++];
					break;
				case '>':
					pop(&OPTR, &theta);
					pop(&OPND, &b);
					pop(&OPND, &a);
					push(&OPND, operate(a, theta, b));
					break;
			}
		}
	}
	return getTop(OPND);
}
int in(SElemType c, const char OP[]) {
	SElemType* e = strchr(OP, c);
	if (e == NULL)
	{
		return 0;
	} else {
		return 1;
	}
}
OperatorType precede(OperatorType o1, OperatorType o2) {
	int x, y;
	char* p1 = strchr(OP, o1);
	char* p2 = strchr(OP, o2);

	x = p1 - OP;
	y = p2 - OP;

	return PrecedeTable[x][y];
}
OperandType operate(OperandType a, OperatorType theta, OperandType b) {
	int x, y, z = CHAR_MAX - 48;
	x = a - '0';
	y = b - '0';

	switch(theta) {
		case '+':
            z = x + y;
            break;
        case '-':
            z = x - y;
            break;
        case '*':
            z = x * y;
            break;
        case '/':
            z = x / y;
            break;
	}
	return z + 48;
}



void hanoi(int n, char x, char y, char z) {
	if (n == 1) {
		move(x, 1, z);
	} else {
		hanoi(n - 1, x, z, y);
		move(x, n, z);
		hanoi(n - 1, y, x, z);
	}
}

void move(char x, int n, char z) {
	hanoiStep++;
	printf("第%2d步：将第 %d 个圆盘从 %c 移到 %c \n", hanoiStep, n, x, z);
	printHanoi(x, n, z);

}
void initHanoi(int n) {
	int i;
    int* towerX, * towerY, * towerZ;
    
    T.plates = (int**) malloc(3 * sizeof(int*));
    
    towerX = (int*) malloc(n * sizeof(int));
    towerY = (int*) malloc(n * sizeof(int));
    towerZ = (int*) malloc(n * sizeof(int));
    
    for(i = 0; i < n; ++i) {
        towerX[i] = n - i;
        towerY[i] = 0;
        towerZ[i] = 0;
    }
    
    T.plates[0] = towerX;
    T.plates[1] = towerY;
    T.plates[2] = towerZ;
    
    T.high[0] = n;
    T.high[1] = 0;
    T.high[2] = 0;
    
    // 汉诺塔移动的图形表示
    PrintGraph('\0', 0, '\0');
}
void printHanoi(char t1, int n, char t2) {
	int i, j;
    char** s;
    
    // 将n号盘子从t1中移除
    if(t1 == 'x') {
        T.plates[0][T.high[0] - 1] = 0;
        T.high[0]--;
    } else if(t1 == 'y') {
        T.plates[1][T.high[1] - 1] = 0;
        T.high[1]--;
    } else if(t1 == 'z') {
        T.plates[2][T.high[2] - 1] = 0;
        T.high[2]--;
    } else {
        // t1上的圆盘不需要移动
    }
    
    // 将n号盘子添加到t2中
    if(t2 == 'x') {
        T.plates[0][T.high[0]] = n;
        T.high[0]++;
    } else if(t2 == 'y') {
        T.plates[1][T.high[1]] = n;
        T.high[1]++;
    } else if(t2 == 'z') {
        T.plates[2][T.high[2]] = n;
        T.high[2]++;
    } else {
        // t2上的圆盘不需要移动
    }
    
    s = (char**) malloc((N + 2) * sizeof(char*));
    for(i = 0; i < N + 2; i++) {
        s[i] = (char*) malloc(N * sizeof(char));
        
        for(j = 0; j < i; j++) {
            if(i == N + 1) {
                s[i][j] = '-';  // 将最后一行初始化为托盘
            } else {
                s[i][j] = '*';
            }
        }
        
        if(i == N + 1) {
            s[i][j - 1] = '\0';
        } else {
            s[i][j] = '\0';
        }
    }
    
    for(i = N - 1; i >= 0; i--) {
        printf("%-*s | %-*s | %-*s\n", N, s[T.plates[0][i]], N, s[T.plates[1][i]], N, s[T.plates[2][i]]);
    }
    printf("%-*s + %-*s + %-*s\n", N, s[N + 1], N, s[N + 1], N, s[N + 1]);
    printf("%-*s %-*s %-*s\n", N + 2, "x", N + 2, "y", N + 2, "z");
    
    printf("\n");
}