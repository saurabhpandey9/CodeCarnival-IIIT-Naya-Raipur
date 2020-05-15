# Problem 1 :
## Saurabh and Exponential Crowd

**Time Limit: 2 seconds**
In the near future, lockdown opened and crowd emerges in the market. Saurabh goes to market to meet his friend after a long time but is unable to find him. Saurabh called his friend to ask where is he. His friend said "Everyone in the crowd is wearing a T-Shirt with a number on it and every T-Shirt repeats \(K\) times except the one I am wearing (Because I am unique)."

Saurabh's friend gives him an array \(A\), consisting of \(N\) integers, where \(A_i\) represents the T-Shirt number of \(i^{th}\) person in the crowd \(1\leq i \leq N\). Saurabh needs to find \(x\), the T-shirt number of his friend, which is unique and every other T-shirt number is repeated.

Now, to reach his friend, Saurabh needs to calculate his friend's location so that he could directly teleport to his friend avoiding contact with any other person. His friend also gave him an integer \(R\) and the location is defined as \(x^{^{2R}C_R}\), where \(^NC_r = \frac{N!}{R!(N-R)!}\)

Saurabh needs to print calculate the location finally. Since the location can be very big, print the location(answer) modulo \(10^9+7\). \([\%(10^9+7)]\).

**Note: Output for 0^0 is 1**
### Input Format
The first line contains \(T\), the number of test cases.

The first line of every test case contains \(N\),\(K\) and \(R\). 

The second line of every test case contains N integers denoting \(A_i\).

### Output Format
For every test case, print location \(\%10^9+7\) in new line.

### Constraints
```
1 ≤ T ≤ 1, 000
3 ≤ N ≤ 1, 00, 000
1 ≤ Ai ≤ 109
2 ≤ K ≤ N − 1
0 ≤ R ≤ 109
```
### Sample Examples

#### Input
```
2
6 5 4
11 11 11 14 11 11
5 2 10
8 8 6 6 7
```
#### Output
```
947961792
527936690
```

### Explanation
In first test case, \(N = 6\), \(K=5\) and \(R = 4\). We can see that \(11\) is repeated 4 times but \(14\) occurs once, so \(x= 14\). Now, \(^{2*4}C_{4}\) = 70. So, the location is \((14^{70}) \% (10^9+7)\) = \(947961792\).

In the second test case, \(N = 5\), \(K=2\) and \(R = 10\). We can see that \(8\) and \(6\) are repeated 2 times but \(7\) occurs once, so \(x= 7\). Now, \(^{2*10}C_{10}\) = \(184756\). So, the location is \((7^{184756}) \% (10^9+7)\) = \(527936690\).

## Code (In C++):

```cpp
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

```

