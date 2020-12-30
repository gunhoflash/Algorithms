#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int
        i,  // indexer
        len;

    long long
        min, max,
        divider_root,
        divider_unit,
        divider,
        n_square_nono; // answer

    vector<bool>
        is_square_nono;

    cin >> min >> max;
    len = max - min + 1;
    is_square_nono.resize(len, true);

    divider_root = 1;
    while (true) {
        divider_root++;
        divider_unit = divider_root * divider_root;
        divider = divider_unit;

        // end
        if (divider > max) break;

        // make the first divider
        if (divider < min) divider *= min / divider;
        if (divider < min) divider += divider_unit;

        // check all not 'square-nono'
        while (divider <= max) {
            is_square_nono[divider - min] = false;
            divider += divider_unit;
        }
    }

    // count the number of 'square-nono'
    n_square_nono = 0;
    for (i = 0; i < len; i++) {
        if (is_square_nono[i]) n_square_nono++;
    }

    // print the answer
    cout << n_square_nono;

    return 0;
}