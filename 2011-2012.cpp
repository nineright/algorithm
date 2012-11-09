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

typedef unsigned char uint8;
const int MAX_LEN = 2000000;
const int MAX_QLEN = 1000000;
//对搜索状态进行判重
int g[5][5];

typedef struct{
	int cs;   //当前值
	int pre; //上次所在节点在队列中的下标
	uint8 dir; //dir=1表示在当前节点右侧，dir=0在左侧
	uint8 t;   //当前状态所在节点
}QNode;
QNode que[MAX_QLEN];
uint8 vis[4][MAX_LEN][2];
int calc(int num, uint8 t)
{
//	printf("%s\n", expr);
	switch(t){
	case 1:
		return num+7;
	case 2:
		return num*3;
	case 3:
		return (num>>1);
	case 4:
		return num-5;
	default:
		printf("Opps t = %d\n", t);
	}
}

//通过记录两边操作次数的奇偶性判断从左/右边到右/左边的操作是否合法
bool check(uint8 pre, uint8 t, uint8 dir)
{
	//上次操作和本次操作属于同一侧
	if((pre&1) == (t&1))
		return true;	

	if(t == 1 || t == 3)
		return dir == 0;	
	else 
		return dir == 1;
}

void print_expr(int idx)
{
	if(que[idx].pre != -1)
		print_expr(que[idx].pre);

	switch(que[idx].t){
	case 1:
		printf("+7)");
		break;
	case 2:
		printf("*3)");
		break;
	case 3:
		printf("/2)");
		break;
	case 4:
		printf("-5)");
		break;
	defalut:
		printf("Opps t = %d\n", que[idx].t);
	}
}

void bfs()
{
	int start = 2011;	
	int rear, front;
	front = rear = 0;
	que[rear].cs= start+7;
	que[rear].t = 1;
	que[rear].pre = -1;
	que[rear++].dir = 1;

	que[rear].cs= start/2;
	que[rear].t = 3;
	que[rear].pre = -1;
	que[rear++].dir = 1;

	memset(vis, 0x00, sizeof(vis));
	vis[0][start+7][1] = 1;
	vis[2][start/2][1] = 1;
	while(front < rear && rear < MAX_QLEN){
		QNode cur = que[front++];
		uint8 t = cur.t;
		//printf("[%d] cs:%d t:%d pre:%d dir:%d\n", front-1, cur.cs, cur.t, cur.pre, cur.dir);
		if(cur.cs == 2012 && t == 4 && cur.dir == 1){
			printf("Min number of operator is %d\n", vis[t-1][cur.cs][cur.dir]);
			for(int i = 0; i < vis[cur.t-1][cur.cs][cur.dir]; i++)
				putchar('(');
			printf("2011");
			print_expr(front-1);
			puts("");
			break;
		}
		for(int i = 1; i <= 4; i++){
			if(i != t && g[t][i] && check(t, i, cur.dir)){
				QNode tmp;
				if((t&1) == (i&1))
					tmp.dir = cur.dir^1;//在同一侧绕圈,反向改变
				else tmp.dir = cur.dir;
				tmp.cs = calc(cur.cs, i);
				tmp.t = i;
				tmp.pre = front-1;
				
				//if(tmp.cs < 0)
				//	printf("%d\n", vis[t-1][cur.cs][cur.dir]);	
				if(tmp.cs >= 0 && tmp.cs < MAX_LEN && !vis[i-1][tmp.cs][tmp.dir]){
					que[rear++] = tmp;	
					vis[i-1][tmp.cs][tmp.dir] = vis[t-1][cur.cs][cur.dir]+1;
				}
			}
		}
	}
	
}
int main()
{

	char expr[100];
	//fill the graph
	memset(g, 0x00, sizeof(g));
	for(int i = 1; i <= 4; i++)
		for(int j = i+1; j <= 4; j++)
			g[i][j] = g[j][i] = 1;
	g[0][1] = g[0][3] = 1;

	bfs();
	return 0;
}

/*
 * Min number of operator is 26
 * ((((((((((((((((((((((((((2011/2)+7)/2)+7)/2)+7)/2)+7)/2)*3) \
 *  			-5)*3)-5)+7)/2)-5)*3)-5)*3)/2)+7)-5)*3)/2)+7)-5)	
 * 
 */
