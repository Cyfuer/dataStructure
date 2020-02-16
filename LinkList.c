#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OVERFLOW -2

typedef int ElemType;
typedef struct LNode{
	ElemType data;
	struct  LNode* next;
} LNode;

typedef LNode* LinkList;

int InitList(LinkList* L);
int DestroyList(LinkList* L);
int ClearList(LinkList L);
int ListEmpty(LinkList L);
int ListLength(LinkList L);
int GetElem(LinkList L, int i, ElemType* e);
int LocateElem(LinkList L, ElemType e, int(Compare(ElemType,ElemType)));
int PreElem(LinkList L, ElemType cur_e, ElemType* pre_e);
int NextElem(LinkList L, ElemType cur_e, ElemType* next_e);
int ListInsert(LinkList L, int i, ElemType e);
int ListDelete(LinkList L, int i, ElemType* e);
void ListTraverse(LinkList L, void(Visit)(ElemType));
int CreateList_Head(LinkList* L, int n, char* path);
int CreateList_Tail(LinkList* L, int n, char* path);

// 把A和B合并为C；
void MergeList(LinkList* La, LinkList* Lb, LinkList* Lc);


int InitList(LinkList* L) {
	(*L) = (LinkList) malloc(sizeof(LNode));
	if (*L == NULL) {
		exit(OVERFLOW);
	}

	(*L)->next = NULL;
	return 1;
}
int DestroyList(LinkList* L) {
	LinkList p;
	if (L == NULL || *L == NULL) {
		return 0;
	}

	p = *L;
	while(p != NULL) {
		p = (*L)->next;
		free(*L);
		(*L) = p;
	}
	return 1;
}
int ClearList(LinkList L) {
	LinkList pre, p;
	if (L == NULL) {
		return 0;
	}
	p = L->next;
	while(p != NULL) {
		pre = p;
		p = p->next;
		free(pre);
	}
	L->next = NULL;
	return 0;
}
int ListEmpty(LinkList L) {
	return (L != NULL && L->next == NULL) ? 1 : 0;
}
int ListLength(LinkList L) {
	if (L == NULL || L->next == NULL) {
		return 0;
	}

	LinkList p = L->next;
	int i = 0;
	while(p != NULL) {
		i++;
		p = p->next;
	}
	return i;
}
int GetElem(LinkList L, int i, ElemType* e) {
	if (L == NULL || L->next == NULL) {
		return 0;
	}

	LinkList p = L->next;
	int j = 0;
	while(p != NULL && j < i - 1) {
		j++;
		p = p->next;
	}

	if (p->next == NULL || j > i - 1) {
		return 0;
	}
	*e = p->next->data;

	return i;

}
int LocateElem(LinkList L, ElemType e, int(Compare(ElemType,ElemType))) {
	if (L == NULL || L->next == NULL) {
		return 0;
	}

	LinkList p = L->next;
	int i = 0;

	while(p != NULL && !Compare(p->data, e)) {
		i++;
		p = p->next;
	}
	if (p != NULL) {
		return i;
	} else {
		return 0;
	}
}
int PreElem(LinkList L, ElemType cur_e, ElemType* pre_e) {
	LinkList pre, next;
	if (L == NULL || L->next == NULL) {
		return 0;
	}
	pre = L->next;
	if (pre->data == cur_e)
	{
		return 0;
	}
	next = pre->next;
	while(next != NULL && next->data != cur_e) {
		pre = next;
		next = next->next;
	}
	if (next == NULL)
	{
		return 0;
	}
	*pre_e = pre->data;
	return 1;
}
int NextElem(LinkList L, ElemType cur_e, ElemType* next_e) {
	LinkList pre;
	if (L == NULL || L->next == NULL) {
		return 0;
	}
	pre = L->next;
	while(pre != NULL && pre->data != cur_e) {
		pre = pre->next;
	}

	if (pre->next == NULL)
	{
		return 0;
	}
	*next_e = pre->next->data;
	return 1;

}
int ListInsert(LinkList L, int i, ElemType e) {
	if (L == NULL || L->next == NULL) {
		return 0;
	}

	LinkList p = L->next;
	int j = 0;
	while(p != NULL && j < i - 1) {
		p = p->next;
		j++;
	}

	if (p == NULL || j > i - 1)
	{
		return 0;
	}

	LinkList new = (LinkList)malloc(sizeof(LNode));
	if (new == NULL)
	{
		exit(OVERFLOW);
	}
	new->next = p->next;
	new->data = e;
	p->next = new;
	return 1;
}
int ListDelete(LinkList L, int i, ElemType* e) {
	if (L == NULL || L->next == NULL) {
		return 0;
	}

	LinkList p = L->next;
	int j = 0;
	while(p != NULL && j < i - 1) {
		p = p->next;
		j++;
	}

	if (p == NULL || j > i - 1)
	{
		return 0;
	}

	LinkList q = p->next;
	p->next = q->next;
	*e = q-data;
	free(q);
	return 1;
}
void ListTraverse(LinkList L, void(Visit)(ElemType)) {
	if (L == NULL || L->next == NULL) {
		return 0;
	}

	LinkList p = L->next;
	while(p !+ NULL) {
		Visit(p);
		p = p->next;
	}
}
int CreateList_Head(LinkList* L, int n, char* path) {

}
int CreateList_Tail(LinkList* L, int n, char* path) {

}

void MergeList(LinkList* La, LinkList* Lb, LinkList* Lc) {
	LinkList pa, pb, pc;

	pa = (*La)->next;
	pb = (*Lb)->next;
	pc = *Lc = *La;

	while(pa && pb) {
		if (pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		} else {
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;
	free(*Lb);
}
