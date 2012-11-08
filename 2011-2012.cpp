/*
 *   -------->[1 (+7)]<-------->[2 (*3)]
 *   |           /\   \           / /\
 *   |           ||     \       /   ||
 *[0 (2011)]     ||       \  /      ||
 *   |           ||       /  \      ||
 *   |           \/    /       \    \/
 *   --------->[3 (/2)]<------->[4 (-5)]
 *
 * 节点0为初始节点，节点1，2，3，4构成4个节点的有向完全图
 */

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAX_LEN = 4000000;
//对搜索状态进行判重
bool vis[4][MAX_LEN]; 
//运算过程中可能会产生负数，但是-5产生的负数不会太小
const int offset = 1000; 
int g[5][5];
int calc(int num, int t, char *expr)
{
	num -= offset;
	switch(t){
	case 1:
		strcat(expr, "+7)");
		return num+7+offset;
	case 2:
		strcat(expr, "/2)");
		return (num>>1)+offset;
	case 3:
		strcat(expr, "*3)");
		return num*3+offset;
	case 4:
		strcat(expr, "-5)");
		return num-5+offset;
	default:
		printf("Opps t = %d\n", t);
	}
}
bool dfs(int cur, int t, int d, char *expr)
{
	//bool ret = false;
	//在指定表达式操作数数目下存在表达式
	//因为2012不能整除3，所以不可能由*3得到2012
	if(t == 4 && cur == 2012+offset){
		printf("num of operators in expr is %d\n", strlen(expr)/3);
		printf("expression: ");
		for(int i = 0; i < strlen(expr); i += 3)
			putchar('(');
		printf("%s\n", expr);
		return true;
	}
	if(d == 0)
		return false;
	if(t > 0)	
		vis[t-1][cur] = 1;
	for(int i = 1; i <= 4; i++){
		if(i != t && g[t][i]){
			int tmp = calc(cur, i, expr);
			if(tmp < MAX_LEN && !vis[i-1][tmp]){
				if(dfs(tmp, i, d-1, expr))
					//ret = true;
					return true;
			}	
			expr[strlen(expr)-3] = '\0'; 
		}
	}
	//return ret;
	return false;
}
int main()
{

	char expr[100];
	int start = 2011;
	//fill the graph
	memset(g, 0x00, sizeof(g));
	for(int i = 1; i <= 4; i++)
		for(int j = i+1; j <= 4; j++)
			g[i][j] = g[j][i] = 1;
	g[0][1] = g[0][2] = 1;

	//二分表达式长度，限定dfs的搜索深度
	int l = 1, r = 34;
	while(l <= r){
		memset(vis, false, sizeof(vis));	
		memset(expr, 0x00, sizeof(expr));
		int mid = (l+r)/2;
		//length of mid is ok
		if(dfs(2011+offset, 0, mid, expr)){
			r = mid-1;		
		}
		else
			l = mid+1;
	}
	return 0;
}

