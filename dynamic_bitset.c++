#include <vector>
#include <stdexcept>
#include <iostream>
#include <bits/stdc++.h>

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
        if (bitSize != other.bitSize) {
            throw std::invalid_argument("Bitsets must be of the same size for bitwise operations.");
        }
        for (size_t i = 0; i < data.size(); ++i) {
            data[i] &= other.data[i];
        }
        return *this;
    }

    // Bitwise OR with DynamicBitset
    DynamicBitset& operator|=(const DynamicBitset& other) {
        if (bitSize != other.bitSize) {
            throw std::invalid_argument("Bitsets must be of the same size for bitwise operations.");
        }
        for (size_t i = 0; i < data.size(); ++i) {
            data[i] |= other.data[i];
        }
        return *this;
    }

    // Bitwise XOR with DynamicBitset
    DynamicBitset& operator^=(const DynamicBitset& other) {
        if (bitSize != other.bitSize) {
            throw std::invalid_argument("Bitsets must be of the same size for bitwise operations.");
        }
        for (size_t i = 0; i < data.size(); ++i) {
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

int main() {
    DynamicBitset db = DynamicBitset::from_value(255);
    std::cout << db << std::endl;

    std::unordered_map<DynamicBitset,int> brother;

    brother.insert({db,9});

    std::cout << brother[db];

    return 0;
}
