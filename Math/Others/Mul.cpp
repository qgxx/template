// 快速乘


using ll = long long;

ll mul(ll a, ll n, ll p){
    ll ans = 0;   
    while (n) {
        if (n & 1) ans = (ans + a) % p;
        n >>= 1;
        a = (a + a) % p;
    }
    return ans;
}