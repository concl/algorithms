// // Standard io interface
// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n;
//     cin >> n;
//     vector<ll> arr(n);
//     for (int i = 0; i < n; i++) {
//         cin >> arr[i];
//     }

//     LazySegmentTree tree(arr);

//     int q;
//     cin >> q;
//     for (int _ = 0; _ < q; _++) {

//         string query_type;
//         cin >> query_type;
//         if (query_type == "range_update") {
//             int l, r;
//             ll val;
//             cin >> l >> r >> val;
//             tree.range_update(l, r, val);
//         } else if (query_type == "query") {
//             int l, r;
//             cin >> l >> r;
//             ll res = tree.query(l, r);
//             cout << res << endl;
//         } else {
//             cerr << "Skipping unknown query type" << endl;
//         }
//     }

//     return 0;
// }