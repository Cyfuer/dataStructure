#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 1000

typedef int ElemType;

typedef struct SlinkNode {
	ElemType data;
	int next;
} SLinkList[MAXSIZE];

void initSpace(SLinkList s);
int mallocSpace(SLinkList s);
void freeSpace(SLinkList s, int k);

int initList(SLinkList s, int* S);
int destoryList(SLinkList s, int* S);
int clearList(SLinkList s, int S);
int listEmpty(SLinkList s, int S);
int listLength(SLinkList s, int S);
int getElem(SLinkList s, int S, int i, ElemType* e);
int locateElem(SLinkList s, int S, ElemType e, int(Compare)(ElemType, ElemType));
int preElem(SLinkList s, int S, ElemType cur_e, ElemType* pre_e);
int nextElem(SLinkList s, int S, ElemType cur_e, ElemType* next_e);
int listInsert(SLinkList s, int S, int i, ElemType e);
int listDelete(SLinkList s, int S, int i, ElemType* e);
void listTraverse(SLinkList s, int S, void(visit)(ElemType));
void printList(SLinkList s, int S);

// 对集合A和集合B进行(A-B)∪(B-A)计算，计算结果存入静态链表S
void difference(SLinkList s, int* S, char* path);
void PrintElem(ElemType e);

int main(int argc, char const *argv[])
{
	SLinkList s;
	int S;

	difference(s, &S, NULL);
	printf("S = (A-B)∪(B-A) = ");
	listTraverse(s, S, PrintElem);
	return 0;
}

void initSpace(SLinkList s) {
	for (int i = 0; i < MAXSIZE - 1; ++i) {
		s[i].next = i + 1;
	}
	s[MAXSIZE - 1].next = 0;
}
int mallocSpace(SLinkList s) {
	int i = s[0].next;
	if (i != 0) {
		s[0].next = s[i].next;
	}
	return i;
}
void freeSpace(SLinkList s, int k) {
	s[k].next = s[0].next;
	s[0].next = k;
}

int initList(SLinkList s, int* S) {
	initSpace(s);
	int index = mallocSpace(s);
	if (index == 0)
	{
		return 0;
	}
	s[index].next = 0;
	*S = index;
	return 1;
}
int destoryList(SLinkList s, int* S) {
	int cur;
	if (S == NULL || *S == 0)
	{
		return 0;
	}
	while(*S != 0) {
		cur = s[*S].next;
		freeSpace(s, *S);
		*S = cur;
	}
	return 1;
}
int clearList(SLinkList s, int S) {
	int p, next;
	if (S == 0)
	{
		return 0;
	}
	p = s[S].next;
	while(p != 0) {
		next = s[p].next;
		freeSpace(s, p);
		p = next;
	}
	s[S].next = 0;
	return 1;
}
int listEmpty(SLinkList s, int S) {
	return (S != 0 && s[S].next == 0) ? 1 : 0;
}
int listLength(SLinkList s, int S) {
	int count = 0;
	if (S == 0 || s[S].next == 0)
	{
		return 0;
	}
	S = s[S].next;
	while(S != 0) {
		count++;
		S = s[S].next;
	}
	return count;
}
int getElem(SLinkList s, int S, int i, ElemType* e) {
	int count = 0;
	if (S == 0 || s[S].next == 0)
	{
		return 0;
	}
	S = s[S].next;
	while (S != 0 && count < i - 1) {
		S = s[S].next;
	}
	*e = s[S].data;
	return 1;
}
int locateElem(SLinkList s, int S, ElemType e, int(Compare)(ElemType, ElemType)) {
	int count = 0;
	if (S == 0 || s[S].next == 0)
	{
		return 0;
	}
	S = s[S].next;
	while (S != 0 && !Compare(s[S].data, e)) {
		S = s[S].next;
		count++;
	}
	if (S != 0)
	{
		return count;
	} else {
		return 0;
	}
}
int preElem(SLinkList s, int S, ElemType cur_e, ElemType* pre_e) {

	ElemType pre;
	int count = 0;

	if (S == 0 || s[S].next == 0)
	{
		return 0;
	}
	S = s[S].next;
	while (S != 0 && s[S].data != cur_e) {
		pre = s[S].data;
		S = s[S].next;
		count++;
	}
	if (S != 0 && count != 0)
	{
		*pre_e = pre;
		return 1;
	} else {
		return 0;
	}
}
int nextElem(SLinkList s, int S, ElemType cur_e, ElemType* next_e) {
	if (S == 0 || s[S].next == 0)
	{
		return 0;
	}
	S = s[S].next;
	while (S != 0 && s[S].data != cur_e) {
		S = s[S].next;

	}
	if (S != 0 && s[S].next != 0)
	{
		S = s[S].next;
		*next_e = s[S].data;
		return 1;
	} else {
		return 0;
	}
}
int listInsert(SLinkList s, int S, int i, ElemType e) {
	if (S == 0)
	{
		return 0;
	}
	int j = 0;
	while(S != 0 && j < i - 1) {
		S = s[S].next;
		j++;
	}
	if (S == 0 || j > i - 1)
	{
		return 0;
	}
	int new = mallocSpace(s);
	s[new].data = e;
	s[new].next = s[S].next;
	s[S].next = new;

	return 1;
}
int listDelete(SLinkList s, int S, int i, ElemType* e) {
	if (S == 0)
	{
		return 0;
	}
	int j = 0;
	while(S != 0 && j < i - 1) {
		S = s[S].next;
		j++;
	}
	if (S == 0 || j > i - 1)
	{
		return 0;
	}
	int q = s[S].next;
	s[S].next = s[q].next;
	*e = s[q].data;
	freeSpace(s, q);
	return 1;
}

