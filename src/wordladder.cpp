//Author: https://github.com/SamFangshan
#include <iostream>
#include <fstream>
#include "console.h"
#include "hashset.h"
#include "strlib.h"
#include "stack.h"
#include "queue.h"
#include "filelib.h"
#include "simpio.h"
using namespace std;

void printTheHeading();
void loadDict(HashSet<string>& dict);
bool readWords(string& word1, string& word2, HashSet<string>& dict);
bool getWords(string& word1, string& word2);
void findLadder(HashSet<string>& dict, string& word1, string& word2);
int oneStep(Queue<Stack<string> >& q, HashSet<string>& dict, string& word2, Stack<string>& st);

int main() {
    printTheHeading();

    HashSet<string> dict;
    loadDict(dict);

    string word1, word2;
    while (readWords(word1, word2, dict)) {
        findLadder(dict, word1, word2);
    }

    cout << "Have a nice day." << endl;
    return 0;
}

void printTheHeading() {
    cout << "Welcome to CS 106B/X Word Ladder!" << endl;
    cout << "Please give me two English words, and I will convert the" << endl;
    cout << "first into the second by modifying one letter at a time." << endl;
    cout << "" << endl;
}

void loadDict(HashSet<string>& dict) {
    ifstream dictFile;
    promptUserForFile(dictFile, "Dictionary file name: ");
    string word;
    while (dictFile >> word) {
        dict.add(word);
    }
}

bool readWords(string& word1, string& word2, HashSet<string>& dict) {
    if (!getWords(word1, word2)) {
        return false;
    }
    while (word1 == word2 || word1.length() != word2.length() || (!dict.contains(word1) || !dict.contains(word2))) {
        if (word1 == word2) {
            cout << "The two words must be different." << endl;
            if (!getWords(word1, word2)) {
                return false;
            }
        } else if (word1.length() != word2.length()) {
            cout << "The two words must be the same length." << endl;
            if (!getWords(word1, word2)) {
                return false;
            }
        } else {
            cout << "The two words must be found in the dictionary." << endl;
            if (!getWords(word1, word2)) {
                return false;
            }
        }
    }
    return true;
}

bool getWords(string& word1, string& word2) {
    cout << "" << endl;
    word1 = getLine("Word 1 (or Enter to quit): ");
    if (word1.length() == 0) {
        return false;
    }
    word1 = toLowerCase(word1);

    word2 = getLine("Word 2 (or Enter to quit): ");
    if (word2.length() == 0) {
        return false;
    }
    word2 = toLowerCase(word2);
    return true;
}

void findLadder(HashSet<string>& dict, string& word1, string& word2) {
    Stack<string> s1;
    s1.push(word1);
    Queue<Stack<string> > q;
    q.enqueue(s1);

    Stack<string> st;

    int con = 0;
    while (true) {
        con = oneStep(q, dict, word2, st);
        if (con == 1 || con == 2) {
            break;
        }
    }

    if (con == 2) {
        cout << "A ladder from " << word2 << " back to " << word1 << ":" << endl;
        while (!st.isEmpty()) {
            cout << st.pop() << " ";
        }
        cout << "" << endl;
    } else if (con == 1) {
        cout << "No word ladder found from " << word2 << " back to " << word1 << "." << endl;
    }

}

int oneStep(Queue<Stack<string> >& q, HashSet<string>& dict, string& word2, Stack<string>& st) {
    if (!q.isEmpty()) {
        Stack<string> s = q.dequeue();
        string w = s.peek();
        for (int i = 0; i < w.length(); i++) {
            for (int j = 0; j < 26; j++) {
                string temp = w;
                string str = "";
                str += (char)('a' + j);
                temp.replace(i, 1, str);
                if (w != temp && dict.contains(temp)) {
                    Stack<string> stack = s;
                    stack.push(temp);
                    if (temp == word2) {
                        st = stack;
                        return 2;
                    }
                    q.enqueue(stack);
                }
            }
        }
    } else {
        return 1;
    }

    return 0;
}
