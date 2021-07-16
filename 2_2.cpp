#include <iostream>
using namespace std;
#include <cstring>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
const int MAX = 50+1;
int a[MAX][MAX];
bool visited[MAX][MAX];
int block = 0;
int m, n, s;
void DFS(int x, int y, int s){
	
	if(visited[x][y]) return;
	visited[x][y]=true;
	if (x+1 >= 0 && x+1 < m && y >= 0 && y < n && !visited[x+1][y] && a[x+1][y] == s){	
		//a[x][y] = 0;
		//visited[x][y] = true;
		DFS(x+1 ,y, s);
	}else if(x-1 >= 0 && x-1 < m && y >= 0 && y < n && !visited[x-1][y] && a[x-1][y] == s){	
		//a[x][y] = 0;
		//visited[x][y] = true;
		DFS(x-1 ,y, s);
	}else if(x >= 0 && x < m && y+1 >= 0 && y+1 < n && !visited[x][y+1] && a[x][y+1] == s){	
		//a[x][y] = 0;
		//visited[x][y] = true;
		DFS(x ,y+1, s);
	}else if(x >= 0 && x < m && y-1 >= 0 && y-1 < n && !visited[x][y-1] && a[x][y-1] == s){	
		//a[x][y] = 0;
		//visited[x][y] = true;
		DFS(x ,y-1, s);
	}
	
}
int main(int argc, char** argv) {
	
	scanf("%d%d",&m,&n);
	
	memset(visited, false, sizeof(visited));
	
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			scanf("%d", &a[i][j]);
		}
	}
	
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			s = a[i][j];
			if(!visited[i][j]&&a[i][j]==s){
				block++;
				DFS(i, j, s);
				
			}
		}
	}
		
	printf("%d", block);
	return 0;
}
