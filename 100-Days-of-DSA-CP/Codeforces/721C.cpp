/*
░█████╗░███╗░░░███╗░█████╗░███╗░░██╗██╗░░██╗░██████╗██╗░░██╗░█████╗░
██╔══██╗████╗░████║██╔══██╗████╗░██║██║░██╔╝██╔════╝██║░░██║██╔══██╗
███████║██╔████╔██║███████║██╔██╗██║█████═╝░╚█████╗░███████║███████║
██╔══██║██║╚██╔╝██║██╔══██║██║╚████║██╔═██╗░░╚═══██╗██╔══██║██╔══██║
██║░░██║██║░╚═╝░██║██║░░██║██║░╚███║██║░╚██╗██████╔╝██║░░██║██║░░██║
╚═╝░░╚═╝╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝╚═╝░░╚═╝╚═════╝░╚═╝░░╚═╝╚═╝░░╚═╝
*/


#include <bits/stdc++.h>
#include <set>
using namespace std;

#define AAKANKSHA ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define ll long long
using ld = long double;
using vi = vector<int>;
using vc = vector<char>;
using vvi = vector<vi>;
using vll = vector<ll>;
using vvll = vector<vll>;
using vb = vector<bool>;
#define umap unordered_map
#define uset unordered_set
#define lb lower_bound
#define ub upper_bound
#define ppb pop_back
#define pb push_back
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(v) v.begin(), v.end()
#define allr(v) v.rbegin(), v.rend()
#define mems(x, v) memset(x, v, sizeof(x))
#define sz(v) ((int)(v).size())
#define rep(i,a,b) for(int i=a;i<b;i++)
#define rrep(i,a,b) for(int i=a;i>=b;i--)
#define log(x)  std::cout<<x<<std::endl;
#define logs(x)  std::cout<<x<<" ";

const double PI = acos(-1.0);
const int INF = 1e9;
const ll MOD = 1e9+7;

std::vector<std::pair<int, int>> adj[5005];
int dp[5005][5005];
void addEdge(int u, int v, int wt) {

    //we transposed the graph
    adj[v].push_back(std::make_pair(u, wt)); // Comment this line for a directed graph
}

int solve(int node, int noOfNodesVisited) {
    //i learnt that if you are guessing any state which is of the form 10^9 you are thinking wrong
    //learnt answer construction
    if(noOfNodesVisited<0)return 1e9+7;
    if(node==1 and noOfNodesVisited==1) return 0;
    if(dp[node][noOfNodesVisited]!=-1) return dp[node][noOfNodesVisited];

    int ans=1e9+7;
    for(auto child:adj[node]) {
    int temp=solve(child.first,noOfNodesVisited-1);
    if( temp+child.second <= ans ){
        ans=temp+child.second;
    }
}
    return dp[node][noOfNodesVisited]=ans;
}

int main() {
    AAKANKSHA;
    
    int t = 1;
    // Uncomment the next line if there are multiple test cases
    // cin >> t;
    while(t--) {
        int n,m,T;
        cin>>n>>m>>T;

        rep(i,0,m) {
            int u,v,wt;
            cin>>u>>v>>wt;
            addEdge(u,v,wt);
        }
        mems(dp,-1);
        rep(i,1,n+1){
            solve(n,i);
        }
        int noOfNodes;
        rrep(j,n,1){
            if(dp[n][j] <=T){
                logs(j)
                noOfNodes=j;
                break;

            }
        }
        cout<<endl;
        int answer=noOfNodes;
        vi path;
        int node=n;
        while(answer!=0){
            path.pb(node);
            for(auto & [x,y]: adj[node]){
                if(dp[x][answer-1]==dp[node][answer]-y){
                    node=x;
                    break;
                }
            }
            answer--;
        }
        path.pop_back();
        path.pb(1);
    reverse(all(path));
    for(auto &x:path)logs(x);
    }

    return 0;
}
