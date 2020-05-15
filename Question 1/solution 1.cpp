#include <bits/stdc++.h>
#include<ctime>
using namespace std;

typedef long long int ll;
const ll MOD = 1e9+7;
const ll MAX = 2e5+5;
#define FIO ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);

#define inp(arr, n)            \
    for (ll i = 0; i < n; i++) \
        cin >> arr[i];

ll power(ll x,ll y){
    ll res = 1;
    while(y){
        if(y&1) res = res*x;
        x*=x;
        y>>=1;
    }
    return res;
}

ll mod_power(ll x,ll y,ll mod){
    ll res = 1;
    while(y){
        if(y&1) res = (res*x)%mod;
        x = (x*x)%mod;
        y>>=1;
    }
    return res%mod;
}
ll get_once_occurence(ll arr[],ll N,ll K){
    ll answer = 0;
    if(K&1){
        ll dp[32];
        memset(dp,0,sizeof(dp));
        for(ll i=0;i<N;i++){
            ll curr = arr[i];
            while(curr){
                ll p = curr&(-curr);
                curr = curr-p;
                ll pos = log2(p);
                dp[pos] = (dp[pos]+1)%K;
            }
        }
        for(ll i=0;i<32;i++){
            answer += power(2,i)*dp[i];
        }
    }else{
        for(ll i =0;i<N;i++){
            answer^=arr[i];
        }
    }
    return answer;
}

ll fact_2[MAX];
ll fact_5e8_3[MAX];
ll fact[MAX];
void precompute(){
    fact_2[0]=fact_5e8_3[0]=fact[0]=1;
    ll mod1 = 2;
    ll mod2 = 5e8+3;
    for(ll i =1;i<=MAX;i++){
        fact_2[i] = (fact_2[i-1]*i)%mod1;
        fact_5e8_3[i] = (fact_5e8_3[i-1]*i)%mod2;
        fact[i] = (fact[i-1]*i)%MOD;
    }
}

ll CRT(ll num[],ll rem[],ll N){
    ll prod = 1;
    for(ll i=0;i<N;i++)
        prod*=num[i];
    ll result = 0;
    for(ll i =0;i<N;i++){
        ll pp = prod/num[i];
        ll temp = (rem[i]*mod_power(pp,num[i]-2,num[i]))%prod;
        temp = (temp*pp)%prod;
        result =  (result%prod+temp%prod)%prod;
    }
    return result%prod;
}

ll solve(ll x,ll N){
    ll mod1 = 2;
    ll mod2 = 5e8+3;
    ll r1 = 0;
    ll r2 = (fact_5e8_3[2*N]*mod_power(fact_5e8_3[N],mod2-2,mod2))%mod2;
    r2 = (r2*mod_power(fact_5e8_3[N],mod2-2,mod2))%mod2;
    if(r2<0){
        r2 = (r2+mod2)%mod2;
    }
    ll num[] = {mod1,mod2};
    ll rem[] = {r1,r2};
    ll y = CRT(num,rem,2);
    if(x==0 && y==0)
        return 1;

    return mod_power(x,y,MOD);
}

int main(int argc, char const *argv[]){
    FIO
    time_t start_time,end_time;
    start_time = time(NULL);   
    precompute();
    // freopen(argv[1],"r",stdin);
    // freopen(argv[2],"w",stdout);
    ll T;
    cin >> T;
    while (T--){
        ll N,K,R;
        cin>>N>>K>>R;
        ll arr[N];
        inp(arr,N)
        ll x = get_once_occurence(arr,N,K);
        ll z = solve(x,R);
        cout<<z<<"\n";
    }
    end_time = time(NULL);  
    return 0;
}