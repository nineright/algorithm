#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

//#define DEBUG

int m[2][2] = {{6, -4}, {1, 0}};

void matrix_mul(int a[][2], int b[][2], int c[][2])
{
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++){
			c[i][j] = 0;
			for(int k = 0; k < 2; k++)
				c[i][j] += a[i][k]*b[k][j];
			c[i][j] %= 1000;
		}
}

void fast_exp(int n, int a[][2])
{
	int b[2][2];
	if(n == 1) {
		memcpy(a, m, sizeof(m));
		return ;
	}
	memset(b, 0, sizeof(b));
	if((n&1) == 0){
		fast_exp(n/2, b);
		matrix_mul(b, b, a);
	}else{
		fast_exp(n-1, b);
		matrix_mul(b, m, a);
	}
}


int main()
{
	int T;
	int n;
#ifndef DEBUG
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	scanf("%d", &T);
	for(int cas = 1; cas <= T; cas++){
		int a[2][2];
		memset(a, 0, sizeof(a));
		scanf("%d", &n);
		fast_exp(n-1, a);	
		double ans = 6*a[0][0]+2*a[0][1];
		int res = (int(ans)%1000+999)%1000;

		printf("Case #%d: ", cas);
		if(res < 10)printf("00");
		else if(res < 100) printf("0");
		printf("%d\n", res);
	}
	return 0;
}

