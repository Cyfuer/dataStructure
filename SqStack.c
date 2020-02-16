#include <stdio.h>
#include <stdlib.h>

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
int stackTraverse(SqStack s, void(visit)(SElemType));
void printElem(SElemType e);

// 进制转换：将指定的非负十进制整数，转换为八进制后输出
void conversion(int i);

int main(int argc, char const *argv[])
{
	// SqStack s;
	// initStack(&s);
	conversion(842);

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