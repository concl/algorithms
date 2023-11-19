{
	// Place your cp-setup-c++ workspace snippets here. Each snippet is defined under a snippet name and has a scope, prefix, body and 
	// description. Add comma separated ids of the languages where the snippet is applicable in the scope field. If scope 
	// is left empty or omitted, the snippet gets applied to all languages. The prefix is what is 
	// used to trigger the snippet and the body will be expanded and inserted. Possible variables are: 
	// $1, $2 for tab stops, $0 for the final cursor position, and ${1:label}, ${2:another} for placeholders. 
	// Placeholders with the same ids are connected.
	// Example:
	// "Print to console": {
	// 	"scope": "javascript,typescript",
	// 	"prefix": "log",
	// 	"body": [
	// 		"console.log('$1');",
	// 		"$2"
	// 	],
	// 	"description": "Log output to console"
	// }
	"C++ Competitive Programming Template": {
        "prefix": "cp_setup",
        "body": [
            "#include <bits/stdc++.h>",
			"#include <ext/pb_ds/assoc_container.hpp>",
			"",
			"/* #region cp template */",
			"#define ll long long",
			"#define ld long double",
			"#define pb push_back",
			"#define mp make_pair",
			"#define pii pair<int, int>",
			"#define pll pair<ll, ll>",
			"#define vi vector<int>",
			"#define vll vector<ll>",
			"#define vvi vector<vi>",
			"#define vvl vector<vll>",
			"#define endl \"\\n\"",
			"#define all(x) (x).begin(), (x).end()",
			"#define elif else if",
			"#define hash_table gp_hash_table",
			"#define forn(i,n) for(int i=0;(i)<(n);i++)",
			"",
            "using namespace std;",
			"using namespace __gnu_pbds;",
			"",
			"",
			"struct custom_hash {",
			"    static uint64_t splitmix64(uint64_t x) {",
			"        // http://xorshift.di.unimi.it/splitmix64.c",
			"        x += 0x9e3779b97f4a7c15;",
			"        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;",
			"        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;",
			"        return x ^ (x >> 31);",
			"    }",
			"    size_t operator()(uint64_t x) const {",
			"        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();",
			"        return splitmix64(x + FIXED_RANDOM);",
			"    }",
			"};",
			"",
			"template <typename X, typename Y>",
			"using safe_map = unordered_map<X, Y, custom_hash>;",
			"",
			"template <typename X>",
			"using safe_set = unordered_set<X, custom_hash>;",
			"",
			"template <typename X, typename Y>",
			"using safe_hash_table = hash_table<X, Y, custom_hash>;",
			"",
            "template<typename A, typename B> ostream& operator<< (ostream &cout, pair<A,B> const &p) {",
			"    return cout << \"(\" << p.F << \", \" << p.S << \")\";",
			"}",
			"template<typename A> ostream& operator<< (ostream &cout, vector<A> const&v) {",
			"    cout << \"[\"; forn(i,(int)v.size()){ if (i) cout << \", \"; cout << v[i];} return cout << \"]\";",
			"}",
			"/* #endregion */",
			"",
			"const ll MOD = 1e9+7;",
			"// const ll MOD = 998244353;",
			"const ll INF = 1e18;",
			"",
			"",
			"",
            "",
            "int main() {",
			"    ios_base::sync_with_stdio(false);",
			"    cin.tie(NULL);",
			"    ",
            "    $1",
			"    ",
            "    return 0;",
            "}"
			"// python tester.py ${TM_FILENAME_BASE} input -v testpy.py"
        ],
        "description": "C++ Competitive Programming Template"
    }
}