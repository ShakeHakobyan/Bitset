# Bitset
A bitset is a data structure that stores multiple boolean values but takes lesser memory space as compared to other data structures
that can store a sequence of bits like a boolean array or boolean vector.


The class bitset represents a fixed-size sequence of N bits.
Bitsets can be manipulated by standard logic operators and constructed from strings and integers.
```c++
  int N;
  std::cin >> N;
  Bitset set(N);
```
A bitset stores bits (elements with only two possible values: 0 or 1, true or false, ...).
The class emulates an array of bool elements, but optimized for space allocation:
each element occupies only one bit by using array of type char instead of type bool.
Indexing of elements in a bitset is reverse (from right to left).
Let’s take an example, for bitset [01101001]. 0’s are at index 1, 2, 4, 7. And 1’s are at index 0, 3, 5, 6.

## Use cases
Bitsets are often used for modeling subsets of some set.
Let's say we have a set of all the digits {0, 1, 2, 3, ..., 9}.
Any subset of this set can be represented by a bitset of 10 bits.
For example subset {0, 2, 3, 8} could be represented like [0100001101].
**X**-th bit of the bitset is set to 1 if digit **X** is present in the subset,
and **X**-th bit is set to 0 if digit **X** is not present in the subset.
```
[0100001101] <-> {0, 2, 3, 8}
[0000100110] <-> {1, 2, 5}
[0111001100] <-> {2, 3, 6, 7, 8}
```

## 1. Main structure
Implement constructor and destructor:
```c++
#include <iostream>
#include <cstddef> // is used for type 'size_t'

class Bitset {
public:
  // creates a sequence of bits with size 'count', and fills the set with 0s
  explicit Bitset(size_t count);

  // delete allocated memory
  ~Bitset();

private:
  // variable for storing dynamic array of chars
  char *set;

  // fixed size of the sequence of bits
  size_t bitsSize;
};
```

***NOTE:*** constructor should not allocate more than `(count + 7) / 8` bytes of memory. :shushing_face:

### Example
```c++
  Bitset bset(12);
  // dynamic array of chars is created with size 2 and stored in a variable 'set'
  // set[1] -> [0000.0000]
  // set[0] -> [0000.0000]
  // which contains 16 bits, but we only use 12 of them
```

## 2. Get & Set
Add following functions:
```c++
  // return the bit with index in the set
  bool operator[](size_t index);

  // set the bit with index to 'value'
  void setValue(size_t index, bool value);
```
***NOTE:*** elements are indexed starting from 0, from right to left. :monocle_face:

### Example
```c++
  Bitset bset(12);
  // set[1] -> [0000.0000]
  // set[0] -> [0000.0000]
  bset.setValue(1, true);
  bset.setValue(3, true);
  bset.setValue(4, true);
  bset.setValue(9, true);
  // set[1] -> [0000.0010]
  // set[0] -> [0001.1010]
  bool flag = bset[3] // bset[3] will return true
```

## 3. Console output
Overload `opeartor<<` for writing into console using `std::cout`
```c++
  friend std::ostream &operator<<(std::ostream &os, const Bitset &set);
```

### Example
```c++
int main() {
  Bitset bset(12);
  bset.setValue(1, true);
  bset.setValue(3, true);
  bset.setValue(4, true);
  bset.setValue(9, true);
  std::cout << "Bitset: " << bset << '\n'; 
}
```

#### Console output:
```
Bitset: 001000011010
```

## 4. String constructor
Add a constructor so that Bitsets can be converted from strings:
```c++
  explicit Bitset(const std::string &str);
```

### Example
```c++
int main() {
  Bitset bset("01101110");
  std::cout << "Bitset before: " << bset << '\n';
  bset.setValue(0, true);
  bset.setValue(4, true);
  std::cout << "Bitset after:  " << bset << '\n';
}
```

#### Console output:
```
Bitset before: 01101110
Bitset after:  01111111
```

## 5. Copy & Move
Add member functions for construction and assignment:
```c++
  Bitset(const Bitset &set);
  Bitset(Bitset &&set);

  Bitset &operator=(const Bitset &set);
  Bitset &operator=(Bitset &&set);
```

### Example
```c++
int main() {
  Bitset bset1("00110");
  Bitset bset2(bset1);
  std::cout << "Bitset1: " << bset1 << '\n';
  std::cout << "Bitset2: " << bset2 << '\n';
  std::cout << '\n';
  bset1.setValue(0, true);
  std::cout << "Bitset1: " << bset1 << '\n';
  std::cout << "Bitset2: " << bset2 << '\n';
}
```

#### Console output:
```
Bitset1: 00110
Bitset2: 00110

Bitset1: 00111
Bitset2: 00110
```

## 6. Bitwise operators
Overload bitwise operators:
```c++
  friend Bitset operator&(const Bitset &lhs, const Bitset &rhs);
  friend Bitset operator|(const Bitset &lhs, const Bitset &rhs);
  friend Bitset operator^(const Bitset &lhs, const Bitset &rhs);
  
  Bitset operator~();
```

***NOTE:*** operators &, |, ^ are defined only for bitsets of the same size. :hushed:

### Example
```c++
int main() {
  Bitset a("1100");
  Bitset b("0101");
  std::cout << "a & b: " << (a & b) << '\n';
  std::cout << "a | b: " << (a | b) << '\n';
  std::cout << "a ^ b: " << (a ^ b) << '\n';
  std::cout << "~a: " << (~a) << '\n';
}
```

#### Console output:
```
  a & b: 0100
  a | b: 1101
  a ^ b: 1001
  ~a: 0011
```

## 7. Shift
Overload shift operators:
```c++
  friend Bitset operator<<(const Bitset &lhs, unsigned int shift);
  friend Bitset operator>>(const Bitset &rhs, unsigned int shift);
```

### Example
```c++
int main() {
  Bitset a("011010");
  std::cout << "a << 2: " << (a << 2) << '\n';
  std::cout << "a >> 2: " << (a >> 2) << '\n';
}
```

#### Console output:
```
a << 2: 101000
a >> 2: 000110
```

***NOTE:*** don't forget to test and debug everything you wrote. :relieved:	


## Attribution

The problem description in this README was originally written by  
[@Garnik645](https://github.com/Garnik645).

The bitset implementation is my own.
