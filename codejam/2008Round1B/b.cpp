#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 1000000+1000;
bool cp[MAXN];
int pp[MAXN];

int uni_find(int t)
{
	if(pp[t] == t)
		return t;	
	return pp[t] = t;		
}

void set_union(int a, int b)
{
	int pa = uni_find(a);
	int pb = uni_find(b);
	pp[pa] = pb;
}

int main()
{
	int T;
	ll p, a, b;
	memset(cp, false, sizeof(cp));
	for(int i = 2; i <= 1000000; i++){
		if(cp[i]) continue;
		for(int j =i*2; j <= 1000000; j += i)
			cp[j] = 1; 
	}
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
	scanf("%d", &T);	
	for(int cas=1; cas <= T; cas++){
		scanf("%lld %lld %lld", &a, &b, &p);
		for(ll i = a; i <= b; i++){
			pp[i-a] = i-a;
		}
		printf("Case #%d: ", cas);
		if(p > b-a){
			printf("%lld\n", b-a+1);
			continue;
		}
		int ans = 0;
		if(a < p){
			ans += (p-a);
			a = p;
		}
		for(ll i = p; i <= (b-a); i++){
			if(cp[i])
				continue;
			ll t = ((a+i-1)/i)*i;
			if(t > b)
				continue;
			for(ll j = t; j <= b; j += i){
				set_union(j-a, t-a);
			}
		}
		//printf("ans = %d\n", ans);
		for(ll i = a; i <= b; i++){
			pp[i-a] = uni_find(int(i-a));
			//printf("p[%lld]= %lld\n", i, pp[i-a]+a);
			if(pp[i-a] == (i-a))
				ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}

