
#include <bits/stdc++.h>

using namespace std;

// arr is sorted ascending, bs finds index of an occurence, or finds place to insert in sorted list
// if the return value is the size of the list, then value should be appended

namespace ascending {

int bs(vector<int>& arr, int x){

    int hi = arr.size();
    int lo = 0;

    int check = (hi + lo) / 2;

    while (hi > lo){
        if (arr[check] >= x){
            hi = check;
        }
        else if (arr[check] < x){
            lo = check + 1;
        }
        check = (hi + lo) / 2;
    }
    return check;

}

}

namespace descending {

int bs(vector<int>& arr, int x) {

    int hi = arr.size();
    int lo = 0;

    int check = (hi + lo) / 2 + (hi + lo) % 2;

    while (hi > lo){
        if (arr[check] >= x){
            lo = check;
        }
        else if (arr[check] < x){
            hi = check - 1;
        }
        check = (hi + lo) / 2  + (hi + lo) % 2;
    }

    return check;
}

}
