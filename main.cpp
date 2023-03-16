#include <iostream>
#include <vector>

using namespace std;

vector<int> free_rooms;

void build(int v, int tl, int tr, vector<int>& t) {
    if (tl == tr) {
        t[v] = free_rooms[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(v*2, tl, tm, t);
        build(v*2+1, tm+1, tr, t);
        t[v] = max(t[v*2], t[v*2+1]);
    }
}

int assign_group(int v, int tl, int tr, int x, vector<int>& t) {
    if (t[v] < x) {
        return 0;
    }
    if (tl == tr) {
        free_rooms[tl] -= x;
        t[v] = free_rooms[tl];
        return tl+1;
    }
    int tm = (tl + tr) / 2;
    int hotel_id = assign_group(v*2, tl, tm, x, t);
    if (hotel_id == 0) {
        hotel_id = assign_group(v*2+1, tm+1, tr, x, t);
    }
    t[v] = max(t[v*2], t[v*2+1]);
    return hotel_id;
}

int main() {
    int n, m;
    cin >> n >> m;

    free_rooms.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> free_rooms[i];
    }

    vector<int> t(4*n);
    build(1, 0, n-1, t);

    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        int hotel_id = assign_group(1, 0, n-1, x, t);
        cout << hotel_id << " ";
    }
    cout << endl;

    return 0;
}
