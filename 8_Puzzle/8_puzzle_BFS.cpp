#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<algorithm>

using namespace std;

class State {
public:
    int id;
    int parent_id;
    vector<vector<int>> s;

    State() {
        s = vector<vector<int>>(3, vector<int>(3));
    }

    bool operator==(const State &other) const {
        return s == other.s;
    }
};

bool Goal_test(const State &a, const State &b) {
    return a.s == b.s;
}

string encode(const vector<vector<int>> &s){
    string key = "";
    for(const auto &row : s){
        for(int val : row){
            key += to_string(val);
        }
    }
    return key;
}

vector<State> genMove(const State &current, int &id_counter) {
    int row, col;
    vector<State> next_states;

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(current.s[i][j] == 0){
                row = i;
                col = j;
                break;
            }
        }
    }

    int dir[4][2] = {{-1,0},{1,0},{0,-1},{0,1}}; 

    for(int d=0; d<4; d++){
        int new_r = row + dir[d][0];
        int new_c = col + dir[d][1];
        if(new_r >= 0 && new_r < 3 && new_c >= 0 && new_c < 3){
            State new_state = current;
            swap(new_state.s[row][col], new_state.s[new_r][new_c]);
            new_state.parent_id = current.id;
            new_state.id = ++id_counter;
            next_states.push_back(new_state);
        }
    }

    return next_states;
}

void printState(const vector<vector<int>> &s){
    for(const auto &row : s){
        for(int val : row){
            cout << val << " ";
        }
        cout << endl;
    }
    cout << "-----" << endl;
}

void solve(State start, State goal){
    queue<State> q;
    set<string> visited;
    map<int, State> all_states;
    int id_counter = 1;
    start.id = id_counter;
    start.parent_id = 0;

    q.push(start);
    visited.insert(encode(start.s));
    all_states[start.id] = start;

    while(!q.empty()){
        State curr = q.front();
        q.pop();

        if(Goal_test(curr, goal)){
            vector<State> path;
            State trace = curr;
            while(trace.id != 0){
                path.push_back(trace);
                trace = all_states[trace.parent_id];
            }
            reverse(path.begin(), path.end());

            cout << "Goal Reached!" << endl;
            cout << "Number of steps: " << path.size() - 1 << endl;
            cout << "Path from start to goal:" << endl;

            for(const auto &st : path){
                printState(st.s);
            }
            return;
        }

        vector<State> moves = genMove(curr, id_counter);
        for(auto &state : moves){
            string key = encode(state.s);
            if(!visited.count(key)){
                visited.insert(key);
                q.push(state);
                all_states[state.id] = state;
            }
        }
    }

    cout << "No solution found." << endl;
}

int main(){
    State start, goal;

    cout << "Enter initial state (use 0 for blank):" << endl;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cin >> start.s[i][j];
        }
    }
    int count = 1;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            goal.s[i][j] = count;
            count++;
        }
    }
    goal.s[2][2] = 0;
    

    if(Goal_test(start, goal)){
        cout << "Already at goal!" << endl;
        printState(start.s);
    } else {
        solve(start, goal);
    }

    return 0;
}
