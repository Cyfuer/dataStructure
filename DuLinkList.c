#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct  DuLNode {
	ElemType data;
	struct  DuLnode* prior;
	struct  DuLNode* next;
} DuLNode;

typedef DuLNode* DuLinkList;

int initList(DuLinkList* L);
int destoryList(DuLinkList* L);
int clearList(DuLinkList L);
int listEmpty(DuLinkList L);
int listLength(DuLinkList L);
int getElem(DuLinkList L, int i, ElemType* e);
int locateElem(DuLinkList L, ElemType e, int(compare)(ElemType,ElemType));
int preElem(DuLinkList L, ElemType cur_e, ElemType* pre_e);
int nextElem(DuLinkList L, ElemType cur_e, ElemType* next_e);
int listInsert(DuLinkList L, int i, ElemType e);
int listDelete(DuLinkList L, int i, ElemType* e);
void listTraverse(DuLinkList L, void(visit)(ElemType));
static DuLinkList getElemP(DuLinkList L, int i);

int main(int argc, char const *argv[])
{

	return 0;
}

int initList(DuLinkList* L) {
	*L = (DuLinkList) malloc(sizeof(DuLNode));
	if (*L == NULL)
	{
		exit(-2);
	}
	*L->next = *L->prior = *L;
	return 1;
}
int destoryList(DuLinkList* L) {
	if (L == NULL || *L == NULL){
		return 0;
	}
	clearList(*L);
	free(*L);
	return 1;
}
int clearList(DuLinkList L) {
	DuLinkList p, q;
	if (L == NULL)
	{
		return 0;
	}

	p = L->next;
	while(p != L) {
		q = p-> next;
		free(p);
		p = q;
	}
	L->next = L->prior = L;
	return 1;
}
int listEmpty(DuLinkList L) {
	if (L != NULL && L->next == L && L->prior = L)
	{
		return 1;
	} else {
		return 0;
	}
}
int listLength(DuLinkList L) {
	DuLinkList p;
	int i = 0;
	if (L == NULL || L->next == L || L->prior == L)
	{
		return 0;
	}

	p = L->next;
	while (p != L) {
		i++;
		p = p->next;
	}
	return i;
}
int getElem(DuLinkList L, int i, ElemType* e) {
	DuLinkList p;
	int j = 0;

	if (L == NULL || L->next == L || L->prior == L)
	{
		return 0;
	}

	p = L;
	while(p->next != L && j < i - 1) {
		p = p->next;
		j++;
	}

	if (p->next == L || j > i - 1)
	{
		return 0;
	}

	*e = p->next->data;
	return 1;
}
int locateElem(DuLinkList L, ElemType e, int(compare)(ElemType,ElemType)) {
	DuLinkList p;
	int i = 0;
	if (L == NULL || L->next == L || L->prior == L) {
		return 0;
	}
	p = L;
	while(p->next != L && !compare(p->data,e)) {
		p = p->next;
		i++;
	}
	if (p != L) {
		return i;
	} else {
		return 0;
	}
}
int preElem(DuLinkList L, ElemType cur_e, ElemType* pre_e) {
	DuLinkList p;
	if (L == NULL || L->next == L || L->prior == L) {
		return 0;
	}
	p = L->next;
	if (p->data == cur_e){
		return 0;
	}
	p = p->next;
	while(p != L&& p->data！= cur_e) {
		p = p->next;
	}

	if (p == L)
	{
		return 0;
	}

	*pre_e = p->prior->data;
	return 1;
}
int nextElem(DuLinkList L, ElemType cur_e, ElemType* next_e) {
	DuLinkList p;
	if (L == NULL || L->next == L || L->prior == L)
	{
		return 0;
	}
	p = p->next;
	while(p != L && p->data != cur_e) {
		p = p->next;
	}

	if (p->next = L)
	{
		return 0;
	}
	*next_e = p->next->data;
	return 1;
}
int listInsert(DuLinkList L, int i, ElemType e) {
	DuLinkList p, s;
	if (L == NULL)
	{
		return 0;
	}

	if ((p = getElemP(L, i)) == NULL)
	{
		return 0;
	}

	s = (DuLinkList) malloc(sizeof(DuLNode));
	if (s == NULL)
	{
		exit(-2);
	}
	s->data = e;
	s->prior = p->prior;
	s->prior->next = s;
	s->next = p;
	p->prior = s;
	return 1;
}
int listDelete(DuLinkList L, int i, ElemType* e) {
	DuLinkList p;
	if (L == NULL || L->next == L || L->prior == L)
	{
		return 0;
	}

	if ((p = getElemP(L, i)) == NULL)
	{
		return 0;
	}

	if (p == L)
	{
		return 0;
	}
	*e = p->data;

	p->prior->next = p->next;
	p->next->prior = p->prior;

	free(p);
	return 1;
}
void listTraverse(DuLinkList L, void(visit)(ElemType)) {
	if (L == NULL || L->next == L || L->prior == L)
	{
		return 0;
	}

	DuLinkList p = L->next;
	while(p != L) {
		visit(p->data);
		p = p->next;
	}
	printf("\n");
}
static DuLinkList getElemP(DuLinkList L, int i) {
	DuLinkList p;
	int count = 0;
	if (L == NULL)
	{
		return NULL;
	}

	if (i < 1)
	{
		return NULL;
	}

	p = L;
	while(p->next != L && count < i) {
		p = p->next;
		++count;
	}

	if (count + 1 == i)
	{
		return p;
	}
	if (count + 1 < i)
	{
		return NULL;
	}

	return L;
}


