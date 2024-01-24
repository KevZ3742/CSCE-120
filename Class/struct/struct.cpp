#include <bits/stdc++.h>
using namespace std;

struct name{
    string firstName = "";
    string lastName = "";
};

int main(){
    name aName;

    //aName.firstName = "Kevin";
    //aName.lastName = "Zhang";

    aName = {"Kevin", "Zhang"};

    cout << aName.firstName << " " << aName.lastName << endl;
}