/*
	 Author: Jiajiang Xie
*/
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
string removeVowels(string str);

int main(){
    cout << "Please type in a string:" << '\n';
    string str,rev;
    getline(cin,str);
    rev.resize(str.length());
    reverse_copy(str.begin(),str.end(),rev.begin());
    cout << "The string backwards is :" << rev << "\n";
    if (str == rev){
        cout << "This string is a palindrome." <<'\n';
    }
    else{
        cout << "This string is NOT a palindrome." << "\n";
    }
    cout << "The string without vowels:" << removeVowels(str) << endl;
}

string removeVowels(string str){
    string vowels = "aeiouAEIOU";
    string s;
    for(int i = 0; i < str.length(); i++){
        if (vowels.find(str[i]) == str.npos){
            s += str[i];
        }
    }
    return s;
}

