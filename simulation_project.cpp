#include <iostream>
#include <queue>
#include <map>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
};

// Function to create a new node
Node* createNode(char ch, int freq, Node* left, Node* right) {
    Node* node = new Node();
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

// Comparison object for priority queue (min-heap)
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Function to generate codes
void generateCodes(Node* root, string code, map<char, string>& huffmanCode) {
    if (!root) return;

    // If leaf node
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = code;
    }

    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

int main() {
    string text;
    cout << "Enter text: ";
    getline(cin, text);

    map<char, int> freq;

    // Count frequency
    for (int i = 0; i < text.size(); i++) {
        freq[text[i]]++;
    }

    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Create leaf nodes
    for (map<char, int>::iterator it = freq.begin(); it != freq.end(); it++) {
        pq.push(createNode(it->first, it->second, NULL, NULL));
    }

    // Build Huffman Tree
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* newNode = createNode('\0', left->freq + right->freq, left, right);
        pq.push(newNode);
    }

    Node* root = pq.top();

    map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    cout << "\nHuffman Codes:\n";
    for (map<char, string>::iterator it = huffmanCode.begin(); it != huffmanCode.end(); it++) {
        cout << it->first << " : " << it->second << endl;
    }

    // Encode the input
    string encoded = "";
    for (int i = 0; i < text.size(); i++) {
        encoded += huffmanCode[text[i]];
    }

    cout << "\nEncoded Text: " << encoded << endl;

    return 0;
}

