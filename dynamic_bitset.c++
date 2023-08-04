
// this code is incomplete

#include <stdexcept>
#include <bits/stdc++.h>

using namespace std;

class DynamicBitset {
private:
    std::vector<uint64_t> data;
    size_t bitSize;

    // Helper function to calculate the required size in uint64_t units
    size_t calcSize(size_t bitCount) const {
        return (bitCount + 63) / 64;
    }

public:
    DynamicBitset() : bitSize(0) {}

    DynamicBitset(size_t size) 
        : data(calcSize(size), 0), bitSize(size) {}

    static DynamicBitset from_value(uint64_t value) {
        DynamicBitset db;
        db.data.push_back(value);
        db.bitSize = 64;
        return db;
    }

    struct Proxy {
        DynamicBitset& db;
        size_t index;
        
        Proxy(DynamicBitset& db, size_t index) : db(db), index(index) {}
        
        operator bool() const {
            return db.get(index);
        }
        
        Proxy& operator=(bool value) {
            db.set(index, value);
            return *this;
        }
    };
    
    Proxy operator[](size_t index) {
        return Proxy(*this, index);
    }

    bool operator[](size_t index) const {
        return get(index);
    }
    
    struct Hasher {
        std::size_t operator()(const DynamicBitset& db) const {
            std::size_t seed = db.data.size();
            for(auto& i : db.data) {
                seed ^= std::hash<uint64_t>{}(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
            }
            return seed;
        }
    };

    void resize(size_t newSize) {
        data.resize(calcSize(newSize), 0);
        bitSize = newSize;
    }

    bool get(size_t index) const {
        if (index >= bitSize) {
            throw std::out_of_range("Index out of range");
        }
        return (data[index >> 6] >> (index & 0x3F)) & 1;
    }

    void set(size_t index, bool value) {
        if (index >= bitSize) {
            throw std::out_of_range("Index out of range");
        }
        if (value) {
            data[index >> 6] |= (1ull << (index & 0x3F));
        } else {
            data[index >> 6] &= ~(1ull << (index & 0x3F));
        }
    }

    bool operator==(const DynamicBitset& other) const {
        if(bitSize != other.bitSize) {
            return false;
        }

        for(size_t i = 0; i < data.size(); ++i) {
            if(data[i] != other.data[i]) {
                return false;
            }
        }

        return true;
    }

    // Bitwise AND with DynamicBitset
    DynamicBitset& operator&=(const DynamicBitset& other) {
        size_t n = data.size();
        size_t m = other.data.size();
        size_t k = min(n,m);

        for (size_t i = 0; i < k; ++i) {
            data[i] &= other.data[i];
        }
        return *this;
    }

    // Bitwise OR with DynamicBitset
    DynamicBitset& operator|=(const DynamicBitset& other) {
        size_t n = data.size();
        size_t m = other.data.size();
        size_t k = min(n,m);

        for (size_t i = 0; i < k; ++i) {
            data[i] |= other.data[i];
        }
        return *this;
    }

    // Bitwise XOR with DynamicBitset
    DynamicBitset& operator^=(const DynamicBitset& other) {
        size_t n = data.size();
        size_t m = other.data.size();
        size_t k = min(n,m);

        for (size_t i = 0; i < k; ++i) {
            data[i] ^= other.data[i];
        }
        return *this;
    }

    // Bitwise NOT
    DynamicBitset operator~() const {
        DynamicBitset result(*this);
        for (auto& val : result.data) {
            val = ~val;
        }
        return result;
    }

    // Bitshifts
    DynamicBitset& operator<<=(size_t shift) {
        if (shift >= bitSize) {
            std::fill(data.begin(), data.end(), 0);
            return *this;
        }

        const size_t shiftBlocks = shift / 64;
        const size_t shiftBits = shift % 64;

        if (shiftBits == 0) {
            for (size_t i = data.size(); i-- > shiftBlocks; ) {
                data[i] = data[i - shiftBlocks];
            }
        } else {
            for (size_t i = data.size(); i-- > shiftBlocks + 1; ) {
                data[i] = (data[i - shiftBlocks] << shiftBits) | (data[i - shiftBlocks - 1] >> (64 - shiftBits));
            }
            data[shiftBlocks] = data[0] << shiftBits;
        }

        std::fill(data.begin(), data.begin() + shiftBlocks, 0);
        
        return *this;
    }

