
// Set this to compile to javascript, see README.md
// #define TARGET_EMSCRIPTEN

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <deque>


class Node {
    bool leaf;
    char c;
    int position, left, right, label;
    unsigned window;
public:
    Node(bool leaf, char c, int position, int left, int right, int label, unsigned window):
        leaf{leaf}, c{c}, position{position}, left{left}, right{right}, label{label}, window{window} {
            leaf = (left == -1 && right == -1);
    }
    int get_label() const { return label; }
    bool get_leaf() const { return leaf; }
    int getPosition() const { return position; }

    // all questions are in the form of "Is the nth charcter in
    // the sliding window c?"
    // if so, go right, else go left
    int get_next_decision(const std::deque<char>& slide_window) const {
        return (slide_window[window+position] == c) ? right : left;
    }
};

class DecisionTree {
    std::vector<Node> tree;
    unsigned window;
public:
    // load decision tree from file.
    // file format:
    //   first line: <node_count> <window width>
    //   rest: <character> <position> <left node> <right node> <output>
    void read_from_file(const std::string& fn) {
        std::ifstream is;
        is.open(fn, std::ifstream::in);
        int node_count;
        is >> node_count;
        is >> window;
        tree.reserve(node_count);
        std::string field;
        is.ignore(1);
        while (std::getline(is, field)) {
            std::stringstream ss(field);
            char c;
            int pos, leftIndex, rightIndex, label;
            ss.get(c);
            ss >> pos;
            ss >> leftIndex;
            ss >> rightIndex;
            bool leaf = false;
            if (leftIndex == -1 && rightIndex == -1) {// leaf node
                ss >> label;
                leaf = true;
            }
            else
                label = -1;
            tree.push_back(Node{leaf, c, pos, leftIndex, rightIndex, label, window});
        }
    }
    // traverse tree until a leaf node is reached
    // stop at 200 to avoid loops (error in the tree)
    // if no decision was made, keep the character as it is
    int classify(const std::deque<char>& slide_window) const {
        int index = 0, limit = 200;
        while (index < (int)tree.size()) {
            index = tree[index].get_next_decision(slide_window);
            if (tree[index].get_leaf())
                // leaf node is reached, no further decisions necessary
                return tree[index].get_label();
            if (limit-- < 1) return 0;
        }
        return 0;
    }
};

class Accentizer {
    std::map<char, DecisionTree> trees;
    // Hungarian accents in the order of the classifiers labeling
    std::map<char, std::vector<std::string>> accent_map = {
        {'a', {"a", "á"}},
        {'e', {"e", "é"}},
        {'i', {"i", "í"}},
        {'o', {"o", "ó", "ö", "ő"}},
        {'u', {"u", "ú", "ü", "ű"}},
    };
    // Hungarian uppercase accents in the order of the classifiers labeling
    std::map<char, std::vector<std::string>> accent_map_upper = {
        {'a', {"A", "Á"}},
        {'e', {"E", "É"}},
        {'i', {"I", "Í"}},
        {'o', {"O", "Ó", "Ö", "Ő"}},
        {'u', {"U", "Ú", "Ü", "Ű"}},
    };
    int window = 4;
public:
    void load(std::string basedir) {
        for (auto const& p: accent_map) {
            char c = p.first;
            std::string fname = basedir + "/" + c;
            trees[c] = DecisionTree();
            trees[c].read_from_file(fname);
        }
    }
    std::string accentize(std::string inp) {
        std::string input = std::string(window-1, '_') + " " + inp + " " + std::string(window-1, '_');

        int fullw = window*2+1;
        std::deque<char> slide_window;
        std::stringstream output;


        for (int i=0;i<fullw;i++) {
            slide_window.push_back(normalize(input[i]));
        }
        int input_pos = window;
        for(auto curit=input.begin()+fullw; curit != input.end(); curit++) {
            char midc = slide_window[window];
            if (accent_map.count(midc)) {
                int label = trees[midc].classify(slide_window);
                if (isupper(input[input_pos]))
                    output << accent_map_upper[midc][label];
                else
                    output << accent_map[midc][label];
            }
            else output << input[input_pos];
            input_pos++;

            char norm = normalize(*curit);
            slide_window.push_back(norm);
            slide_window.pop_front();
        }
        output << std::endl;
        return output.str();
    }

    // map characters to a small set of characters
    static char normalize(char c) {
        if (isspace(c)) return ' ';
        if (isdigit(c)) return '0';
        if (ispunct(c)) return '_';
        if (isalpha(c)) return tolower(c);
        return '*';
    }
};


#ifdef TARGET_EMSCRIPTEN

#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(accentizer) {
    emscripten::class_<Accentizer>("Accentizer")
        .constructor<>()
        .function("accentize", &Accentizer::accentize)
        .function("load", &Accentizer::load)
        ;
}

#else

int main(int argc, char* argv[]) {
    Accentizer ac;
    if (argc > 1) ac.load(argv[1]);
    else ac.load("tree");

    std::stringstream ss;
    for (std::string line; std::getline(std::cin, line);) {
        ss << line << '\n';
    }

    std::cout << ac.accentize(ss.str());
}

#endif
