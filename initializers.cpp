#include <iostream>

using namespace std;

class MyClass {
public:
  float x = 2.0f;//Java-style default initialization is new in C++11
  float y, z;

  MyClass() : y(3.0f), z(4.0f) { }//This is a delegated constructor, new in C++11

  //This is initialization from a braced list (i.e. {x, y, z})
  MyClass(initializer_list<float> lst) {
    auto it = lst.begin();//Automatically deduces that it is a std::initializer_list<float>::iterator
    x = *(it++);
    y = *(it++);
    z = *(it++);
  }
  MyClass(const MyClass&) = default;//Explicit defaulting
  MyClass(MyClass&& obj) {*this = obj;}//Move constructor
  
  MyClass& operator=(const MyClass&) = default;//Explicit defaulting

  //Move assignment operator
  MyClass& operator=(MyClass&& obj) {
    x = move(obj.x);
    y = move(obj.y);
    z = move(obj.z);
    obj.z = 10.0f;
  }

  friend ostream& operator<<(ostream& os, const MyClass& obj) {
    os << obj.x << " " << obj.y << " " << obj.z;
    return os;
  }
};

int main(int argc, char* argv[]) {
  cout << "Beginning initializer tests." << endl;

  MyClass obj1;
  cout << "Test 1: Default constructor with delegation" << endl;
  cout << obj1 << endl;
  cout << "Expected: " << endl << "2 3 4" << endl;

  MyClass obj2{1.0, 2.0, 3.0};
  cout << "Test 2: Constructor with initializer list (generalized initializer)" << endl;
  cout << obj2 << endl;
  cout << "Expected: " << endl << "1 2 3" << endl;

  obj1 = move(obj2);
  cout << "Test 3: the move operator" << endl;
  cout << obj1 << " " << obj2 << endl;
  cout << "Expected: " << endl << "1 2 3 1 2 10" << endl;

  cout << "Test 4: Reassignment post move operator" << endl;
  obj2.x = 5.0f;
  cout << obj1 << " " << obj2 << endl;
  cout << "Expected: " << endl << "1 2 3 5 2 10" << endl;

  obj2 = {4, 6, 8};
  cout << "Test 5: Reinitialization via initialization list" << endl;
  cout << obj1 << " " << obj2 << endl;
  cout << "Expected: " << endl << "1 2 3 4 6 8" << endl;

  cout << "Finished." << endl;
  return 0;
}