    DynamicBitset& operator>>=(size_t shift) {
        if (shift >= bitSize) {
            std::fill(data.begin(), data.end(), 0);
            return *this;
        }

        const size_t shiftBlocks = shift / 64;
        const size_t shiftBits = shift % 64;

        if (shiftBits == 0) {
            for (size_t i = 0; i < data.size() - shiftBlocks; ++i) {
                data[i] = data[i + shiftBlocks];
            }
        } else {
            for (size_t i = 0; i < data.size() - shiftBlocks - 1; ++i) {
                data[i] = (data[i + shiftBlocks] >> shiftBits) | (data[i + shiftBlocks + 1] << (64 - shiftBits));
            }
            data[data.size() - shiftBlocks - 1] = data.back() >> shiftBits;
        }

        std::fill(data.end() - shiftBlocks, data.end(), 0);
        
        return *this;
    }

    // Overloaded operators for int and long long
    DynamicBitset& operator&=(int value) {
        return *this &= DynamicBitset::from_value(value);
    }

    DynamicBitset& operator|=(int value) {
        return *this |= DynamicBitset::from_value(value);
    }

    DynamicBitset& operator^=(int value) {
        return *this ^= DynamicBitset::from_value(value);
    }

    DynamicBitset& operator&=(long long value) {
        return *this &= DynamicBitset::from_value(value);
    }

    DynamicBitset& operator|=(long long value) {
        return *this |= DynamicBitset::from_value(value);
    }

    DynamicBitset& operator^=(long long value) {
        return *this ^= DynamicBitset::from_value(value);
    }

    friend std::ostream& operator<<(std::ostream& os, const DynamicBitset& db) {
        for (size_t i = 0; i < db.bitSize; ++i) {
            os << db.get(i);
        }
        return os;
    }
};

// Specialize std::hash for DynamicBitset
namespace std {
    template <>
    struct hash<DynamicBitset> {
        std::size_t operator()(const DynamicBitset& db) const {
            return DynamicBitset::Hasher{}(db);
        }
    };
}

// Non-member bitwise operators
DynamicBitset operator&(DynamicBitset lhs, const DynamicBitset& rhs) {
    lhs &= rhs;
    return lhs;
}

DynamicBitset operator|(DynamicBitset lhs, const DynamicBitset& rhs) {
    lhs |= rhs;
    return lhs;
}

DynamicBitset operator^(DynamicBitset lhs, const DynamicBitset& rhs) {
    lhs ^= rhs;
    return lhs;
}

DynamicBitset operator&(DynamicBitset lhs, int rhs) {
    lhs &= rhs;
    return lhs;
}

DynamicBitset operator|(DynamicBitset lhs, int rhs) {
    lhs |= rhs;
    return lhs;
}

DynamicBitset operator^(DynamicBitset lhs, int rhs) {
    lhs ^= rhs;
    return lhs;
}

DynamicBitset operator&(DynamicBitset lhs, long long rhs) {
    lhs &= rhs;
    return lhs;
}

DynamicBitset operator|(DynamicBitset lhs, long long rhs) {
    lhs |= rhs;
    return lhs;
}

DynamicBitset operator^(DynamicBitset lhs, long long rhs) {
    lhs ^= rhs;
    return lhs;
}

// Non-member bitwise shift operators
DynamicBitset operator<<(DynamicBitset lhs, size_t shift) {
    lhs <<= shift;
    return lhs;
}

DynamicBitset operator>>(DynamicBitset lhs, size_t shift) {
    lhs >>= shift;
    return lhs;
}

int main() {
    const int size = 1e5;
    cout << size << endl;
    bitset<size> bitset1;
    bitset<size> bitset2;

    DynamicBitset db1(size);
    DynamicBitset db2(size);

    // populate the bitsets
    for (int i = 0; i < size; i++) {
        bitset1[i] = i % 2;
        bitset2[i] = (i + 1) % 2;
        db1[i] = i % 2;
        db2[i] = (i + 1) % 2;
    }
    // cout << bitset1 << endl;
    // cout << bitset2 << endl;

    // benchmark bitwise operations on bitsets
    auto start = std::chrono::high_resolution_clock::now();
    auto result_bitset = bitset1 & bitset2;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Bitset AND operation took: " << elapsed.count() << " s\n";
    // cout << result_bitset << endl;

    start = std::chrono::high_resolution_clock::now();
    result_bitset = bitset1 | bitset2;
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Bitset OR operation took: " << elapsed.count() << " s\n";
    // cout << result_bitset << endl;

    start = std::chrono::high_resolution_clock::now();
    result_bitset = bitset1 ^ bitset2;
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Bitset XOR operation took: " << elapsed.count() << " s\n";
    // cout << result_bitset << endl;

    start = std::chrono::high_resolution_clock::now();
    result_bitset = bitset1 ^ bitset1;
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Bitset XOR operation took: " << elapsed.count() << " s\n";
    // cout << result_bitset << endl;

    // benchmark bitwise operations on DynamicBitsets
    auto start2 = std::chrono::high_resolution_clock::now();
    auto result_db = db1 & db2;
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed2 = end2 - start2;
    std::cout << "DynamicBitset AND operation took: " << elapsed2.count() << " s\n";
    // cout << result_db << endl;

    start2 = std::chrono::high_resolution_clock::now();
    result_db = db1 | db2;
    end2 = std::chrono::high_resolution_clock::now();
    elapsed2 = end2 - start2;
    std::cout << "DynamicBitset OR operation took: " << elapsed2.count() << " s\n";

    start2 = std::chrono::high_resolution_clock::now();
    result_db = db1 ^ db2;
    end2 = std::chrono::high_resolution_clock::now();
    elapsed2 = end2 - start2;
    std::cout << "DynamicBitset XOR operation took: " << elapsed2.count() << " s\n";

    start2 = std::chrono::high_resolution_clock::now();
    result_db = db1 ^ db1;
    end2 = std::chrono::high_resolution_clock::now();
    elapsed2 = end2 - start2;
    std::cout << "DynamicBitset XOR operation took: " << elapsed2.count() << " s\n";

    // benchmark bitwise operations on bitsets over 1000 iterations average
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        result_bitset = bitset1 & bitset2;
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Bitset AND operation took: " << elapsed.count() / 1000 << " s\n";

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        result_bitset = bitset1 | bitset2;
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Bitset OR operation took: " << elapsed.count() / 1000 << " s\n";

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        result_bitset = bitset1 ^ bitset2;
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Bitset XOR operation took: " << elapsed.count() / 1000 << " s\n";

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        result_bitset = bitset1 ^ bitset1;
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Bitset XOR operation took: " << elapsed.count() / 1000 << " s\n";

    // benchmark bitwise operations on DynamicBitsets over 1000 iterations average
    start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        result_db = db1 & db2;
    }
    end2 = std::chrono::high_resolution_clock::now();
    elapsed2 = end2 - start2;
    std::cout << "DynamicBitset AND operation took: " << elapsed2.count() / 1000 << " s\n";

