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


// BSTNode class for the Binary Search Tree
class BSTNode {
public:
    Song song;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Song s) : song(s), left(nullptr), right(nullptr) {}
};

// BST class for managing the Binary Search Tree
class BST {
private:
    BSTNode* root;

public:
    BST() : root(nullptr) {}

    // Insert a song into the BST
    void insert(Song song) {
        string lowerTitle = song.getLowerTitle();
        song.title = lowerTitle;  // Ensure the song title is stored in lowercase
        root = insertRec(root, song);
    }

    // Search for a song by title in the BST
    BSTNode* search(string title) {
        string lowerTitle = toLowerCase(title);
        return searchRec(root, lowerTitle);
    }

private:
    // Helper function for insertion
    BSTNode* insertRec(BSTNode* node, Song song) {
        if (node == nullptr) {
            return new BSTNode(song);
        }

        if (song.title < node->song.title) {
            node->left = insertRec(node->left, song);
        } else if (song.title > node->song.title) {
            node->right = insertRec(node->right, song);
        }
        return node;
    }

    // Helper function for searching
    BSTNode* searchRec(BSTNode* node, string title) {
        if (node == nullptr || node->song.title == title) {
            return node;
        }

        if (title < node->song.title) {
            return searchRec(node->left, title);
        }
        return searchRec(node->right, title);
    }

    // Helper function to convert string to lowercase
    string toLowerCase(string str) {
        for (size_t i = 0; i < str.size(); ++i) {
            str[i] = tolower(str[i]);
        }
        return str;
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


// Graph class to track the user's music journey
class Graph {
private:
    unordered_map<string, list<string> > adjList;  // Add space between >>
    string lastSong; // Keeps track of the last song played

public:
    void addSongToJourney(const string& songTitle) {
        addVertex(songTitle);
        if (!lastSong.empty()) {
            addEdge(lastSong, songTitle);
        }
        lastSong = songTitle;
    }

    void addVertex(const string& vertex) {
        adjList[vertex];
    }

    void addEdge(const string& vertex1, const string& vertex2) {
        adjList[vertex1].push_back(vertex2);
        adjList[vertex2].push_back(vertex1);
    }

    void display() {
        for (unordered_map<string, list<string> >::iterator it = adjList.begin(); it != adjList.end(); ++it) {  // Add space between >>
            cout << it->first << " -> ";
            for (list<string>::iterator neighbor = it->second.begin(); neighbor != it->second.end(); ++neighbor) {
                cout << *neighbor << " ";
            }
            cout << endl;
        }
    }

    void resetJourney() {
        adjList.clear();
        lastSong.clear();
    }
};

