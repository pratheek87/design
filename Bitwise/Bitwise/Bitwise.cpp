
#include <iostream>

using namespace std;

void check_if_odd_number()
{
    int n1 = 14;

    //The '&' operator will return 0 if the number is even and return 1 if the number is odd
    // 1110 -- 14
    // 0001 -- 1 
    // ------- &
    //    0

    // 1111 -- 15
    // 0001 -- 1 
    // ------- &
    //    1

    cout << ((n1 & 1) ? "Odd" : "Even" ) << endl;
}


//check if numbers have same sign
void check_same_signs()
{
    int n1 = 14;
    int n2 = 5;
    int y = (n1 ^ n2);

    cout << y << endl;

    cout << ((n1 ^ n2) ? "same" : "different" ) << endl;
}

int main()
{
    check_same_signs();
}
