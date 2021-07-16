#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
typedef int typeElem;
typedef struct Node {
	typeElem data;
	struct Node* next;
}Node;

typedef struct List {
	Node* pHead;
	Node* pTail;
}List;
typedef Node* Position;
List Create();
void Clear(List* pList);
void Destroy(List* pList);
List Copy(List list);
int IsEmpty(List list);
int Length(List list);
Position BeginPosition(List list);
Position EndPosition(List list);
Position NextPosition(List list, Position pos);
Position LocatePosition(List list, int i);
Position LocateElem(List list, typeElem e);
typeElem GetElem(List list, Position pos);
void SetElem(List list, Position pos, typeElem e);
int InsertBefore(List* pList, Position pos, typeElem e);
void Delete(List* pList, Position pos);

List Create() {
	List list;
	list.pHead = list.pTail = (Node*)malloc(sizeof(Node));
	if (list.pHead==NULL)
	{
		list.pHead = list.pTail = NULL;
	}
	return list;
}
void Clear(List* pList) {
	Node* p = pList->pHead->next;
	while (p != NULL) {
		Node* q = p;
		p = p->next;
		free(q);
	}
	pList->pHead->next = NULL;
	pList->pTail = pList->pTail;
}
void Destroy(List* pList) {
	Clear(pList);
	Node* p = pList->pHead;
	free(p);
	pList->pHead = pList->pTail = NULL;
}
List Copy(List list) {
	List dest = Create();
	if (dest.pHead->next==NULL)
	{
		return dest;
	}
	Node* p = list.pHead->next;
	while (p != NULL) {
		Node* s = (Node*)malloc(sizeof(Node));
		if (s==NULL)
		{
			Destroy(&dest);
			return dest;
		}
		s->data = p->data;
		s->next = dest.pTail->next;
		dest.pTail->next = s;
		dest.pTail = s;
		p = p->next;
	}
	return dest;
}
int IsEmpty(List list) {
	return (list.pHead->next == NULL);
}
int Length(List list) {
	int icount = 0;
	Node* p = list.pHead->next;
	while (p != NULL)
	{
		icount++;
		p = p->next;
	}
	return icount;
}
Position BeginPosition(List list) {
	return list.pHead;
}
Position EndPosition(List list) {
	return list.pTail;
}
Position NextPosition(List list, Position pos) {
	return pos->next;
}
Position LocatePosition(List list, int i) {
	Node* p = list.pHead;
	while (--i > 0 && p->next != NULL) {
		p = p->next;
	}
	return p;
}
Position LocateElem(List list, typeElem e) {
	Node* p = list.pHead;
	while (p->next != NULL&&e != p->next->data) {
		p = p->next;
	}
	return p;
}
typeElem GetElem(List list, Position pos) {
	assert(pos != EndPosition(list));
	return pos->next->data;
}
void SetElem(List list, Position pos, typeElem e) {
	assert(pos != EndPosition(list));
	pos->next->data = e;
}
int InsertBefore(List* pList, Position pos, typeElem e) {
	Node* p = (Node*)malloc(sizeof(Node));
	if (p==NULL)
	{
		return 0;
	}
	p->data = e;
	p->next = pos->next;
	pos->next = p;
	if (pos==EndPosition(*pList))
	{
		pList->pTail = p;
	}
	return 1;
}
void Delete(List* pList, Position pos) {
	assert(pos != EndPosition(*pList));
	Node* q = pos->next;
	pos->next = q->next;
	free(q);
	if (q == pList->pTail) {
		pList->pTail = pos;
	}
}
void PrintList(List list) {
	Node* p = list.pHead;
	printf("(");
	if (p!=EndPosition(list))
	{
		printf("%d", p->next->data);
		p = p->next;
	}
	while (p!=EndPosition(list))
	{
		printf("->%d", p->next->data);
		p = p->next;
	}
	printf(")");
	printf("\n");
}
List reverse(List list){
	List dest = Create();
	Node* p = list.pHead;
	Node* q = dest.pHead;
	if(p!=EndPosition(list)){
		Node* s = p->next;
		p->next = s->next;
		s->next = q->next;
		q->next = s;
		dest.pTail = s;
		if(s==EndPosition(list)){
			list.pTail = list.pHead;
		}
	}
	while(p!=EndPosition(list)){
		Node* s = p->next ;
		p->next = s->next;
		s->next = q->next;
		q->next = s;
		if(s==EndPosition(list)){
			list.pTail = list.pHead;
		}
	}
	return dest;
}

int main() {
	int i,x;
	List zlist, flist,dest,dest1;
	zlist = Create();
	flist = Create();
	while (1)
	{
		scanf("%d", &x);
		if (x==0)
		{
			break;
		}
		Position pos,pos1;
		pos = zlist.pHead;
		pos1 = flist.pHead;
		if (x>0)
		{
			while (pos->next != NULL && x > pos->next->data)
			{
				pos = pos->next;
			}

			InsertBefore(&zlist, pos, x);
		}
		else
		{
			while (pos1->next!=NULL&&x>pos1->next->data)
			{
				pos1 = pos1->next;
			}
			InsertBefore(&flist, pos1, x);
		}
	}
	PrintList(zlist);
	PrintList(flist);
	dest = reverse(zlist);
	dest1 = reverse(flist);
	PrintList(dest);
	PrintList(dest1);
	Destroy(&dest);
	Destroy(&dest1);
	Destroy(&zlist);
	Destroy(&flist);
	return 0;
}
