#include <bits/stdc++.h>
#include "LinearQueue.cpp"

using namespace std;


class PriorityQueue: public LinearQueue {
public:
   void insertionSort() {
      for (int i = front + 1; i <= rear; i++) {
         int temp = arr[i];
         int j = i - 1;
         while (j >= front && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
         }

         arr[j + 1] = temp;
      }
   }

   void push(int x) {
      LinearQueue::push(x);
      insertionSort();
   }

   void push_max_priority(int value) {
      if (isFull()) {
         cout << "Queue is full. Cannot push " << value << endl;
         return;
      }

      // If queue is empty, place the element at the start.
      if (isEmpty()) {
         front = 0;
         rear = 0;
         arr[rear] = value;
         return;
      }

      // Start from the end of the queue.
      int i;
      for (i = rear; i >= front; i--) {
         // If the new value is larger, shift the current element to the right.
         if (value > arr[i]) {
            arr[i + 1] = arr[i];
         } else {
            // Found the correct spot, stop shifting.
            break;
         }
      }

      // Insert the new value into its correct position.
      arr[i + 1] = value;
      rear++; // Increment the rear pointer.
   }

   void push_min_priority(int value) {
      if (isFull()) {
         cout << "Queue is full. Cannot push " << value << endl;
         return;
      }

      // If queue is empty, place the element at the start.
      if (isEmpty()) {
         front = 0;
         rear = 0;
         arr[rear] = value;
         return;
      }

      // Start from the end of the queue.
      int i;
      for (i = rear; i >= front; i--) {
         // If the new value is smaller, shift the current element to the right.
         if (value < arr[i]) {
            arr[i + 1] = arr[i];
         } else {
            // Found the correct spot, stop shifting.
            break;
         }
      }

      // Insert the new value into its correct position.
      arr[i + 1] = value;
      rear++; // Increment the rear pointer.
   }
};


int main() {
   PriorityQueue* pq = new PriorityQueue();
   pq->push_max_priority(10);
   pq->push_max_priority(0);
   pq->push_max_priority(30);
   pq->push_max_priority(20);
   pq->push_max_priority(50);
   while (! pq->isEmpty()) {
      cout << pq->peek() << endl;
      pq->pop();
   }
   return 0;
}