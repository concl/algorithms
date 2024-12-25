#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    
    int x, y, z;
    cin >> x >> y >> z;
    
    // Total number of people
    int n = x + y + z; 

    vector<vector<int>> people(n);

    for (int _ = 0; _ < n; _++) {
        int a, b, c;
        cin >> a >> b >> c;
        people[_] = {a, b, c};
    }

    sort(people.begin(), people.end(), [](const vector<int> f, const vector<int> s) {
        int a1 = f[0];
        int b1 = f[1];

        int a2 = s[0];
        int b2 = s[1];

        return a1 - b1 < a2 - b2;
    }); // Sort in ascending order of a - b, the difference between the number of gold coins and the number of silver coins
    
    // Partial solutions
    vector<ll> silver_and_bronze(z + 1);
    vector<ll> gold_and_bronze(z + 1);

    // Orderings
    multiset<vector<int>, function<bool(const vector<int>& f, const vector<int>& s)>> silver_and_bronze_ordering([](const vector<int>& f, const vector<int>& s) {
        int b1 = f[1];
        int c1 = f[2];

        int b2 = s[1];
        int c2 = s[2];

        return c1 - b1 < c2 - b2;
    });

    multiset<vector<int>, function<bool(const vector<int>& f, const vector<int>& s)>> gold_and_bronze_ordering([](const vector<int>& f, const vector<int>& s) {
        int a1 = f[0];
        int c1 = f[2];

        int a2 = s[0];
        int c2 = s[2];

        return c1 - a1 < c2 - a2;
    });

    // Add all the people from the beginning and end of the original list to their respective sets (These count as the first split for each side)
    for (int i = 0; i < y; i++) {
        silver_and_bronze_ordering.insert(people[i]);
        silver_and_bronze[0] += people[i][1];
    }

    for (int i = n - 1; i >= n - x; i--) {
        gold_and_bronze_ordering.insert(people[i]);
        gold_and_bronze[z] += people[i][0];
    }

    // Store the position to check the new person with to determine how to update the optimal solutions
    auto silver_and_bronze_pos = prev(silver_and_bronze_ordering.end());
    auto gold_and_bronze_pos = prev(gold_and_bronze_ordering.end());

    // Consider the next Z splits
    for (int i = 1; i <= z; i++) {

        // New person for silver and bronze
        vector<int> new_person1 = people[y + i - 1];
        silver_and_bronze_ordering.insert(new_person1);

        ll next_optimal_value1 = silver_and_bronze[i - 1];

        int b1 = new_person1[1];
        int c1 = new_person1[2];
        
        int b2 = (*silver_and_bronze_pos)[1];
        int c2 = (*silver_and_bronze_pos)[2];

        
        if (c1 - b1 < c2 - b2) {
            next_optimal_value1 -= b2;
            next_optimal_value1 += b1;
            next_optimal_value1 += c2;
            silver_and_bronze_pos--;
        } else {
            next_optimal_value1 += c1;
        }
        silver_and_bronze[i] = next_optimal_value1;

        // New person for gold and bronze
        vector<int> new_person2 = people[n - x - i];
        gold_and_bronze_ordering.insert(new_person2);

        ll next_optimal_value2 = gold_and_bronze[z - i + 1];

        int a1 = new_person2[0];
        c1 = new_person2[2];
        
        int a2 = (*gold_and_bronze_pos)[0];
        c2 = (*gold_and_bronze_pos)[2];

        
        if (c1 - a1 < c2 - a2) {
            next_optimal_value2 -= a2;
            next_optimal_value2 += a1;
            next_optimal_value2 += c2;
            gold_and_bronze_pos--;
        } else {
            next_optimal_value2 += c1;
        }
        gold_and_bronze[z - i] = next_optimal_value2;
    }

    ll output = 0;
    for (int i = 0; i <= z; i++) {
        output = max(output, silver_and_bronze[i] + gold_and_bronze[i]);
    }

    cout << output << endl;
    return 0;
}