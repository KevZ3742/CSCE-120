#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int*> v;

    for (size_t i = 0; i < 10; i++)
    {
        v.push_back(new int(i+1));
        cout << "capacity: " << v.capacity() << endl;
    }
    
    for (size_t i = 0; i < v.size(); i++)
    {
        cout << *(v.at(i)) << endl;
    }

    while (!v.empty())
    {
        delete v.at(0);
        v.erase(v.begin());
    }
}