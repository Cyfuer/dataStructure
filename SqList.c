#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef int ElemType;

typedef struct {
	ElemType *elem;
	int length;
	int listsize;
} SqList;

int InitList(SqList* L);
int DestroyList(SqList* L);
int ClearList(SqList* L);
int ListEmpty(SqList L);
int ListLength(SqList L);
int GetElem(SqList L, int i, ElemType* e);
int LocateElem(SqList L, ElemType e, int(compare(ElemType,ElemType)));
int PreElem(SqList L, ElemType cur_e, ElemType *pre_e);
int NextElem(SqList L, ElemType cur_e, ElemType *next_e);
int ListInsert(SqList* L, int i, ElemType e);
int ListDelete(SqList* L, int i, ElemType *e);
void ListTraverse(SqList L, void(Visit)(ElemType));

// 求两个数组的并集
void Union(SqList* La, SqList Lb);
int equal(ElemType e1, ElemType e2);
void printList(ElemType e);

// 合并非递减排列
void mergerList1(SqList La, SqList Lb, SqList *Lc);
void mergerList2(SqList La, SqList Lb, SqList *Lc);



int main(int argc, char const *argv[])
{
	SqList La, Lb, Lc;
	InitList(&La);
	InitList(&Lb);
	InitList(&Lc);

	ListInsert(&La, 1, 1);
	ListInsert(&La, 2, 3);
	ListInsert(&La, 3, 4);

	ListInsert(&Lb, 1, 2);
	ListInsert(&Lb, 2, 5);
	ListInsert(&Lb, 3, 7);

	// Union(&La, Lb);
	// ListTraverse(La, printList);
	mergerList2(La, Lb, &Lc);
	ListTraverse(Lc, printList);



	return 0;
}

int InitList(SqList* L) {
	(*L).elem = (ElemType*) malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if ((*L).elem == NULL) {
		exit(-2);
	}
	(*L).length = 0;
	(*L).listsize = LIST_INIT_SIZE;
	return 1;
}
int DestroyList(SqList* L) {
	if (L == NULL || (*L).elem == NULL) {
		return 0;
	}
	free((*L).elem);
	(*L).elem = NULL;
	(*L).length = 0;
	(*L).listsize = 0;
	return 1;
}
int ClearList(SqList* L) {
	if (L == NULL || (*L).elem == NULL) {
		return 0;
	}
	(*L).length = 0;
	return 1;
}
int ListEmpty(SqList L) {
	return L.length == 0 ? 1 : 0;
}
int ListLength(SqList L) {
	return L.length;
}
int GetElem(SqList L, int i, ElemType* e) {
	if (i < 1 || i > L.length) {
		return 0;
	}
	*e = L.elem[i - 1];
	return 1;
}
int LocateElem(SqList L, ElemType e, int(compare(ElemType,ElemType))) {
	if (L.elem == NULL){
		return 0;
	}
	int i = 1;
	ElemType *p = L.elem;
	while (i <= L.length && !compare(*p++, e)) {
		++i;
	}
	if (i <= L.length){
		return i;
	} else {
		return 0;
	}
}
int PreElem(SqList L, ElemType cur_e, ElemType *pre_e) {
	if (L.elem == NULL || L.length < 2) {
		return 0;
	}

	int i = 0;
	while(i < L.length && L.elem[i] != cur_e) {
		i++;
	}
	if (i == 0 || i >= L.length) {
		return 0;
	}
	*pre_e = L.elem[i-1];
	return 1;
}
int NextElem(SqList L, ElemType cur_e, ElemType *next_e) {
	if (L.elem == NULL || L.length < 2) {
		return 0;
	}

	int i = 0;
	while(i < L.length && L.elem[i] != cur_e) {
		i++;
	}

	if (i >= L.length - 1) {
		return 0;
	}
	*next_e = L.elem[i + 1];
	return 1;
}
int ListInsert(SqList* L, int i, ElemType e) {
	if (L == NULL || (*L).elem == NULL || i < 1 || i > (*L).length + 1) {
		return 0;
	}

	
	if ((*L).length > (*L).listsize) {
		ElemType *newbase = (ElemType *)realloc((*L).elem, ((*L).listsize + LISTINCREMENT)*sizeof(ElemType));
		if (!newbase) {
			exit(-2);
		}
		(*L).listsize += LISTINCREMENT;
	}

	ElemType *q = &(*L).elem[i - 1];
	for (ElemType *p = &(*L).elem[(*L).length - 1]; p >= q; p--) {
		*(p + 1) = *p;
	}
	*q = e;
	(*L).length++;
	return 1;
	
}
int ListDelete(SqList* L, int i, ElemType *e) {
	if (L == NULL || (*L).elem == NULL || i < 0 || i > (*L).length) {
		return 0;
	}
	
	for (int j = i - 1; j < (*L).length; ++i) {
		(*L).elem[j] = (*L).elem[j + 1];
	}
	(*L).length --;
	return 1;
}
void ListTraverse(SqList L, void(Visit)(ElemType)) {
	for (int i = 0; i < L.length; ++i)
	{
		Visit(L.elem[i]);
	}
	printf("\n");
}


int equal(ElemType e1, ElemType e2) {
	return e1 == e2 ? 1 : 0;
}

void printList(ElemType e) {
	printf("%d \n", e);
}


void Union(SqList* La, SqList Lb) {
	int La_len, Lb_len;
	ElemType e;

	La_len = ListLength(*La);
	Lb_len = ListLength(Lb);

	for (int i = 0; i < Lb_len; ++i) {
		GetElem(Lb, i+1, &e);
		if (!LocateElem(*La, e, equal)) {
			ListInsert(La, ++La_len, e);
		}
	}
}

void mergerList1(SqList La, SqList Lb, SqList *Lc) {

	int La_len = ListLength(La), Lb_len = ListLength(Lb);
	int La_idx = 0, Lb_idx = 0, Lc_idx = 0;
	ElemType a, b;
	while (La_idx < La_len && Lb_idx < Lb_len) {
		GetElem(La, La_idx+1, &a);
		GetElem(Lb, Lb_idx+1, &b);
		if (a <= b) {
			ListInsert(Lc, Lc_idx++ + 1, a);
			La_idx++;
		} else {
			ListInsert(Lc, Lc_idx++ + 1, b);
			Lb_idx++;
		}
	}
	while(La_idx < La_len) {
		GetElem(La, La_idx++ + 1, &a);
		ListInsert(Lc, Lc_idx++ + 1, a);
	}
	while(Lb_idx < Lb_len) {
		GetElem(Lb, Lb_idx++ + 1, &b);
		ListInsert(Lc, Lc_idx++ + 1, b);
	}
}

void mergerList2(SqList La, SqList Lb, SqList *Lc) {
	int len = La.length + Lb.length;
	// ElemType *newbase = (ElemType *)realloc((*Lc).elem, len * sizeof(ElemType));
	// if (!newbase)
	// {
	// 	exit(-2);
	// }
	// (*Lc).listsize = len;
	// (*Lc).elem = newbase;

	ElemType *a = La.elem;
	ElemType *b = Lb.elem;
	ElemType *c = (*Lc).elem;

	ElemType *a_last = La.elem + La.length - 1;
	ElemType *b_last = Lb.elem + Lb.length - 1;

	while (a <= a_last && b <= b_last) {
		if (*a <= *b) {
			*c++ = *a++;
		} else {
			*c++ = *b++;
		}
		(*Lc).length++;
	}
	while(a <= a_last) {
		*c++ = *a++;
		(*Lc).length++;
	}
	while(b <= b_last) {
		*c++ = *b++;
		(*Lc).length++;
	}
}