    start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        result_db = db1 | db2;
    }
    end2 = std::chrono::high_resolution_clock::now();
    elapsed2 = end2 - start2;
    std::cout << "DynamicBitset OR operation took: " << elapsed2.count() / 1000 << " s\n";

    start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        result_db = db1 ^ db2;
    }
    end2 = std::chrono::high_resolution_clock::now();
    elapsed2 = end2 - start2;
    std::cout << "DynamicBitset XOR operation took: " << elapsed2.count() / 1000 << " s\n";

    start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        result_db = db1 ^ db1;
    }
    end2 = std::chrono::high_resolution_clock::now();
    elapsed2 = end2 - start2;
    std::cout << "DynamicBitset XOR operation took: " << elapsed2.count() / 1000 << " s\n";

    // benchmark getting and setting bits over 1000 iterations average
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        bitset1[0] = 1;
        bitset1[1] = 0;
        bitset1[2] = 1;
        bitset1[3] = 0;
        bitset1[4] = 1;
        bitset1[5] = 0;
        bitset1[6] = 1;
        bitset1[7] = 0;
        bitset1[8] = 1;
        bitset1[9] = 0;
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Bitset setting bits operation took: " << elapsed.count() / 1000 << " s\n";

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        bitset1[0];
        bitset1[1];
        bitset1[2];
        bitset1[3];
        bitset1[4];
        bitset1[5];
        bitset1[6];
        bitset1[7];
        bitset1[8];
        bitset1[9];
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Bitset getting bits operation took: " << elapsed.count() / 1000 << " s\n";

    start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        db1[0] = 1;
        db1[1] = 0;
        db1[2] = 1;
        db1[3] = 0;
        db1[4] = 1;
        db1[5] = 0;
        db1[6] = 1;
        db1[7] = 0;
        db1[8] = 1;
        db1[9] = 0;
    }
    end2 = std::chrono::high_resolution_clock::now();
    elapsed2 = end2 - start2;
    std::cout << "DynamicBitset setting bits operation took: " << elapsed2.count() / 1000 << " s\n";

    start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        db1[0];
        db1[1];
        db1[2];
        db1[3];
        db1[4];
        db1[5];
        db1[6];
        db1[7];
        db1[8];
        db1[9];
    }
    end2 = std::chrono::high_resolution_clock::now();
    elapsed2 = end2 - start2;
    std::cout << "DynamicBitset getting bits operation took: " << elapsed2.count() / 1000 << " s\n";



    return 0;
}