void listTraverse(SLinkList s, int S, void(visit)(ElemType)) {
	if (S == 0 || s[S].next == 0)
	{
		return;
	}
	S = s[S].next;
	while(S != 0) {
		visit(s[S].data);
		S = s[S].next;
	}
	printf("\n");
}
void printList(SLinkList s, int S) {
	while(S != 0) {
		printf("%6d | %6d | %6d\n", S, s[S].data, s[S].next);
	}
}

void difference(SLinkList s, int* S, char* path) {
	int m, n;
	int j;
	int R;
	int i, k, p;
	int b;
	FILE* fp;
	int readFromConsole;

	readFromConsole = path == NULL || strcmp(path, "") == 0;

	initSpace(s);
	*S = mallocSpace(s);
	R = *S;

	if (readFromConsole) {
		printf("请输入集合A的元素个数：");
        scanf("%d", &m);
        printf("请输入集合B的元素个数：");
        scanf("%d", &n);
	} else {
		fp = fopen(path, "r");
		if (fp == NULL)
		{
			exit(-2);
		}
		fscanf(fp, "%d%d", &m, &n);
	}
	if(readFromConsole) {
        printf("请输入 %d 个元素存入集合A：", m);
    }

    for (j = 1; j <= m; ++j)
    {
    	i = mallocSpace(s);
    	if (readFromConsole) {
    		scanf("%d", &s[i].data);
    	} else {
    		fscanf(fp, "%d", &s[i].data);
    	}
    	s[R].next = i;
    	R = i;
    }
    s[R].next = 0;

    if(readFromConsole) {
        printf("请输入 %d 个元素存入集合B：", n);
    }

    for (j = 1; j <= n; ++j)
    {
    	if (readFromConsole) {
    		scanf("%d", &b);
    	} else {
    		fscanf(fp, "%d", &b);
    	}
    	p = *S;
    	k = s[*S].next;
    	while(k != s[R].next && s[k].data != b) {
    		p = k;
    		k = s[k].next;
    	}
    	if (k == s[R].next)
    	{
    		i = mallocSpace(s);
    		s[i].data = b;
    		s[i].next = s[R].next;
    		s[R].next = i;
    	} else {
    		s[p].next = s[k].next;
    		freeSpace(s, k);
    		if (R == k) {
    			R = p;
    		}
    	}
    }

    if (!readFromConsole)
    {
    	fclose(fp);
    }

}

void PrintElem(ElemType e) {
    printf("%d ", e);
}
