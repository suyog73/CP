// Suyog Patil

#include <bits/stdc++.h>
using namespace std;

int main()
{
    // Declaration of tuple
    tuple<int, char, string, vector<pair<int, int>>> tp1;

    // Initialization of tuple
    // Way 1
    tuple<int, string> tp2(2, "Suyog");

    // Way 2
    tuple<int, string> tp3 = make_tuple(3, "Zingur");

    // Way 3
    tuple<int, string> tp4;
    tp4 = make_tuple(4, "Langur");

    // Accessing tuple
    cout << "tp2\n";
    cout << get<0>(tp2) << " ";
    cout << get<1>(tp2) << "\n";
    cout << "tp3\n";
    cout << get<0>(tp3) << " ";
    cout << get<1>(tp3) << "\n";
    cout << "tp4\n";
    cout << get<0>(tp4) << " ";
    cout << get<1>(tp4) << "\n";

    // Swap tuple
    // To swap tuples, the datatype declared inside tuples should be same
    cout << "\nAfter swapping tp2 and tp3\n";

    tp2.swap(tp3);
    cout << "tp2\n";
    cout << get<0>(tp2) << " ";
    cout << get<1>(tp2) << "\n";
    cout << "tp3\n";
    cout << get<0>(tp3) << " ";
    cout << get<1>(tp3) << "\n";

    // Decomposing tuple
    cout << "\nDecomposing tuple using tie\n";
    int a;
    string s;

    tie(a, s) = tp2;
    cout << "a = " << a << "\ns = " << s << "\n";
    tie(ignore, s) = tp3;
    cout << "Using 'ignore' keyword to ignore 1st element of tuple\n";
    cout << s << "\n";

    // Concatenating tuples
    cout << "\nConcatenating tuple t1 and t2 \n";
    tuple<int, string> t1(2, "Suyog");
    tuple<pair<int, int>, char> t2({3, 5}, 'S');

    // tuple<int, string, pair<int, int>, char> t = tuple_cat(t1, t2);
    auto t = tuple_cat(t1, t2);

    cout << get<0>(t) << "\n";
    cout << get<1>(t) << "\n";
    cout << get<2>(t).first << " " << get<2>(t).second << "\n";
    cout << get<3>(t) << "\n";

    return 0;
}
