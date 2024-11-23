#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <iterator>
#include <numeric>

using namespace std;

constexpr int MAX_N = 1'000'000;  // C++17 digit separator

// Generate prime numbers using Sieve of Eratosthenes
vector<int> sieve_of_eratosthenes(int limit) {
    vector<bool> is_prime(limit + 1, true);
    
    // Using iterators and numeric algorithms from STL
    for (auto p = begin(is_prime) + 2; p != end(is_prime); ++p) {
        if (*p) {
            for (auto i = begin(is_prime) + distance(begin(is_prime), p) * distance(begin(is_prime), p); 
                 i < end(is_prime); 
                 advance(i, distance(begin(is_prime), p))) {
                *i = false;
            }
        }
    }
    
    vector<int> primes;
    // Using STL algorithms to populate prime numbers
    for (int i = 2; i < limit; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

// Check if a number is circular prime
bool is_circular_prime(int n, const set<int>& prime_set) {
    string num = to_string(n);
    const size_t len = num.length();
    
    // Using STL algorithms for string rotation
    for (size_t i = 0; i < len - 1; ++i) {
        rotate(begin(num), begin(num) + 1, end(num));
        if (prime_set.find(stoi(num)) == end(prime_set)) {
            return false;
        }
    }
    return true;
}

int main() {
    cout << "Starting Circular Primes calculation...\n";
    
    // Generate prime numbers
    auto primes = sieve_of_eratosthenes(MAX_N);
    
    // Convert vector to set using iterator range constructor
    set<int> prime_set(begin(primes), end(primes));
    
    // Using STL algorithms to count circular primes
    auto circular_count = count_if(begin(primes), end(primes),
        [&prime_set](int n) { 
            if (is_circular_prime(n, prime_set)) {
                cout << "Found circular prime: " << n << '\n';
                return true;
            }
            return false;
        });
    
    cout << "\nTotal number of circular primes found: " << circular_count << '\n';
    
    return 0;
}