#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    vector<char> digit(n);

    queue<int> q;

    int start = 1 % n;

    // Nếu x % n = y % n => (x + k*n) % n = (y + k*n) % n với mọi k >= 0

    q.push(start);
    visited[start] = true;
    digit[start] = '1';

    int found = -1;
    int level = 1;

    while (!q.empty() && level <= 9) {
        int sz = q.size();
        while (sz --) {
            int u = q.front();
            q.pop();

            if (u == 0) {
                found = u;
                break;
            }

            for (char d : {'0', '1'}) {
                int v = (u * 10 + (d - '0')) % n;
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    digit[v] = d;
                    q.push(v);
                }
            }
        }
        if (found != -1) break;
        level ++;
    }

    if (!visited[0]) return 0;

    string res;
    for (int r = 0; r != -1; r = parent[r]) {
        res += digit[r];
    }
    reverse(res.begin(), res.end());

    cout << res;
}

// Độ phức tạp: O(n)
// Ý tưởng: Sử dụng BFS để tìm số nhỏ nhất gồm các chữ số 0 và 1 chia hết cho n
// Mỗi trạng thái là số dư khi chia cho n
// Từ mỗi trạng thái u, ta có thể chuyển sang trạng thái v = (u * 10 + d) % n với d là chữ số 0 hoặc 1
// Khi tìm thấy trạng thái 0, ta dừng và truy vết lại để lấy số cần tìm.    

// Tại sao có thể dùng % n để giảm trạng thái?
// Giả sử ta có hai số x và y mà x % n = y % n
// Khi đó ta có thể viết x = a*n + r và y = b*n + r với r = x % n = y % n
// Bất kỳ số nào được tạo thành từ x hoặc y bằng cách thêm các chữ số 0 hoặc 1 vào cuối
// đều có dạng:
// x' = x * 10^k + m
// y' = y * 10^k + m
// Khi đó:
// x' % n = ( (a*n + r) * 10^k + m ) % n = ( r * 10^k + m ) % n
// y' % n = ( (b*n + r) * 10^k + m ) % n = ( r * 10^k + m ) % n
// Vậy x' % n = y' % n
// Do đó, ta chỉ cần quan tâm đến các trạng thái từ 0 đến n-1 (các số dư khi chia cho n)