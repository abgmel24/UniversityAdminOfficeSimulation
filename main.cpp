#include "Configuration.h"
#include "ServiceCenter.h"
#include <iostream>

using namespace std;
int main(int argc, char** argv) {
    if(argc != 2) {
        cout << "Wrong amount of arguments" << endl;
        return 1;
    }

    Configuration *config = new Configuration(argv[1]);
    ServiceCenter *center = new ServiceCenter(config);
    center->service();
}