#include <iostream>
using namespace std;

#define MAX 100

class MinHeap {
    int arr[MAX];
    int size;

public:
    MinHeap() {
        size = 0;
    }

    // Insert element into heap
    void insert(int value) {
        size++;
        int i = size;

        // Heapify up
        while (i > 1 && arr[i / 2] > value) {
            arr[i] = arr[i / 2];
            i = i / 2;
        }
        arr[i] = value;
    }

    // Delete minimum element (root)
    int deleteMin() {
        if (size == 0) {
            cout << "Heap is empty\n";
            return -1;
        }

        int min = arr[1];
        int last = arr[size--];

        int i = 1, child;

        // Heapify down
        while (i * 2 <= size) {
            child = i * 2;

            if (child + 1 <= size && arr[child + 1] < arr[child])
                child++;

            if (last <= arr[child])
                break;

            arr[i] = arr[child];
            i = child;
        }

        arr[i] = last;
        return min;
    }

    // Display heap
    void display() {
        for (int i = 1; i <= size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};

int main() {
    MinHeap h;

    h.insert(30);
    h.insert(10);
    h.insert(20);
    h.insert(5);

    cout << "Heap elements: ";
    h.display();

    cout << "Deleted min: " << h.deleteMin() << endl;

    cout << "Heap after deletion: ";
    h.display();

    return 0;
}