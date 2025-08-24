#include <bits/stdc++.h>
using namespace std;

int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
int dy[8] = {0, 0, 1, -1, 1, -1, 1, -1};
double cost[8] = {1, 1, 1, 1, 1.5, 1.5, 1.5, 1.5};

struct Node {
    int x, y;
    double g, f;
    Node(int _x, int _y, double _g, double _f) : x(_x), y(_y), g(_g), f(_f) {}
    bool operator>(const Node &other) const {
        return f > other.f; 
    }
};

double heuristic(int x1, int y1, int x2, int y2) {
    int dx = abs(x1 - x2);
    int dy = abs(y1 - y2);
    int dmin = min(dx, dy);
    int dmax = max(dx, dy);
    return dmin * 1.5 + (dmax - dmin) * 1.0;
}

bool inBounds(int x, int y, int n, int m){
    return (x>=0 && x<n && y>=0 && y<m);
}

vector<pair<int,int>> Gen_Move(vector<string>& grid, pair<int,int> start, pair<int,int> goal) {
    int n = grid.size(), m = grid[0].size();

    vector<vector<double>> g(n, vector<double>(m, 1e9));
    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, {-1,-1}));
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    g[start.first][start.second] = 0;
    pq.push(Node(start.first, start.second, 0, heuristic(start.first, start.second, goal.first, goal.second)));
 
    while(!pq.empty()) {
        Node curr = pq.top(); 
        pq.pop();
        int x = curr.x, y = curr.y;

        if (x == goal.first && y == goal.second) {
            vector<pair<int,int>> path;
            while (!(x == -1 && y == -1)) {
                path.push_back({x,y});
                auto p = parent[x][y];
                x = p.first; y = p.second;
            }
            reverse(path.begin(), path.end());
            return path;
        }
        for(int i=0;i<8;i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(!inBounds(nx, ny, n, m)) continue;
            if(grid[nx][ny] == '#') continue; 

            double ng = g[x][y] + cost[i];
            if(ng < g[nx][ny]) {
                g[nx][ny] = ng;
                parent[nx][ny] = {x,y};
                double f = ng + heuristic(nx, ny, goal.first, goal.second);
                pq.push(Node(nx, ny, ng, f));
            }
        }
    } 
    return {};
}

void Take_inputs(){
    int n,m;
    cout<<"Enter Grid Size : "<<endl;
    cin>>n>>m;

    vector<string> grid(n, string(m, '.'));

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            grid[i][j] = '.';
        }
    }

    int st1,st2;
    pair<int,int> start, goal;
    cout<<endl<<"Enter Start Coordinates : "<<endl;
    cin>>st1>>st2;
    start={st1,st2};
    grid[st1][st2] = 'S';

    int end1,end2;
    cout<<endl<<"Enter Destination Coordinates : "<<endl;
    cin>>end1>>end2;
    goal={end1,end2};
    grid[end1][end2] = 'D';

    int r;
    cout<<"Enter number of rivers : "<<endl;
    cin>>r;

    for(int i=0;i<r;i++){
        int a,b;
        cout<<"Enter River "<<i<<" coordinates :";
        cin>>a>>b;
        grid[a][b] ='#';
    }
    auto path = Gen_Move(grid,start,goal);
    if(path.empty()){
        cout<<"No path found\n";
    }else{
        cout << "Path found:\n";
        for(auto [x,y] : path) {
            cout << "(" << x << "," << y << ") ";
            if(grid[x][y] == '.') grid[x][y] = '*'; 
        }
        cout << "\n\nGrid with path:\n";
        for(auto row : grid) cout << row << "\n";
    }
}

int main(){
    Take_inputs();
    return 0;
}
