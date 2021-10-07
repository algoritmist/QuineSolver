#include <bits/stdc++.h>
using namespace std;

const int N = 4;


char pr[256];

vector<bool> x;

string s;


void set_pr(){
    pr['&'] = 1;
    pr['|'] = 2;
    pr['^'] = 3;
}

int is_op(char c){
    return pr[c] != 0;
}

int is_num(char c){
    return '0' <= c && c <= '9';
}

int make_operation(int a, int b, char op){
    if(op == '&'){
        return a & b;
    }
    if(op == '|'){
        return a | b;
    }
    if(op == '^'){
        return a ^ b;
    }
    return 0;
}

int solve_simple(vector<char> ops, vector<char> vals){
    int n = vals.size();
    vector<int> next(n), bad(n);
    iota(next.begin(), next.end(), 1);
    for(int j = 1; j <= 3; ++j){
        for(int i = 0; i < n - 1; ++i){
            while(pr[ops[i]] == j && !bad[i]){
                vals[i] = make_operation(vals[i], vals[next[i]], ops[i]);
                ops[i] = ops[next[i]];
                bad[next[i]] = 1;
                next[i] = next[next[i]];
            }
        }    
    }
    for(int i = 0; i < n; ++i){
        if(!bad[i]){
            return vals[i];
        }
    }
    return -2e18;
}

int solve(const string &s, int &l, vector<char> &ops, vector<char> &vals){
    if(l == s.size()){
        return solve_simple(ops, vals);
    }
    if(is_op(s[l])){
        ops.push_back(s[l]);
        return solve(s, ++l, ops, vals);
    }
    if(s[l] == 'x' || s[l] =='X'){
        int otr = (s[l] == 'X');
        int ind = 0;
        while(++l < s.size()){
            if(is_num(s[l])){
                ind = ind * 10 + (s[l] - '0');
            }
            else{
                break;
            }
        }
        vals.push_back(x[ind - 1] ^ otr);
        return solve(s, l, ops, vals);
    }
    if(s[l] == ')'){
        return solve_simple(ops, vals);
    }
    if(s[l] != '('){
        cerr << l;
        exit(0);
    }

    vector<char> new_ops, new_vals;
    vals.push_back(solve(s, ++l, new_ops, new_vals));
    return solve(s, ++l, ops, vals);
}

vector<int> find_adj(){

    vector<int> adj;
    for(int i = 0; i < N; ++i){
        x[i] = !x[i];

        vector <char> s1, s2;

        int l = 0;
                
        if(solve(s, l, s1, s2)){
            adj.push_back(i);
        }
        x[i] = !x[i];
    }
    return adj;
}

void print(int ind){
    cout << " | (";
    for(int i = 0; i < N; ++i){
        if(i == ind){
            continue;
        }
        (x[i]) ? cout << 'x' : cout << 'X';
        cout << i + 1;
    }

    cout << ')';

}

void rec(int i){
    if(i == N){
        vector<char> s1, s2;
        int l = 0;
        if(!solve(s, l, s1, s2)){
            return;
        }

        /*for(int i = 0; i < N; ++i){
            cout << x[i];
        }
        cout << endl;*/

        auto adj = find_adj();

        if(adj.size() == 0){
            print(-1);
        }
        if(adj.size() == 1){
            /*for(int i = 0; i < N; ++i){
                if(!x[i]){
                    x[i] = 1;
                    auto new_adj = find_adj();
                    x[i] = 0;
                    if(new_adj.size() == 1){
                        return;
                    }
                }
            }*/
            print(adj[0]);
        }
        
        return;
    }
    rec(i + 1);
    x[i] = 1;
    rec(i + 1);
    x[i] = 0;
}

int main(){

    set_pr();

    cin >> s;

    x.resize(N);

    cout << "0";


    rec(0);


    cout << endl << (long double) clock() / CLOCKS_PER_SEC << endl;
}
