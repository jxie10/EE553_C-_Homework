/*
* Author: Jiajiang Xie
*/
#include <iostream>
#include <cmath>
using namespace std;

class PrimeSolver {
private:
    const uint64_t n;
    const uint64_t WORDS;
    uint64_t* isPrime;
    //copy constructor, operator = not required
public:
    PrimeSolver(uint64_t n) : n(n), WORDS((n+63)/64), isPrime(new uint64_t[WORDS]){}
    ~PrimeSolver(){
        delete [] isPrime;
    }
    PrimeSolver(const PrimeSolver& orig) = delete;
    PrimeSolver& operator =(PrimeSolver copy) = delete;
    PrimeSolver(PrimeSolver&& orig) = delete;
    uint64_t countPrimes(){
        int count = 1; // 2 is prime
        // set all odd numbers true, even numbers false
        for (int i = 0; i < WORDS; i++) {
            isPrime[i] = 0xAAAAAAAAAAAAAAAALL; //   10101010 1010
        }
        const uint64_t lim = sqrt(n);
        for (uint64_t i = 3; i <= n; i+= 2) {
            if (isPrime[i>>6] & (1LL << (i & 63))) {
                count++;
                for (uint64_t j = i * i; j < n; j += 2*i) { // clear jth bit
                    isPrime[j >> 6] &= ~(1LL << (j & 63));
                }
            }
        }
        return count;
    }
};

int main() {
    PrimeSolver p(1000000000); // allocate the right number of 64-bit words
#if 0
    //You do not have to support copy constructor, but you should at least delete it
	PrimeSolver p2 = p; // this would give an error

	// same for operator =

	p2 = p; // just delete both copy constructor and operator = to show that you know how
#endif
    cout << p.countPrimes();
}


