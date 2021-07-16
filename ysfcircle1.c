#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef struct Node{
	int data;
	struct Node* next;
}Node;
typedef struct Circle{
	Node* pHead;
}Circle;
typedef Node* Position;
void Destroy(Circle list){
	while(list.pHead->next!=list.pHead){
		Node* p = list.pHead->next;
		list.pHead->next = p->next;
     	free(p);
	}
	free(list.pHead);
	list.pHead = NULL;
}
int IsEmpty(Circle list){
	if(list.pHead==NULL){
	   return 1;
	}else{
	   return 0;
	}
}
Circle Create(int n){
	Circle dest;
	int i;
	dest.pHead = (Node*)malloc(sizeof(Node));
	if(dest.pHead==NULL){
		return dest;
	}
	dest.pHead->data = 1;
	dest.pHead->next = dest.pHead;
    for(i=2;i<=n;i++){
    	Node* s = (Node*)malloc(sizeof(Node));
		if(s==NULL){
			Destroy(dest);
			return dest;
		}
		s->data = i;
		s->next = dest.pHead->next;
		dest.pHead->next = s;
		dest.pHead = s; 
	}
	return dest;
}
Position EndPosition(Circle list){
	return list.pHead;
}
Position BeginPosition(Circle list){
	return list.pHead->next;
}
Position NextPosition(Circle list,Position pos){
  return pos->next;
}
int Length(Circle list){
	Node* p = list.pHead;
	int icount;
	if(p!=NULL){
	icount = 1;
	p = p->next;
	}
	while(p!=EndPosition(list)&&p->next!=NULL){
	icount++;
	p = p->next;	
	}
	return icount;
}
void PrintList(Circle list){
	printf("(");
	Node* p =list.pHead;
	if(p!=NULL){
		printf("%d",p->next->data);
		p = p->next;
	}
	while(p!=EndPosition(list)&&p!=NULL){
		printf("->%d",p->next->data);
		p = p->next;
	}
	printf(")");
	printf("\n");
}
Circle Select(Circle list,int m){
	int n = m,i;
	Circle dest;
	int length = Length(list);
	Node* p = list.pHead;
	Node* s;
	if(m==1){
	printf("error");
	return list; 
	} 
	//第一个节点 
	while(--n){
		p = p->next;
	}
    s = p->next;
    p->next = s->next;
    dest.pHead = s;
    s->next = s;
    for(i=1;i<length;i++){
    	int count = m;
	    while(--count){
	    	p = p->next;
		}
		s = p->next;
		p->next = s->next;
		s->next = dest.pHead->next;
		dest.pHead->next = s;
		dest.pHead = s; 
	}
	list.pHead = NULL;
	return dest;
}
int main(){
	Circle list;
	Circle dest,dest1,dest2;
	int M,N,K,H;
	scanf("%d %d %d %d",&M,&N,&K,&H);
	list = Create(M);
	PrintList(list);
	dest = Select(list,N);
	PrintList(dest);
	dest1 = Select(dest,K);
	PrintList(dest1);
	dest2 = Select(dest1,H);
	PrintList(dest2);
//	printf("%d",Length(list));
    Destroy(list);
    Destroy(dest);
    Destroy(dest1);
    Destroy(dest2);
	return 0;
}
