#include <bits/stdc++.h>
using namespace std;

template <typename T = string>
class sep_iterator {
private:
    istream *in;
    string val;
    char sep = ',';

public:
    using iterator_category = input_iterator_tag;
    using value_type = T;
    using difference_type = size_t;
    using pointer = T *;
    using reference = T &;
    sep_iterator() : in(0) {}
    sep_iterator(istream &in, char sep = ',') : in(&in), sep(sep) {
        ++*this;
    }
    T operator*() const {
		istringstream ss(val);
		T value;
		ss >> value;
		return value;
	}
	sep_iterator & operator++() {
        if (in && !(getline(*in, val, sep)))
            in = 0;
        return *this;
    }
    bool operator!=(const sep_iterator& rhs) const {
		return in != rhs.in;
	}
};
    
template <>
string sep_iterator<string>::operator*() const {
	return val;
}

struct NWNode {
    static const string null_class;
    static const unordered_set<string> nulls;
    string val, unknown;
    unordered_map<string, NWNode *> children;
    ~NWNode() {
		for (auto & [name, node] : children)
            delete node;
    }
    NWNode(const string & s) : val(s) {}
    NWNode(istream & in) {
        string line;
        int unknown_id = 0;
        while (getline(in, line))
        {
            istringstream ss(line);
            NWNode *root = this;
            for (auto &w : vector<string>{sep_iterator<>(ss), sep_iterator<>()})
            {
                if (nulls.count(w)) {
                    if (!root->unknown.size())
                        root->unknown = null_class + "_" + to_string(unknown_id++);
                    w = root->unknown;
                }
                for (auto &c : w)
                    if (!isalnum(c))
                        c = '_';
                if (!root->children.count(w))
                    root->children[w] = new NWNode(w);
                root = root->children[w];
            }
        }
    }
    string to_str(bool isroot = true) const {
        if (!children.size())
            return val;
        string res = isroot ? "" : "(";
        for (auto &[name, subtree] : children) {
            if (res.size() > 1)
                res += ", ";
            res += subtree->to_str(false);
        }
        res += isroot ? ";" : ")" + val;
        return res;
    }
    operator string() const {
        return to_str();
    }
};

const string NWNode::null_class{"UNKNOWN"};
const unordered_set<string> NWNode::nulls{"Non", "NON", "null", "NULL", "unknown", ""};

int main(int argc, const char ** argv) {
    if (argc != 2 || !argv[1]) {
        cerr << "Please inpout your csv file name" << endl;
        return -1;
    }
    ifstream csv(argv[1]);
	if (!csv) {
        cerr << "Open file " << argv[1] << " failed" << endl;
        return -1;
    }
    cout << string(NWNode(csv)) << endl;
    csv.close();
}
