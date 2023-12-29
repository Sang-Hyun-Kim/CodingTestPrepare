#include <iostream>
#include <deque>
#include <algorithm> // std::find
#include <utility>   // std::pair

int main() {
    // deque<pair<int, int>> 생성
    std::deque<std::pair<int, int>> myDeque = {
        {1, 2},
        {3, 4},
        {5, 6}
    };

    // 찾을 pair
    std::pair<int, int> targetPair = { 3, 4 };

    // std::find()를 사용하여 pair를 찾음
    auto it = std::find(myDeque.begin(), myDeque.end(), targetPair);

    // pair를 찾았는지 확인
    if (it != myDeque.end()) {
        std::cout << "Pair found at index: " << std::distance(myDeque.begin(), it) << std::endl;
    }
    else {
        std::cout << "Pair not found in the deque." << std::endl;
    }

    return 0;
}
