#include <iostream>
#include "Bitset.h"

int main() {
    {
        Bitset b(12);
        b.setValue(1, true);
        b.setValue(3, true);
        b.setValue(4, true);
        b.setValue(9, true);
        std::cout << "Basic set/get:  " << b << '\n';
    }

    {
        Bitset b("01101110");
        std::cout << "From string:   " << b << '\n';
        b.setValue(0, true);
        b.setValue(4, true);
        std::cout << "After set:    " << b << '\n';
    }

    {
        Bitset a("00110");
        Bitset b(a);
        a.setValue(0, true);
        std::cout << "Copy src:     " << a << '\n';
        std::cout << "Copy dst:     " << b << '\n';
    }

    {
        Bitset a("1100");
        Bitset b("0101");
        std::cout << "a & b:        " << (a & b) << '\n';
        std::cout << "a | b:        " << (a | b) << '\n';
        std::cout << "a ^ b:        " << (a ^ b) << '\n';
        std::cout << "~a:           " << (~a) << '\n';
    }

    {
        Bitset a("1000110111011010");
        std::cout << "Shift left:   " << (a << 10) << '\n';
        std::cout << "Shift right:  " << (a >> 10) << '\n';
    }

    return 0;
}
