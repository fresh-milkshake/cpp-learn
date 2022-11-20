
// includes for the STL algorithms
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T>
void print(T& t)
{
    for (int i = 0; i < t.size(); i++)
        cout << t[i] << " ";
    cout << endl;
}

void print(const char* s)
{
    cout << s << endl;
}

vector<int> initial_vector(int size) {
    vector<int> v;
    for (int i = 0; i < size; ++i)
        v.push_back(i);
    return v;
}

void print_title(const char* title) {
    cout << endl << string(10, '-') << " " << title << " " << string(10, '-') << endl;
}

void test_algorithms() {
    print("test_algorithms - begin");

    vector<int> v = initial_vector(10);

    // reverse - reverses the order of the elements in the range [first,last)
    print_title("reverse");
    print(v);
    reverse(begin(v), end(v));
    print(v);

    // rotate - rotates the order of the elements in the range [first,last), in such a way that the element 
    // pointed by middle becomes the new first element
    print_title("rotate(3)");
    print(v);
    rotate(v.begin(), v.begin() + 3, v.end());
    print(v);

    // random_shuffle - rearranges the elements in the range [first,last) randomly
    print_title("random_shuffle");
    print(v);
    random_shuffle(v.begin(), v.end());
    print(v);

    // sort - sorts the elements in the range [first,last) into ascending order
    print_title("sort");
    print(v);
    sort(v.begin(), v.end());
    print(v);

    // stable_sort - sorts the elements in the range [first,last) into ascending order,
    // preserving the relative order of the elements with equivalent values
    print_title("stable_sort");
    print(v);
    stable_sort(v.begin(), v.end());
    print(v);

    // partial_sort - rearranges the elements in the range [first,last) in such a way that the elements
    // from first to middle are the smallest elements in the range [first,last) and are sorted in ascending order
    print_title("partial_sort(3)");
    print(v);
    partial_sort(v.begin(), v.begin() + 3, v.end());
    print(v);

    // nth_element - rearranges the elements in the range [first,last) in such a way that the element at the nth position
    // is the element that would be in that position in a sorted sequence
    print_title("nth_element(3)");
    print(v);
    nth_element(v.begin(), v.begin() + 3, v.end());
    print(v);

    // lower_bound - returns an iterator pointing to the first element in the range [first,last) which does not compare
    // less than val
    print_title("lower_bound");
    print(v);
    cout << "lower_bound(3) = " << *lower_bound(v.begin(), v.end(), 3) << endl;

    // upper_bound - returns an iterator pointing to the first element in the range [first,last) which compares greater than val
    print_title("upper_bound");
    print(v);
    cout << "upper_bound(3) = " << *upper_bound(v.begin(), v.end(), 3) << endl;

    // binary_search - searches the sorted range [first,last) for an element equivalent to val
    print_title("binary_search");
    print(v);
    cout << "binary_search(3) = (true/false)  " << binary_search(v.begin(), v.end(), 3) << endl;

    // equal_range - returns the bounds of a range that includes all the elements in the range [first,last) which have a value equivalent to val
    print_title("equal_range");
    print(v);
    auto range = equal_range(v.begin(), v.end(), 3);
    cout << "equal_range(3) = " << *range.first << " " << *range.second << endl;

    // merge - merges two sorted ranges [first1,last1) and [first2,last2) into one sorted range beginning at d_first
    print_title("merge");
    vector<int> v1 = initial_vector(5);
    vector<int> v2 = initial_vector(5);
    print(v1);
    print(v2);
    vector<int> v3(10);
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
    print(v3);

    // inplace_merge - merges two sorted ranges [first,middle) and [middle,last) into one sorted range [first,last)
    print_title("inplace_merge");
    print(v3);
    inplace_merge(v3.begin(), v3.begin() + 5, v3.end());
    print(v3);

    // includes - tests whether the sorted range [first1,last1) includes the sorted range [first2,last2)
    print_title("includes");
    print(v1);
    print(v2);
    cout << "includes = " << includes(v1.begin(), v1.end(), v2.begin(), v2.end()) << endl;

    // set_union - computes the union of the two sorted ranges [first1,last1) and [first2,last2) and stores the result in the range beginning at d_first
    print_title("set_union");
    print(v1);
    print(v2);
    vector<int> v4(10);
    set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v4.begin());
    print(v4);


}

int main() {
    test_algorithms();
    return 0;
}
