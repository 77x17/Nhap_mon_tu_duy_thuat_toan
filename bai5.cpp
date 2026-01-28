#include <iostream>
using namespace std;

int main() {
    string A, B;
    cin >> A >> B;

    int n = A.size();
    int m = B.size();

    vector<int> lps(m, 0);
    for (int i = 1, len = 0; i < m; ) {
        if (B[i] == B[len]) {
            lps[i ++] = ++len;
        } else if (len) {
            len = lps[len - 1];
        } else {
            lps[i ++] = 0;
        }
    }

    vector<int> ans;
    for (int i = 0, j = 0; i < n; ) {
        if (A[i] == B[j]) {
            i ++, j ++;
        }
        if (j == m) {
            ans.push_back(i - j + 1);
            j = lps[j - 1];
        } else if (i < n && A[i] != B[j]) {
            if (j) {
                j = lps[j - 1];
            } else {
                i ++;
            }
        }
    }

    for (int pos : ans) {
        cout << pos << " ";
    }
}

// Độ phức tạp: O(n + m)

// Gọi KMP[i] là độ dài tiền tố dài nhất của B trùng với hậu tố của A[0..i]
// Ví dụ: 
// A = "genygeny"
// B = "gen"
// KMP[0] = 1;
// KMP[1] = 2;
// KMP[2] = 3 = len(B) => tìm thấy B xuất hiện tại vị trí i - len(B) + 1
// KMP[3] = 0;
// ...

// Làm sao để tính KMP
// Nhận xét: Giả sử KMP[i - 1] = k, khi đó KMP[i] <= k + 1;

// TH tốt nhất: Nếu A[i] == B[k + 1] => KMP[i] = k + 1;
// TH xấu nhất: KMP[i] có thể = 0 nếu không có tiền tố nào trùng với hậu tố của A[0..i]
// TH trung bình: KMP[i] = h + 1 với 0 <= h + 1 < k;

// Quan sát: Nếu KMP[i] = h + 1 với 0 <= h + 1 < k, theo định nghĩa:
// A[i - h .. i] = B[1 .. h + 1]
// => A[i] = B[h + 1]
// => A[i - h .. i - 1] = B[1 .. h] (nói cánh khác, h ký tự đầu của B trùng với h ký tự cuối của A[0..i - 1])


// Nhận xét: Nếu KMP[i - 1] = k và KMP[i] = h + 1 với 0 <= h < k thì xâu B[1..k] có h ký tự đầu tiên giống với h ký tự cuối cùng.
// Ví dụ: B1 B2 B3 B4 B5 B6 B7 B8 B9 B10
//.       A1 A2 A3 A4 A5 A6 A7 A8 A9 A10 A11 A12 A13 A14
// KMP[10] = 7 => B1..B7 = A4..A10 => B5..B7 = A8..A10
// KMP[11] = 4 = 3 + 1 => B1..B4 = A8..A11 => B4 = A11 và B1..B3 = A8..A10
// => B1..B3 = B5..B7

// Như vậy, để tính KMP[i] trong TH trung bình, ta cần xét các độ dài h vừa là tiền tố, vừa là hậu tố của B[1..k]
// ta chọn h lớn nhất thỏa mãn A[i] = B[h + 1] => KMP[i] = h + 1 

// Bài toán trở thành làm sao để tính các độ dài vừa là tiền tố, vừa là hậu tố của B[1..k] một cách nhanh nhất
// Đặt LPS[i] là độ dài lớn nhất của tiền tố của B[1..i] trùng với hậu tố của B[1..i]

// Nhận xét: Nếu B[1..k] có đồng thời h1, h2 vừa là tiền tố, vừa là hậu tố với h1 < h2
// Thì h1 cũng là độ dài vừa là tiền tố, vừa là hậu tố của B[1..h2]
// Danh sách các độ dài vừa là tiền tố, vừa là hậu tố của B[1..k] là: h = LPS[k], LPS[LPS[k]], LPS[LPS[LPS[k]]], ...

// Tính LPS:
// TH1, TH2 như KMP
// TH3: Xét qua các độ dài vừa là tiền tố, vừa là hậu tố của B[1..i - 1] (h = k = LPS[i - 1], h = LPS[k], ...), nếu B[i] = B[h + 1] thì LPS[i] = h + 1
 
