#include <stdio.h>
#include <stdlib.h>

typedef int QElemType;

typedef struct QNode {
	QElemType data;
	struct  QNode* next;
} QNode, *QueuePtr;

typedef struct {
	QueuePtr front;
	QueuePtr rear;
} LinkQueue;

int initQueue(LinkQueue* Q);
int destoryQueue(LinkQueue* Q);
int clearQueue(LinkQueue* Q);
int queueEmpt(LinkQueue Q);
int queueLength(LinkQueue Q);
int getHead(LinkQueue Q, QElemType* e);
int enterQueue(LinkQueue* Q, QElemType e);
int deleteQueue(LinkQueue* Q, QElemType* e);
int queueTraverse(LinkQueue Q, void(Visit)(QElemType));


int initQueue(LinkQueue* Q) {
	if (Q == NULL) {
		return 0;
	}
	(*Q).front = (*Q).rear = (QueuePtr) malloc(sizeof(QNode));
	if (!(*Q).front) {
		exit(-2);
	}
	(*Q).front->next = NULL;
	return 1;
}
int destoryQueue(LinkQueue* Q) {
	if (Q == NULL) {
		return 1;
	}
	while((*Q).front) {
		(*Q).rear = (*Q).front->next;
		free((*Q).front);
		(*Q).front = (*Q).rear;
	}
	return 1;
}
int clearQueue(LinkQueue* Q) {
	if (Q == NULL)  {
		return 0;
	}
	(*Q).rear = (*Q).front->next;
	while((*Q).rear) {
		(*Q).front->next = (*Q).rear->next;
		free((*Q).rear);
		(*Q).rear = (*Q).front->next;
	}
	(*Q).rear = (*Q).front;
	return 1;
}
int queueEmpt(LinkQueue Q) {
	return Q.front == Q.rear ? 1 : 0;
}
int queueLength(LinkQueue Q) {
	int count = 0;
	QueuePtr p = Q.front;
	while(p != Q.rear) {
		count++;
		p = p->next;
	}
	return count;
}
int getHead(LinkQueue Q, QElemType* e) {
	QueuePtr p;
	if (Q.front == NULL || Q.front == Q.rear)
	{
		return 0;
	}
	p = Q.front->next;
	*e = p->data;
	return 1;
}
int enterQueue(LinkQueue* Q, QElemType e) {
	QueuePtr p;
	if (Q == NULL || (*Q).front == NULL)
	{
		return 0;
	}
	p = (QueuePtr) malloc(sizeof(QNode));
	if (!p) {
		exit(-2);
	}

	p->data = e;
	p->next = NULL;

	(*Q).rear->next = p;
	(*Q).rear = p;
	return 1;

}
int deleteQueue(LinkQueue* Q, QElemType* e) {
	QueuePtr p;
	if (Q == NULL || (*Q).front == NULL || (*Q).front == (*Q).rear)
	{
		return 0;
	}

	p = (*Q).front->next;
	*e = p->data;
	(*Q).front->next = p->next;
	if ((*Q).rear == p) {
		(*Q).rear = (*Q).front;
	}
	free(p);

	return 1;
}
int queueTraverse(LinkQueue Q, void(Visit)(QElemType)) {
	QueuePtr p;
	if (Q.front == NULL) {
		return 0;
	}

	p = Q.front->next;

	while(p != NULL) {
		Visit(p->data);
		p = p->next;
	}
	printf("\n");
	return 1;
}
