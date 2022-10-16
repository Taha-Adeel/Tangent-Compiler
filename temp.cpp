#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rint(x) int x;cin>>x;
#define rstring(x) string x;cin>>x;
#define tc(t) rint(t)while(t--)
#define all(x) x.begin(), x.end()
#define vi vector<int>
#define vll vector<ll>
#define rvi(a,n) vector<int>a(n);for(auto &i:a)cin>>i;
#define rvll(a,n) vector<ll>a(n);for(auto &i:a)cin>>i;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    variant<bool,int> v,w,x;
    v = false;
    w = false;
    visit( [](auto& l, auto& r, auto&res) {res = l||r;}, v, w, x);
    cout<<get<bool>(x)<<'\n';
}