#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#define SElemType int
#define Size 10
//˳��ջ 
typedef struct Stack{
	SElemType* base;
	SElemType* top;
	int size;
}Stack;
//�ڵ� 
typedef struct Node{
	int data;
	struct Node* next;
}Node;
//������
typedef struct Queue{
	Node* pHead;
	Node* pTail;
}Queue;
 
 
//ջ���� 
int Init(Stack* dest){
//	Stack dest;
	dest->base = dest->top = (SElemType*)malloc(Size*sizeof(SElemType));
	if(dest->base==NULL){
		printf("full m");
	return 0;
    }
    dest->size = Size;
    return 1;
}
void DestroyStack(Stack* stack){
	free(stack->base);
    stack->base = stack->top = NULL;
	stack->size = 0;
    return ;
}
int Push(Stack* stack,SElemType e){
	if(stack->top-stack->base >= stack->size){
		SElemType* p = realloc(stack->base,2*Size*sizeof(SElemType));
		if(p==NULL){
			return 0;
		}
		stack->base = p;
		stack->top = stack->base + stack->size;
		stack->size *= 2;
	}
	*stack->top = e;
	stack->top++;
	return 1;
}
SElemType GetTop(Stack* stack){
	if(stack->top==stack->base){
		printf("��ջ");
		return 0;
	}
	return *(stack->top-1);
}
SElemType Pop(Stack* stack){
   SElemType temp;
   temp = *(--stack->top);
   return temp;
}
int SLength(Stack stack){
	return (stack.top-stack.base);
}
//���к���
int InitQueue(Queue* queue){
	queue->pHead = queue->pTail = (Node*)malloc(sizeof(Node));
	if(queue->pHead==NULL){
	  printf("mem full");
	  return 0;
	}
	queue->pHead->next = NULL; 
    return 1;
}
void ClearQueue(Queue* queue){
	Node* p = queue->pHead;
	while(p->next!=NULL){
		Node* q = p->next;
		p->next = q->next;
		free(q);
	}
	queue->pTail = queue->pHead;
}
void DestroyQueue(Queue* queue){
	ClearQueue(queue);
	free(queue->pHead);
//	printf("over");
	queue->pHead = queue->pTail = NULL; 
}
int QLength(Queue queue){
	Node* p = queue.pHead;
	int icount = 0;
	while(p->next!=NULL&&p!=queue.pTail){
		icount++;
		p = p->next;
	} 
	return icount;
}
int EnQueue(Queue* queue,int e){
	Node* s = (Node*)malloc(sizeof(Node));
	if(s==NULL){
		printf("mem full");
		return 0;
	}
	s->data = e;
	s->next = queue->pTail->next;
	queue->pTail->next = s;
	queue->pTail = s;
	return 1;
}
int GetHead(Queue* queue){
	return queue->pHead->next->data;
}
int DeQueue(Queue* queue,int* x){
	if(queue->pHead->next!=NULL){
	*x = queue->pHead->next->data;
	Node* p = queue->pHead->next;
	queue->pHead->next = p->next;
	if(p==queue->pTail){
		queue->pTail = queue->pHead;
	}
	free(p);
	return 1;
	}else{
		printf("�ն���");
		return 0;
	} 
}

 
//���� 
int main(){
	Stack stack ;
	Queue queue;
	Init(&stack);
	InitQueue(&queue);
	
	int x,i;
	while(1){
		scanf("%d",&x);
		if(x==0){
			break;
		}else if(x>0){
			Push(&stack,x);
//			printf("success\n");
		}else{
			EnQueue(&queue,x);
//			printf("sucess\n");
		}
	} 
	int sl,ql;
	sl = SLength(stack);
	ql = QLength(queue);
	
	
   printf("ջ��Ԫ��:\n");
   for(i=0;i<sl;i++){
   	printf("%d  ",Pop(&stack));
   }
   printf("\n������Ԫ�أ�\n");
   for(i=0;i<ql;i++){
   	int s;
   	DeQueue(&queue,&s);
	   printf("%d  ",s); 
   }
   DestroyStack(&stack);
   DestroyQueue(&queue);
   return 0;  	
} 
