#include <vector>
#include <queue>
#include <iostream>

using namespace std;

void queue_test(void);
void vector_test(void);

int main(int argc, char const *argv[])
{
    vector_test();

    return 0;
}

void queue_test(void)
{
    std::queue<int> q;

    q.push(1);
    q.push(2);
    q.push(3);

    cout << q.front() << "\t" << q.back() << endl;

    q.pop();
    q.pop();
    q.push(4);
    q.push(5);
    q.push(6);
    q.pop();
    q.pop();
    q.push(7);

    cout << q.front() << "\t" << q.back() << endl;
}

void vector_test(void)
{
    std::vector<int> v;

    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(3);
    v.pop_back();
    v.emplace_back(4);

    // cout << v.front() << "\t" << v.back() << endl;
    for (auto x : v) { std::cout << x << "\t"; }
    std::cout << std::endl;

    // v.erase(v.begin());
    // v.erase(v.begin());
    // v.emplace_back(5);
    // v.emplace_back(6);

    v.resize(v.size() + 1);

    // cout << v.front() << "\t" << v.back() << endl;
    for (auto x : v) { std::cout << x << "\t"; }
    std::cout << std::endl;

}
