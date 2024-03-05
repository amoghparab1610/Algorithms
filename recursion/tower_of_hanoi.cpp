#include <iostream>

using namespace std;

void move(int k, int from, int to){
    cout << "Move " << k << " from " << from << " to " << to << "\n";
}

void tower_of_hanoi(int n, int start, int spare, int end){
    if (n == 1)
        move(n, start, end);
    else {
        tower_of_hanoi(n-1, start, end, spare);
        move(n, start, end);
        tower_of_hanoi(n-1, spare, start, end);
    }
}

int main(){
    tower_of_hanoi(3, 0, 1, 2);
    return 0;
}
