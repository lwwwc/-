#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#define SElemType char
#define Size 10
//Ë³ÐòÕ» 
typedef struct Stack{
	SElemType* base;
	SElemType* top;
	int size;
}Stack;

//Õ»º¯Êý 
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
		printf("¿ÕÕ»");
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
void caculate(Stack* op,Stack* num){
	char op1 = Pop(op);
	char num1,num2,result;
	num2 = Pop(num);
	num1 = Pop(num);
	switch(op1){
		case'+':result = num1 + num2;	Push(num,result); break;
		case'-':result = num1 - num2; 	Push(num,result); break;
		case'*':result = num1 * num2; 	Push(num,result); break;
		case'/':result = num1 / num2; 	Push(num,result); break; 
		default:;
	}
//	printf("%d  ",result);

}
void dealExpression(Stack* op,Stack* num){
	char c;
	int flag = 1; 
	int	opNum; 
	scanf("%c",&c);
	while(flag){
		switch(c){
			case '(': Push(op,c); 	scanf("%c",&c);  break;
			case ')':while(GetTop(op)!='('){
				       caculate(op,num);
			     	}
			     	Pop(op);
			     	scanf("%c",&c);
			     	break;
		    case '#':while(GetTop(op)!='#'){
		    	        caculate(op,num);
			         }
			         Pop(op);
					 flag = 0;
					 break;
			case '+':
			case '-': while(1){
				         if(GetTop(op)=='#'||GetTop(op)=='(')
				          break;
				         caculate(op,num);
		            	} 
		            	Push(op,c);
		            	scanf("%c",&c);
		            break;
			case '*':
			case '/':  while(GetTop(op)=='*'||GetTop(op)=='/')
			             caculate(op,num);
			            Push(op,c);
			            scanf("%c",&c);
			            break;
			default:  
				opNum = 0 ;
             do{
			 opNum = opNum*10 + c -'0';
			 scanf("%c", &c);
	       	}while(c>='0'& c<='9');
		    Push(num,opNum);
		}
//		if(c=='#'){
//			break;
//		}
//		scanf("%c",&c);
	}
	printf("\n%d",Pop(num)); 
}
int main(){
	Stack op,num;
    Init(&op);
    Init(&num);
    Push(&op,'#'); 
    dealExpression(&op,&num);
    DestroyStack(&op);
    DestroyStack(&num);
//      char c,result;
      
    return 0;
}
