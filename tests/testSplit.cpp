#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    string s = "5 1 2 R C F";

    int timeSpent[3];
    char order[3];

    string temp;
    int i = 0;
    int x = 0;
    while(x < 3) {
        if(s[i] == ' ') {
            timeSpent[x] = stoi(temp);
            x++;
            s = s.substr(++i);
            i = 0;         
        } else {
            temp = s.substr(0, ++i);
        }
    }

    x = 0;

    cout << s << endl;

    while(x < 3) {
        if(s[i] == '\0') {
            order[x] = temp[0];
            break;
        }

        if(s[i] == ' ') {
            order[x] = temp[0];
            x++;
            s = s.substr(++i);
            i = 0;         
        } else {
            temp = s.substr(0, ++i);
        }
    }
    
    for(int i = 0; i < 3; ++i) {
        cout << timeSpent[i] << " ";
        cout << order[i] << endl;
    }

    cout << "curr: " << order[0] << endl;
}