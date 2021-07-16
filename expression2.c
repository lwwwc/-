#include<stdio.h>
#include<stdlib.h>

typedef struct Num{
	int num[30];
	int top;
}Num;
typedef struct Op{
	char op[30];
	int top;
}Op;

void InitNum(Num* n){
	n->top = 0;
} 
void InitOp(Op* o){
	o->top = 0;
}
char OPop(Op* o){
	return o->op[--o->top]; 
}
int NPop(Num* n){
	return n->num[--n->top];
}
char GetTopO(Op* o){
	return o->op[o->top-1];
}
int GetTopN(Num* n){
	return n->num[n->top-1];
}
void PushO(Op* o,char c){
	o->op[o->top++] = c;
}
void PushN(Num* n,int a){
	n->num[n->top++] = a;
}
void DestroyO(Op* o){
	o->top = 0;
}
void DestroyN(Num* n){
	n->top = 0;
}

void caculate(Op* op,Num* num){
	char op1 = OPop(op);
	int  num1,num2,result;
	num2 = NPop(num);
	num1 = NPop(num);
	switch(op1){
		case'+':result = num1 + num2; break;
		case'-':result = num1 - num2; break;
		case'*':result = num1 * num2; break;
		case'/':result = num1 / num2; break; 
	}
//	printf("%d  ",result);
	PushN(num,result);
}
void dealExpression(Op* op,Num* num){
	char c;
	int flag = 1; 
	int	opNum; 
	scanf("%c",&c);
	while(flag){
		switch(c){
			case '(': PushO(op,c); 	scanf("%c",&c);  break;
			case ')':while(GetTopO(op)!='('){
				       caculate(op,num);
			     	}
			     	OPop(op);
			     	scanf("%c",&c);
			     	break;
		    case '#':while(GetTopO(op)!='#'){
		    	        caculate(op,num);
			         }
			         OPop(op);
					 flag = 0;
					 printf("\n%d",NPop(num)); 
					 break;
			case '+':
			case '-': while(1){
				         if(GetTopO(op)=='#'||GetTopO(op)=='(')
				          break;
				         caculate(op,num);
		            	} 
		            	PushO(op,c);
		            	scanf("%c",&c);
		            break;
			case '*':
			case '/':  while(GetTopO(op)=='*'||GetTopO(op)=='/')
			             caculate(op,num);
			            PushO(op,c);
			            scanf("%c",&c);
			            break;
			default:  
			 	opNum = 0 ;
               do{
			   opNum = opNum*10 + c -'0';
			   scanf("%c", &c);
	       	  }while(c>='0'& c<='9');
//	          printf("%d ",opNum);
		       PushN(num,opNum);
//		    printf("%d",GetTopN(num));
		}
	}
}
int main(){
	Op op;
	Num num;
    InitOp(&op);
    InitNum(&num);
    PushO(&op,'#'); 
    dealExpression(&op,&num);
    DestroyO(&op);
    DestroyN(&num);
//      char c,result;
      
    return 0;
}
