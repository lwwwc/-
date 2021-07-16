#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize  100

typedef struct {
	float data[maxsize];
	int top;
}number;

typedef struct{
	char data[maxsize];
	int top;
}sign;

number Num;
sign sig;
char expression[maxsize];

void InitNumber(number* stack){
	stack->top = 0;
}
void InitSign(sign* stack){
	stack->top = 0;
}
void PopNumber(number* stack,float* e){
	if(stack->top==0){
		printf("空栈1");
	}else
	*e = stack->data[--stack->top];
}
void PopSign(sign* stack,char* e){
	if(stack->top==0){
		printf("空栈2");
	}else
	*e = stack->data[--stack->top];
}
void PushNumber(number* stack,float e){
	stack->data[stack->top++] = e; 
}
void PushSign(sign* stack,char e){
	stack->data[stack->top++] = e;
} 
void GetTopNumber(number* stack,float* e){
	if(stack->top==0){
		printf("空栈3");
	}else
	*e = stack->data[stack->top-1];
}
void GetTopSign(sign* stack,char* e){
	if(stack->top==0){
		printf("空栈4");
	}else
	*e = stack->data[stack->top-1]; 
}
void Caculate(number* num,char e){
	float num1,num2,result;
	PopNumber(&Num,&num2);
	PopNumber(&Num,&num1); 
	switch(e){
		case '+': result = num1 + num2;
		break;
		case '-': result = num1 - num2;
		break;
		case '*': result = num1 * num2;
		break;
		case'/': 
		if(num2==0){
			printf("表达式出错");
		} else{
			result = num1/num2;
			break;
		}
	}
	PushNumber(&Num,result);
}
int main(){
	InitNumber(&Num);
	InitSign(&sig);
	PushSign(&sig,'#');
//	printf("%d",sig.top);
	gets(expression);
	char op;
	float res;
    int length = strlen(expression);
    int i;
	for(i = 0; i< length;i++){
		if(expression[i]>='0'&&expression[i]<='9'){
			int opnum = expression[i] - '0';
		    while(expression[i+1]!='\0'&&expression[i+1]>='0'&&expression[i+1]<='9'){
		    	opnum = opnum*10 + expression[i+1] - '0';
		    	i++; 
			}
			PushNumber(&Num,opnum);
		}else{
			switch(expression[i]){
				case '(': 
				    PushSign(&sig,'(');
				    break;
				case '+':
				case '-':
					GetTopSign(&sig,&op);
					while(op!='('&op!='#'){
						Caculate(&Num,op);
						PopSign(&sig,&op);
						GetTopSign(&sig,&op); 
					}
					PushSign(&sig,expression[i]);
				 	break;
				case '*':
				case '/':
					GetTopSign(&sig,&op);
					while(op!='('&op!='#'&op!='+'&op!='-'){
						Caculate(&Num,op);
						PopSign(&sig,&op);
						GetTopSign(&sig,&op); 
					}
					PushSign(&sig,expression[i]);
					break;
				case ')':
					GetTopSign(&sig,&op);
					while(op!='('){
						Caculate(&Num,op);
						PopSign(&sig,&op);
						GetTopSign(&sig,&op); 
					}
					PopSign(&sig,&op); 
					break;
				case '#':
					GetTopSign(&sig,&op);
					while(op!='#'){
						Caculate(&Num,op);
						PopSign(&sig,&op);
						GetTopSign(&sig,&op); 
					}
					PopSign(&sig,&op); 
					break;	
			}
		}
	}
	PopNumber(&Num,&res);
	printf("结果：%.2f",res);
	
	return 0;
} 

