#include <iostream>
using namespace std;

class Office {
    public:
        Office();
        Office(string type);

        string getType();

    private:
        string type;
};

Office::Office() {
    type = "none";
}

Office::Office(string type) {
    this->type = type;
}

string Office::getType() {
    return type;
}

int main(int argc, char** argv) {
    Office *registrar = new Office("registrar");
    Office *cashier = new Office("cashier");
    Office *finaid = new Office("financial aid");

    int size = 3;
    &Office* array;
    array = new &Office[size];

    for(int i = 0; i < size; ++i) {
        cout << "Office " << i << ": " << array[i]->getType() << endl;
    }
}