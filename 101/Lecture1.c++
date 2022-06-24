#include "iostream"
#include "string"
using namespace std;

int main() {
    
    int buffer;
    string str = "hello world";
    string fname = "mohamed ";
    string lname = "abdelrazek";

    string *ptr;


    // TAKE INPUT
    // cin >> buffer;

    // STRING MANIPULATION
    // str = fname.append(lname);
    // int length = str.length();
    // we can slice them
    
    // Place Address
    ptr = &str;

    cout << *ptr << "\n";
    // cout << length << "\n";
    return 0;

}