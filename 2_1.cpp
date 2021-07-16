#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int max, min;
	int x;
	scanf("%d", &x);
	max = x;
	min = x;
	while(scanf("%d", &x)!=EOF){
		if(x > max) max = x;
		if(x < min) min = x;
	}
	printf("%d,%d", min, max);
	return 0;
}
