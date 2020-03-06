#include <stdio.h>
#include <stdlib.h>

#define MAXQSIZE 1000

typedef int QElemType;

typedef struct  {
	QElemType* base;
	int front;
	int rear;
} SqQueue;

int initQueue(SqQueue* Q);
int destoryQueue(SqQueue* Q);
int clearQueue(SqQueue* Q);
int queueEmpt(SqQueue Q);
int queueLength(SqQueue Q);
int getHead(SqQueue Q, QElemType* e);
int enterQueue(SqQueue* Q, QElemType e);
int deleteQueue(SqQueue* Q, QElemType* e);
int queueTraverse(SqQueue Q, void(Visit)(QElemType));


int initQueue(SqQueue* Q) {
	if (Q == NULL) {
		return 0;
	}
	(*Q).base = (QElemType*) malloc(MAXQSIZE * sizeof(QElemType));
	if (!(*Q).base) {
		exit(-2);
	}

	(*Q).front = (*Q).rear = 0;
	return 1;
}
int destoryQueue(SqQueue* Q) {
	if (Q == NULL) {
		return 1;
	}
	if ((*Q).base) {
		free((*Q).base);
	}
	(*Q).base = NULL;
	(*Q).front = (*Q).rear = 0;
	return 1;
}
int clearQueue(SqQueue* Q) {
	if (Q == NULL || (*Q).base == NULL) {
		return 0;
	}
	(*Q).front = (*Q).rear = 0;
	return 1;
}
int queueEmpt(SqQueue Q) {
	return Q.front == Q.rear ? 1 : 0;
}
int queueLength(SqQueue Q) {
	if (Q.base == NULL) {
		return 0;
	}
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}
int getHead(SqQueue Q, QElemType* e) {
	if (Q.base == NULL || Q.front == Q.rear) {
		return 0;
	}
	*e = Q.base[Q.front];
	return 1;
}
int enterQueue(SqQueue* Q, QElemType e) {
	if (Q == NULL || (*Q).base == NULL) {
		return 0;
	}
	if ((*Q).rear + 1 % MAXQSIZE == (*Q).front) {
		return 0;
	}
	(*Q).base[(*Q).rear]  = e;
	(*Q).rear = ((*Q).rear + 1) % MAXQSIZE;
	return 1;
}
int deleteQueue(SqQueue* Q, QElemType* e) {
	if (Q == NULL || (*Q).base == NULL) {
		return 0;
	}
	if ((*Q).front == (*Q).rear) {
		return 0;
	}
	*e = (*Q).base[(*Q).front];
	(*Q).front = ((*Q).front + 1) % MAXQSIZE;
	return 1;
}
int queueTraverse(SqQueue Q, void(Visit)(QElemType)) {
	int i;
	if (Q.base == NULL) {
		return 0;
	}
	for (i = Q.front; i != Q.rear; i = (i + 1) % MAXQSIZE) {
		Visit(Q.base[i]);
	}
	printf("\n");
	return 1;
}
