#include <vector>
#include <string>
#include <iostream>

using namespace std;

template <typename T>
ostream& operator<<(ostream& outs, const vector<T>& a_vector)
{
    outs.put('[');
    char comma[3] = { '\0', ' ', '\0' };
    for (const auto& element : a_vector) {
        outs << comma << element;
        comma[0] = ',';
    }
    return outs << ']';
}
// [\0_\01,_\02,_\03,_\04]
int main()
{
    // c++11 initializer list syntax:
    vector<string> words1{ "the", "frogurt", "is", "also", "cursed" };
    cout << "words1: " << words1 << '\n';

    // words2 == words1
    vector<string> words2(words1.begin(), words1.end());
    cout << "words2: " << words2 << '\n';

    // words3 == words1
    vector<string> words3(words1);
    cout << "words3: " << words3 << '\n';

    // words4 is {"Mo", "Mo", "Mo", "Mo", "Mo"}
    vector<string> words4(5, "Mo");
    cout << "words4: " << words4 << '\n';

    cout << '\n' << "foreach vector" << endl;
    for(const auto & word:words1) {
        cout << ": " << word << endl;
    }

    cout << '\n' << "for-loop vector" << endl;
    for (vector<string>::iterator it = words1.begin(); it != words1.end(); ++it) {
        cout << ": " << *it << endl;
    }

    cout << '\n' << "vector[0]" << endl;
    cout << words1[0] << endl;
    cout << words1.at(0) << endl;

    cout << '\n' << "emplace()" << endl;
    words1.emplace(words1.begin(), "First");
    cout << words1 << endl;

    words1.emplace(words1.begin()+1, "appended");
    cout << words1 << endl;

    cout << '\n' << "emplace_back()" << endl;
    words1.emplace_back("last");
    cout << words1 << endl;

    cout << '\n' << "erase()" << endl;
    words1.erase(words1.begin());
    cout << words1 << endl;

    words1.erase(words1.begin()+1, words1.begin()+3);
    cout << words1 << endl;
    
    cout << '\n' << "swap()" << endl;
    cout << "words1: " << words1 << endl;
    cout << "words2: " << words2 << endl;
    cout << '\n' << "after swap()" << endl;
    words1.swap(words2);
    cout << "words1: " << words1 << endl;
    cout << "words2: " << words2 << endl;

    cout << '\n' << "another swap()" << endl;
    vector<int> a1{ 1, 2, 3 }, a2{ 4, 5 };

    auto it1 = std::next(a1.begin());
    auto it2 = std::next(a2.begin());

    int& ref1 = a1.front();
    int& ref2 = a2.front();

    cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
    a1.swap(a2);
    cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';

    // Note that after swap the iterators and references stay associated with their
    // original elements, e.g. it1 that pointed to an element in 'a1' with value 2
    // still points to the same element, though this element was moved into 'a2'.

    return 0;
}
