#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
using namespace std;

// Define the Song class
class Song {
public:
    string title;
    string artist;
    string vibe;
    int rating; // Average rating

    Song(string t, string a, string v, int r)
        : title(t), artist(a), vibe(v), rating(r) {}

    string getLowerTitle() const {
        string lowerTitle = title;
        transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);
        return lowerTitle;
    }
};


//Node Class for linked list
class ListNode {
public:
    Song song;
    ListNode* next;

    ListNode(Song s) : song(s), next(0) {}
};

// LinkedList class to manage a list of songs
class LinkedList {
private:
    ListNode* head;

public:
    LinkedList() : head(0) {}

    void addSong(Song song) {
        ListNode* newNode = new ListNode(song);
        newNode->next = head;
        head = newNode;
    }

    ListNode* getHead() const {
        return head; // Provide access to the head node
    }

    void display() {
        ListNode* current = head;
        while (current) {
            cout << "🎵 " << current->song.title << " by " << current->song.artist << " (Rating: " << current->song.rating << ")\n";
            current = current->next;
        }
    }

    //Bubble sort to sort the link list based on song ratings
    void bubbleSort(){
        if(!head) return;

        bool swapped;
        do{
            swapped=false;
            ListNode* current=head;
            while(current->next){
                 if (current->song.rating < current->next->song.rating) {
                 swap(current->song, current->next->song);
                 swapped = true;
            }
            current= current->next;
        }
      } while (swapped);
    }

};

// Stack class to manage a stack of songs
class Stack {
private:
    struct StackNode {
        Song song;
        StackNode* next;

        StackNode(Song s) : song(s), next(0) {}
    };

    StackNode* top;

public:
    Stack() : top(0) {}

    void push(Song song) {
        StackNode* newNode = new StackNode(song);
        newNode->next = top;
        top = newNode;
    }

    Song pop() {
        if (top == 0) {
            throw runtime_error("Stack is empty");
        }
        Song song = top->song;
        StackNode* temp = top;
        top = top->next;
        delete temp;
        return song;
    }

    bool isEmpty() {
        return top == 0;
    }
};

// Queue class to manage a queue of songs
class Queue {
private:
    struct QueueNode {
        Song song;
        QueueNode* next;

        QueueNode(Song s) : song(s), next(0) {}
    };

    QueueNode* front;
    QueueNode* rear;

public:
    Queue() : front(0), rear(0) {}

    void enqueue(Song song) {
        QueueNode* newNode = new QueueNode(song);
        if (rear == 0) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    Song dequeue() {
        if (front == 0) {
            throw runtime_error("Queue is empty");
        }
        Song song = front->song;
        QueueNode* temp = front;
        front = front->next;
        delete temp;
        return song;
    }

    bool isEmpty() {
        return front == 0;
    }
};

