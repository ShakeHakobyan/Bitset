#ifndef BITSET_BITSET_H
#define BITSET_BITSET_H
#include <cstddef>
#include <iosfwd>


class Bitset {
private:
    unsigned char* set = nullptr;
    std::size_t bit_count_ = 0;
    std::size_t byte_count_ = 0;

public:
    explicit Bitset(std::size_t count);
    explicit Bitset(const std::string &str);

    Bitset(const Bitset &other);
    Bitset(Bitset &&other) noexcept;

    ~Bitset();

    Bitset &operator=(const Bitset &other);
    Bitset &operator=(Bitset &&other) noexcept;

    bool operator[](std::size_t index) const;
    void setValue(std::size_t index, bool value) const;

    friend std::ostream &operator<<(std::ostream &os, const Bitset &set);
    friend Bitset operator&(const Bitset &lhs, const Bitset &rhs);
    friend Bitset operator|(const Bitset &lhs, const Bitset &rhs);
    friend Bitset operator^(const Bitset &lhs, const Bitset &rhs);
    friend Bitset operator<<(const Bitset &lhs, unsigned int shift);
    friend Bitset operator>>(const Bitset &rhs, unsigned int shift);

    Bitset operator~() const;
};



#endif //BITSET_BITSET_H