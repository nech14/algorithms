

#include <iostream>
#include <map>
#include <chrono>
#include <string>
#include <cmath>

std::string test(int n);

int main()
{
    int n = 10000000;

   std::string answer = test(n);

   std::cout << answer;
}

std::string test(int n) {

    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds;
    std::string answer = "";

    std::map <int, int> phoneBook;

    int l = 0;

    for (int i = 1; i <= n; i*=10) {
        for (int j = l; j <= i; j++) {
            phoneBook.insert(std::make_pair(i+j, i));
        }

        end = std::chrono::steady_clock::now();
        elapsed_seconds = end - start;

        answer += std::to_string(double(elapsed_seconds.count())) + ' ' + std::to_string(sizeof(int) * i/5) + ' ';
        l = i;
    }

    return answer;
}
