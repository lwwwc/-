#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
typedef struct Node {
	int data;
	struct Node* pre;
	struct Node* next; 
}Node;

typedef struct UBN{
	int digit;
	Node* pHead;
	Node* pTail;
}UBN;

Node* NewNode(){
	Node* p = (Node*)malloc(sizeof(Node));
	if(p==NULL){
		printf("mem full");
	}
	return p;
}
void InitUBN(UBN* ubn){
	ubn->pHead = ubn->pTail = NewNode();
	ubn->digit = 0;
	ubn->pHead->data = 0;
	ubn->pHead->next = ubn->pHead->pre = NULL; 
} 

void DestroyUBN(UBN* ubn){
	Node* p = ubn->pHead;
	while(p->next!=NULL){
		Node* q = p->next;
		p->next = q->next;
		free(q); 
	}
	free(p);
	ubn->pHead = ubn->pTail = NULL;
	ubn->digit = 0; 
}
void AppendDigit(UBN* ubn,int digit){
	if(ubn->digit==1&ubn->pTail->data==0){
		ubn->pTail->data = digit;
	}
	Node* p = NewNode();
	p->data = digit;
	p->next = ubn->pTail->next;
	ubn->pTail->next = p;
	p->pre = ubn->pTail;
	ubn->pTail = p;
	ubn->digit++;
}
void AppendFrontDigit(UBN* ubn,int digit){
	Node* p = NewNode();
	p->data = digit;
	p->next = ubn->pHead->next;
	if(ubn->pHead->next!=NULL){
		ubn->pHead->next->pre = p;
	}
	ubn->pHead->next = p;
	p->pre = ubn->pHead;
	if(ubn->pTail == ubn->pHead){
		ubn->pTail = p;
	}
	ubn->digit++;
}
void Normalize(UBN* ubn){
	if(ubn->digit==0){
		AppendDigit(ubn,0);
	}
	while(ubn->digit>1&&ubn->pHead->next->data==0){
		Node* p = ubn->pHead->next;
		ubn->pHead->next = p->next;
		p->next->pre = ubn->pHead;
		free(p);
		ubn->digit--;
	}
}
UBN Input(){
	UBN result;
	InitUBN(&result);
	char ch;
	do{
		ch = getchar();
		if(ch=='-')
		{
			result.pHead->data = 1;
			ch = getchar();
			break;
		}
	}while(ch<'0'||ch>'9');
	while(ch>='0'&ch<='9'){
		AppendDigit(&result,ch-'0');
		ch = getchar();
	}
	Normalize(&result);
	return result;
}
void PrintUBN(UBN* ubn){
	assert(ubn->digit>0&&ubn->pHead->next!=NULL);
	if(ubn->pHead->data==1){
		printf("-");
	}
	Node* p = ubn->pHead->next;
	while(p){
		printf("%d",p->data);
		p = p->next;
	}
	printf("\n");
}
UBN SubUBN(UBN* ua,UBN* ub){
	UBN result;
	InitUBN(&result);
	if(ua->digit<ub->digit||(ua->digit==ub->digit&&ua->pHead->next->data<ub->pHead->next->data)){
	  printf("第一个数小于第二个数");
	  return result;
	}
	int icarry = 0;
	Node* p,*q;
	p = ua->pTail;
	q = ub->pTail;
	while(p!=ua->pHead&&q!=ub->pHead){
		int digit = p->data - q->data - icarry;
		if(digit<0){
			icarry = 1;
			digit += 10;
		}else{
			icarry = 0;
		}
		AppendFrontDigit(&result,digit);
		p = p->pre;
		q = q->pre;
	}
	while(p!=ua->pHead){
		int digit =  p->data - icarry ;
		if(digit<0){
			icarry = 1;
			digit += 10;
		}else{
			icarry = 0;
		}
		AppendFrontDigit(&result,digit);
		p = p->pre;
	}
	Normalize(&result); 
	return result;
} 
UBN AddUBN(UBN* ua,UBN* ub){
	UBN result;
	InitUBN(&result);
	int icarry = 0;
	Node* p,*q;
	p = ua->pTail;
	q = ub->pTail;
	while(p!=ua->pHead&&q!=ub->pHead){
		int digit = icarry + p->data + q->data;
		icarry = digit /10;
		digit %= 10;
		AppendFrontDigit(&result,digit);
		p = p->pre;
		q = q->pre;
	}
	while(p!=ua->pHead){
		int digit = icarry + p->data ;
		icarry = digit /10;
		digit %= 10;
		AppendFrontDigit(&result,digit);
		p = p->pre;
	}
	while(q!=ub->pHead){
		int digit = icarry + q->data;
		icarry = digit /10;
		digit %= 10;
		AppendFrontDigit(&result,digit);
		q = q->pre;
	}
	if(icarry!=0){
		AppendFrontDigit(&result,icarry);
	}
	return result;
} 
int Compare(UBN* ua,UBN* ub){
	if(ua->digit<ub->digit){
		return -1;
	}else if(ua->digit>ub->digit){
		return 1;
	}else{
		Node* p,* q;
		p = ua->pHead->next;
		q = ub->pHead->next;
		while(p!=NULL&&q!=NULL){
			if(p->data<q->data){
				return -1;
			}else if(p->data>q->data){
				return 1;
			}else{
				p = p->next;
				q = q->next;
			}
		}
		return 0;	
		}
}
UBN AddBN(UBN* ua,UBN* ub){
	UBN result;
	if(ua->pHead->data==ub->pHead->data){
		result = AddUBN(ua,ub);
		result.pHead->data = ua->pHead->data;
	}else if(ua->pHead->data==1&&ub->pHead->data==0){
		int flag;
		flag = Compare(ua,ub);
		if(flag<=0){
			result = SubUBN(ub,ua);
			result.pHead->data = 0;
		}else{
			result = SubUBN(ua,ub);
			result.pHead->data = 1;
		}
	}else{
		int flag;
		flag = Compare(ua,ub);
		if(flag>=0){
			result = SubUBN(ua,ub);
			result.pHead->data = 0;
		}else{
			result = SubUBN(ub,ua);
			result.pHead->data = 1;
		}
	}
	return result;
}
UBN SubBN(UBN* ua,UBN* ub){
	UBN result;
	if(ua->pHead->data == 0&&ub->pHead->data == 1){
		result = AddUBN(ua,ub);
		result.pHead->data = 0;
	}else if(ua->pHead->data==1&&ub->pHead->data==0){
		result = AddUBN(ua,ub);
		result.pHead->data = 1; 
	}else if (ua->pHead->data==0&&ub->pHead->data == 0){
		int flag = Compare(ua,ub);
		if(flag>=0){
			result = SubUBN(ua,ub);
			result.pHead->data = 0;
		}else{
			result = SubUBN(ub,ua);
			result.pHead->data = 1;
		}
	}else{
	    int flag = Compare(ua,ub);
		if(flag<=0){
			result = SubUBN(ub,ua);
			result.pHead->data = 0;
		}else{
			result = SubUBN(ua,ub);
			result.pHead->data = 1;
		}
	}
	return result;
}
int main(){
	UBN A,B,C,D;
	
	
	A = Input();
	B = Input();
	
	
	C= AddBN(&A,&B);
	D =SubBN(&A,&B); 
//	printf("%d",Compare(&A,&B));
	PrintUBN(&C);
	PrintUBN(&D);


	DestroyUBN(&A); 
	DestroyUBN(&B); 
	DestroyUBN(&C);
	DestroyUBN(&D); 
	return 0;
}

