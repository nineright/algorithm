#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int MAXN = 1000+10;
ll l[MAXN], r[MAXN];
int main()
{
	int T;
	int n;
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
	scanf("%d", &T);
	for(int cas = 1; cas <= T; cas++){
		scanf("%d", &n);	
		for(int i = 0; i < n; i++){
			scanf("%lld", &l[i]);
		}
		for(int i = 0; i < n; i++){
			scanf("%lld", &r[i]);
		}
		sort(l, l+n);
		sort(r, r+n);
		
		ll ans = 0;
		for(int i = 0; i < n; i++){
			ans += l[i]*r[n-i-1];
		}
		printf("Case #%d: %lld\n", cas, ans);
	}
	return 0;
}
