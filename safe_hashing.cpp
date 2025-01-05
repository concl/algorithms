
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#define ll long long
#define uint unsigned int
#define elif else if
#define hash_table gp_hash_table
using namespace std;
using namespace __gnu_pbds;


struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }

    size_t operator()(const std::string &s) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        // Start with an offset (FNV offset basis + a bit of randomness)
        uint64_t result = 0xcbf29ce484222325ULL ^ FIXED_RANDOM; 
        // A typical FNV-like loop
        for (unsigned char c : s) {
            result ^= c;
            result *= 0x100000001b3ULL; // FNV prime
        }
        return static_cast<size_t>(result);
    }

    template <typename T>
    size_t operator()(const std::vector<T> &v) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        uint64_t result = 0xcbf29ce484222325ULL ^ FIXED_RANDOM; 
        // Combine the hash of each element
        for (auto &elem : v) {
            // Recursively call our custom hash on the element
            // This works for ints, strings, or even nested vectors
            uint64_t h_elem = (*this)(elem);
            result ^= h_elem + 0x9e3779b97f4a7c15ULL + (result << 6) + (result >> 2);
        }
        return static_cast<size_t>(result);
    }
};

// for tuples
namespace {
    template <class T>
    inline void hash_combine(std::size_t& seed, T const& v) {
        custom_hash hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
    struct HashValueImpl {
        static void apply(size_t& seed, Tuple const& tuple) {
            HashValueImpl<Tuple, Index - 1>::apply(seed, tuple);
            hash_combine(seed, std::get<Index>(tuple));
        }
    };

    template <class Tuple>
    struct HashValueImpl<Tuple, 0> {
        static void apply(size_t& seed, Tuple const& tuple) {
            hash_combine(seed, std::get<0>(tuple));
        }
    };
}


// combine hash values of all elements in tuple if all elements are numeric
struct tuple_hash {
    template <typename ... TT>
    size_t operator()(std::tuple<TT...> const& tt) const {
        size_t seed = 0;
        HashValueImpl<std::tuple<TT...>>::apply(seed, tt);
        return seed;
    }
};

// combine all hash values of all elements in tuple, works for both numeric and non-numeric elements that are hashable
// namespace std {
//     namespace {
//         template <class T>
//         inline void hash_combine(std::size_t& seed, T const& v) {
//             seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
//         }

//         template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
//         struct HashValueImpl {
//             static void apply(size_t& seed, Tuple const& tuple) {
//                 HashValueImpl<Tuple, Index - 1>::apply(seed, tuple);
//                 hash_combine(seed, std::get<Index>(tuple));
//             }
//         };

//         template <class Tuple>
//         struct HashValueImpl<Tuple, 0> {
//             static void apply(size_t& seed, Tuple const& tuple) {
//                 hash_combine(seed, std::get<0>(tuple));
//             }
//         };
//     }

//     template <typename ... TT>
//     struct hash<std::tuple<TT...>> {
//         size_t operator()(std::tuple<TT...> const& tt) const {
//             size_t seed = 0;
//             HashValueImpl<std::tuple<TT...>>::apply(seed, tt);
//             return seed;
//         }
//     };
// }

int main() {
    hash_table<long long, int, custom_hash> safe_hash_table;

    safe_hash_table[100] = 3;

    for (auto x : safe_hash_table) {
        cout << x.first << " " << x.second << endl;
    }

    return 0;
}
