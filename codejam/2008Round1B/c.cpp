#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int query[110];
int answer[110];

int main()
{
	int n, K;
	int T;
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
	scanf("%d", &T);	
	for(int cas = 1; cas <= T; cas++){
		scanf("%d %d", &K, &n);
		memset(answer, -1, sizeof(answer));
		for(int i = 0; i < n; i++){
			scanf("%d", &query[i]);
		}
		int pos = 0;
		for(int i = 1; i <= K; i++){
			pos = (pos+i-1)%(K-i+1);
			for(int j = 0; j < n; j++){
				if(query[j] == pos+1){
					answer[j] = i;
					query[j] = -1;
				}else if(query[j] > pos+1){
					query[j]--;
				}
			}
		}
		printf("Case #%d:", cas);
		for(int i = 0; i < n; i++){
			printf(" %d", answer[i]);	
		}	
		puts("");
	}
	return 0;
}

