#include <bits/stdc++.h>
using namespace std;

const int N = 3;

vector<int> mx[1 << N];

char pr[256];

int x[N];


void dec(int i){
    for(int j = 0; j < N; ++j){
        x[j] = (i >> j) & 1;
    }

}


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


int main(){

    set_pr();

    string s;
    cin >> s;


    for(int i = 0; i < (1 << N); ++i){
        dec(i);
        int _l = 0;
        vector<char> s1, s2;
        if(!solve(s, _l, s1, s2)) {
            continue;
        }
        for(int k = 0; k < N; ++k){
            cout << x[k] << ' ';
        }
        cout << endl;
        for(int j = 0; j < N; ++j){
            int d = (i >> j) & 1;
            if(!d){
                dec(i | (1 << j));
                _l = 0;
                s1.clear();
                s2.clear();
                if(solve(s, _l, s1, s2)){
                    mx[i].push_back(j);
                    mx[i | (1 << j)].push_back(j);
                }
            }
        }
    }


    cout << "1";


    for(int i = 0; i < (1 << N); ++i){
        if(mx[i].size() == 1){
            cout << " | (";
            for(int j = 0; j < N; ++j){

                if(j != 0){
                    cout << " & ";
                }
                if(j == mx[i][0]){
                    cout << '1';
                    continue;
                }
                int d = (i >> j) & 1;
                if(!d){
                    cout << "!";
                }
                cout << "x" << j + 1;
            }
            cout << ")";
        }
    }
}
