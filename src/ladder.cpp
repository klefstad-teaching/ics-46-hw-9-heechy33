#include <iostream>
#include <fstream>
#include <vector>
#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << "Error " << msg << word1 << ", " << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (abs((int)str1.length() - (int)str2.length()) > d) {
        return false;
    }
    vector<vector<int>> dp(str1.length() + 1, vector<int>(str2.length() + 1, 0));
    for (int j = 0; j <= str2.length(); j++) {
        dp[str1.length()][j] = str2.length() - j;
    }
    for (int i = 0; i <= str1.length(); i++) {
        dp[i][str2.length()] = str1.length() - i;
    }
    for (int i = str1.length() - 1; i >= 0; i--) {
        for (int j = str2.length() - 1; j >= 0; j--) {
            if (str1[i] == str2[j]) {
                dp[i][j] = dp[i + 1][j + 1];
            } else {
                dp[i][j] = 1 + min(dp[i + 1][j], min(dp[i][j + 1], dp[i + 1][j + 1]));
            }
        }
    }
    return dp[0][0] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        error(begin_word, end_word, "start and end is same");
        return {};
    }
    queue<vector<string>> queue_ladder;
    queue_ladder.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);
    while (!queue_ladder.empty()) {
        vector<string> ladder = queue_ladder.front();
        queue_ladder.pop();
        string last_word = ladder.back();

        for (auto word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) {
                        return new_ladder;
                    }
                    queue_ladder.push(new_ladder);
 
                }

            }
        }
    }
    return {};



}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        error("", "", "can't open file");
    }
    string word;
    while (getline(file, word)) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i] << " ";
    }
}
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;

    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
