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


// Graph class to track the user's music journey
class Graph {
private:
    unordered_map<string, LinkedList> adjList; // Use LinkedList instead of list
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
        adjList[vertex]; // Automatically creates an empty LinkedList
    }

    void addEdge(const string& vertex1, const string& vertex2) {
        adjList[vertex1].addSong(Song(vertex2, "", "", 0)); // Add vertex2 as a song in vertex1's list
        adjList[vertex2].addSong(Song(vertex1, "", "", 0)); // Add vertex1 as a song in vertex2's list
    }

    void display() {
        for (unordered_map<string, LinkedList>::iterator it = adjList.begin(); it != adjList.end(); ++it) {
            cout << it->first << " -> ";
            it->second.display(); // Use the display method of LinkedList
        }
    }

    void resetJourney() {
        adjList.clear();
        lastSong.clear();
    }
};

// SongList class to manage a linked list of Songs
class SongList {
private:
    LinkedList songs;  // Store songs in a linked list
    BST songBST;  // Use BST for fast search
    Graph& userJourneyGraph;
    Stack recentlyRecommended;  // Stack to keep track of recently recommended songs
    Queue recommendations;  // Queue to manage the user's song recommendations

public:
    SongList(Graph& journeyGraph) : userJourneyGraph(journeyGraph) {}

    void addSong(string title, string artist, string vibe, int rating) {
        Song newSong(title, artist, vibe, rating);
        songs.addSong(newSong);  // Add song to the linked list
        songBST.insert(newSong);  // Insert song into the BST
    }

    // Recommend a random song
    void recommendSongs(int moodRating) {
        cout << "\n🎧 Recommended Songs 🎧\n";
        cout << "-----------------------------------\n";

        int songsRecommended = 0;

        // Make sure that at least 5 songs are recommended (or all available songs if fewer than 5)
        for (ListNode* current = songs.getHead(); current != 0 && songsRecommended < 5; current = current->next) {
            if (current->song.rating >= moodRating) {
                cout << "🎵 " << current->song.title << " by " << current->song.artist << "\n";
                userJourneyGraph.addSongToJourney(current->song.title);
                recentlyRecommended.push(current->song);  // Push to stack
                recommendations.enqueue(current->song);  // Enqueue to queue
                songsRecommended++;
            }
        }

        if (songsRecommended == 0) {
            cout << "🙁 No songs found matching this mood.\n";
        }

        cout << "-----------------------------------\n";
    }

    void searchSong(string query) {
        cout << "\n🔍 Searching for Songs...\n";
        cout << "-----------------------------------\n";

        // Convert query to lowercase for case-insensitive comparison
        for (size_t i = 0; i < query.size(); ++i) {
            query[i] = tolower(query[i]);
        }

        bool songFound = false;

        for (ListNode* current = songs.getHead(); current != 0; current = current->next) {
            string lowerSongTitle = current->song.getLowerTitle();

            // Check if the query is a substring of the song title
            if (lowerSongTitle.find(query) != string::npos) {
                cout << "🎵 Found: " << current->song.title << " by " << current->song.artist << "\n";
                userJourneyGraph.addSongToJourney(current->song.title);
                songFound = true;
            }
        }

        if (!songFound) {
            cout << "❌ No songs found with the phrase \"" << query << "\".\n";
        }

        cout << "-----------------------------------\n";
    }

    void searchArtist(string query) {
        cout << "\n🔍 Searching for Artists...\n";
        cout << "-----------------------------------\n";
        for (ListNode* current = songs.getHead(); current != 0; current = current->next) {
            if (current->song.artist.find(query) != string::npos) {
                cout << "🎵 " << current->song.title << " by " << current->song.artist << "\n";
                userJourneyGraph.addSongToJourney(current->song.title);
            }
        }
        cout << "-----------------------------------\n";
    }

    void trendingSong() {
        if (songs.getHead() == 0) {
            cout << "🙁 No songs available to pick a trending song.\n";
            return;
        }

        // Bubble sort the linked list before picking a trending song
        songs.bubbleSort();

        // The first song in the sorted list is the trending song
        cout << "\n🎵 Trending Song:\n";
        cout << "-----------------------------------\n";
        cout << "🎶 " << songs.getHead()->song.title << " by " << songs.getHead()->song.artist << " (" << songs.getHead()->song.vibe << ")\n";
        cout << "-----------------------------------\n";
    }

    void trendingArtist() {
        if (songs.getHead() == 0) {
            cout << "🙁 No songs available to calculate trending artists.\n";
            return;
        }

        unordered_map<string, int> artistCount;
        for (ListNode* current = songs.getHead(); current != 0; current = current->next) {
            artistCount[current->song.artist]++;
        }

        cout << "\n🎤 Trending Artists:\n";
        cout << "-----------------------------------\n";
        int counter = 0;
        for (unordered_map<string, int>::iterator it = artistCount.begin(); it != artistCount.end() && counter < 3; ++it) {
            cout << "🎶 " << it->first << " - " << it->second << " song(s) featured\n";
            counter++;
        }
        cout << "-----------------------------------\n";
    }

    // Function to load songs from a text file
    void loadSongsFromFile(const string& filename) {
        ifstream file(filename.c_str());
        if (!file) {
            cout << "❌ Could not open the file: " << filename << "\n";
            return;
        }

        string title, artist, vibe;
        int rating;
        while (getline(file, title, ',')) {
            getline(file, artist, ',');
            getline(file, vibe, ',');
            file >> rating;
            file.ignore();  // to ignore the newline after the rating
            addSong(title, artist, vibe, rating);
        }

        file.close();
    }
};

// Function to display a musical trivia fact
void displayTrivia() {
    const string trivia[] = {
        "🎵 The longest song ever recorded is 'The Rise and Fall of Bossanova' by PC III, lasting 13 hours!",
        "🎵 The Beatles hold the record for the most number-one hits on the Billboard Hot 100, with 20 songs!",
        "🎵 Michael Jackson's 'Thriller ' remains the best-selling album of all time, with over 66 million copies sold!",
        "🎵 Beethoven was almost completely deaf when he composed his famous Ninth Symphony.",
        "🎵 The shortest song ever recorded is 'You Suffer' by Napalm Death, lasting only 1.316 seconds.",
        "🎵 The highest note ever sung by a human is a G10, achieved by Georgia Brown.",
        "🎵 Elvis Presley is the best-selling solo music artist of all time.",
        "🎵 'Bohemian Rhapsody' by Queen has no chorus.",
        "🎵 Pink Floyd's 'The Dark Side of the Moon' stayed on the Billboard chart for 741 weeks.",
        "🎵 The first music video played on MTV was 'Video Killed the Radio Star' by The Buggles.",
        "🎵 Mozart wrote his first symphony at age 8.",
        "🎵 A piano has 230 strings.",
        "🎵 The first CD pressed in the U.S. was Bruce Springsteen’s 'Born in the USA.'",
        "🎵 The fastest rapper is Twista, who can rap 598 syllables in 55 seconds.",
        "🎵 The world's largest concert attendance was over 3.5 million people for Rod Stewart in 1994."
    };

    int triviaCount = sizeof(trivia) / sizeof(trivia[0]);
    int randomIndex = rand() % triviaCount;

    cout << "\n🎶 Musical Fact 🎶\n";
    cout << trivia[randomIndex] << "\n";
    cout << "-----------------------------------\n";
}

void displayHeader() {
    cout << "\n🎶 Welcome to Melody Mingle! 🎶\n";
    cout << "Where every vibe finds its tune! 🌟\n";
    cout << "-----------------------------------\n";
}


