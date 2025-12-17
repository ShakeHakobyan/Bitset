#include "Bitset.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

Bitset::Bitset(const std::size_t count)
    : bit_count_(count), byte_count_((count + 7) / 8) {
    set = new unsigned char[byte_count_]();
}

Bitset::Bitset(const std::string &str)
    : bit_count_(str.size()), byte_count_((str.size() + 7) / 8) {
    set = new unsigned char[byte_count_]();
    for (std::size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '1') {
            const std::size_t index = str.size() - 1 - i;
            const std::size_t byte_index = index / 8;
            const std::size_t bit_index  = index % 8;
            set[byte_index] |= (1 << bit_index);
        } else if (str[i] != '0') {
            throw std::invalid_argument("Bitset string must contain only '0' or '1'");
        }
    }
}

Bitset::Bitset(const Bitset &other)
    : bit_count_(other.bit_count_), byte_count_(other.byte_count_) {
    set = new unsigned char[byte_count_];
    std::copy_n(other.set, byte_count_, set);
}

Bitset::Bitset(Bitset &&other) noexcept
    : set(other.set), bit_count_(other.bit_count_), byte_count_(other.byte_count_) {
    other.set = nullptr;
    other.bit_count_ = 0;
    other.byte_count_ = 0;
}

Bitset::~Bitset() {
    delete[] set;
}

Bitset& Bitset::operator=(const Bitset& other) {
    if (this == &other) return *this;

    delete[] set;

    bit_count_ = other.bit_count_;
    byte_count_ = other.byte_count_;
    set = new unsigned char[byte_count_];
    std::copy_n(other.set, byte_count_, set);

    return *this;
}

Bitset &Bitset::operator=(Bitset &&other) noexcept {
    if (this == &other) return *this;

    delete[] set;
    set = other.set;
    bit_count_ = other.bit_count_;
    byte_count_ = other.byte_count_;
    other.set = nullptr;
    other.bit_count_ = 0;
    other.byte_count_ = 0;
    return *this;
}

bool Bitset::operator[](const std::size_t index) const {
    if (index >= bit_count_) throw std::out_of_range("Bitset index out of range");
    const std::size_t byte_index = index / 8;
    const std::size_t bit_index  = index % 8;
    return (set[byte_index] >> bit_index) & 1;
}

void Bitset::setValue(const std::size_t index, const bool value) const {
    if (index >= bit_count_) throw std::out_of_range("Bitset index out of range");
    const std::size_t byte_index = index / 8;
    const std::size_t bit_index  = index % 8;

    if (value)
        set[byte_index] |= (1 << bit_index);
    else
        set[byte_index] &= ~(1 << bit_index);
}

Bitset Bitset::operator~() const {
    Bitset result(bit_count_);
    for ( std::size_t i = 0; i < bit_count_; ++i) {
        result.set[i] = ~set[i];
    }
    return result;
}

std::ostream &operator<<(std::ostream &os, const Bitset &b) {
    for (std::size_t i = 0; i < b.bit_count_; ++i) {
        const std::size_t index = b.bit_count_ - 1 - i;
        os.put(b[index] ? '1' : '0');
    }
    return os;
}

Bitset operator&(const Bitset &lhs, const Bitset &rhs) {
    if (lhs.bit_count_ != rhs.bit_count_) {
        throw std::invalid_argument("Bitset sizes must match");
    }
    Bitset result(lhs.bit_count_);
    for (std::size_t i = 0; i < lhs.byte_count_; ++i) {
        result.set[i] = lhs.set[i] & rhs.set[i];
    }
    return result;
}

Bitset operator|(const Bitset &lhs, const Bitset &rhs) {
    if (lhs.bit_count_ != rhs.bit_count_) {
        throw std::invalid_argument("Bitset sizes must match");
    }
    Bitset result(lhs.bit_count_);
    for (std::size_t i = 0; i < lhs.byte_count_; ++i) {
        result.set[i] = lhs.set[i] | rhs.set[i];
    }
    return result;
}

Bitset operator^(const Bitset &lhs, const Bitset &rhs) {
    if (lhs.bit_count_ != rhs.bit_count_) {
        throw std::invalid_argument("Bitset sizes must match");
    }
    Bitset result(lhs.bit_count_);
    for (std::size_t i = 0; i < lhs.byte_count_; ++i) {
        result.set[i] = lhs.set[i] ^ rhs.set[i];
    }
    return result;
}

Bitset operator<<(const Bitset &lhs, const unsigned int shift) {
    Bitset result(lhs.bit_count_);
    if (shift >= lhs.bit_count_) {
        return result;
    }
    for (std::size_t i = shift; i < lhs.bit_count_; ++i) {
        if (lhs[i - shift])
            result.setValue(i, true);
    }
    return result;
}

Bitset operator>>(const Bitset &rhs, const unsigned int shift) {
    Bitset result(rhs.bit_count_);
    if (shift >= rhs.bit_count_) {
        return result;
    }
    for (std::size_t i = 0; i + shift < rhs.bit_count_; ++i) {
        if (rhs[i + shift])
            result.setValue(i, true);
    }
    return result;
}