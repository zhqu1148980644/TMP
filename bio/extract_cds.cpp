#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <utility>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <stdlib.h>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::string;
using std::vector;
using std::map;
using std::set;

using std::stoi;


const char * CDS = "CDS";
const char * EXON = "exon";
const char * IDST = "ID=";
const char * IDST1 = "Parent=";
const char IDED = ';';

const char ANNO = '#';
const char PLUS = '+';
const char MINUS = '-';
const char CHROM = '>';

const char * VERSION = "0.1";

const size_t MINUS_FALG = 0;


const char * EX_TAG = "--ex_tag";
const char * EX_POS = "--ex_pos";
const char * REP_POS = "--rep_pos";
const char * EX_LEN = "--ex_len";






class GFF3
{


};

class GTF
{



};


class BED
{





};



inline void show_error()
{
    cerr << "Error!!!" << endl;
    cerr << "Version : " << VERSION << endl;
    cerr << "Use the command for usage information:" << endl;
    cerr << "a.out --help" << endl;
    cerr << "Caution:" << endl;
    cerr  << "\tBe cautoius with the file's format which you choosed." << endl;
    cerr  << "\tThere could be unexpected error may happen due to the non-standard file format." << endl;
    exit(EXIT_FAILURE);
}

void extract_seq_bytag(const int &, char **);
void extract_seq_bypos(const int &, char **);
void replace_seq_bypos(const int &, char **);
void extract_length(const int &, char **);



bool read_gff(istream &, map<string, vector<size_t >> &, string &);
bool read_genome(istream &, map<string, string> &);
bool read_genome(istream &, map<string, string> &, string &);
bool read_include(istream &, set<string> &);
bool write_cds(ostream &, map<string, string> &, map<string, vector<size_t >> &, set<string> &);
bool write_bed(ostream &, map<string, string> &, map<string, vector<size_t >> &, set<string> &);
void fetch_position(string &, vector<size_t > &);
void transcribe(string &);

int main(int argc, char ** argv) {
    if (argc == 1)
        show_error();
    if (argc == 2 && !strcmp(argv[1], "--help"))
    {
        cerr << "Usage:" << endl;
        cerr << "a.out genome.gff genome.fa [request_gene_list]" << endl;
    }
    else if (!strcmp(argv[1], EX_TAG))
    {
        extract_seq_bytag(argc, argv);
    }
    else if (!strcmp(argv[1], EX_POS))
    {
        extract_seq_bypos(argc, argv);
    }
    else if (!strcmp(argv[1], REP_POS))
    {
        replace_seq_bypos(argc, argv);
    }
    else if (!strcmp(argv[1], EX_LEN))
    {
        extract_length(argc, argv);
    }
    else
    {
        show_error();
    }
}

void extract_seq_bytag(const int & argc, char ** argv)
{
    if (argc < 5 || argc > 6)
        show_error();
    string tag(argv[2]);

    ifstream fa;
    ifstream gff;
    ifstream include;
    gff.open(argv[3]);
    fa.open(argv[4]);
    if (argc == 6)
        include.open(argv[5]);
    if (!fa || !gff || (argc == 6 && !include))
    {
        cerr << "Open file failure!";
        show_error();
    }
    map<string, vector<size_t >> genes;
    map<string, string> genome;
    set<string> gene_set;
    read_gff(gff, genes, tag);
    read_genome(fa, genome);
    if (include.is_open())
        read_include(include, gene_set);

    //write_cds(cout , genome, genes, gene_set);
    write_bed(cout, genome, genes, gene_set);
}

void extract_seq_bypos(const int & argc, char ** argv)
{
    if (argc != 6)
        show_error();
    ifstream fa(argv[2]);
    string chr(argv[3]);
    vector<size_t> pos_vec;
    string loc_string(argv[4]);
    string strand(argv[5]);

    fetch_position(loc_string, pos_vec);
    if ((pos_vec.size() % 2) != 0 || !fa.is_open())
        show_error();

    map<string, string> genome;
    read_genome(fa, genome, chr);
    if (genome.find(chr) == genome.end())
        show_error();

    for (auto it = pos_vec.begin(); it != pos_vec.end(); it+=2)
    {
        if (*it > *(it + 1))
            show_error();
        cout << '>' << *it << ':' << *(it + 1) << endl;
        string && substr = genome[chr].substr(*it - 1, *(it + 1) - *it + 1);
        if (strand == "+")
            cout << substr << endl;
        else
        {
            transcribe(substr);
            for_each(substr.rbegin(), substr.rend(), [] (const char & ch) {cout << ch;});
            cout << endl;
        }
    }
}


void replace_seq_bypos(const int & argc, char ** argv)
{
    if (argc != 5)
        show_error();
    ifstream fa(argv[1]);
    string chr(argv[2]);
    vector<size_t> pos_vec;
    string loc_string(argv[3]);

    fetch_position(loc_string, pos_vec);
    if (pos_vec.size() != 2|| !fa.is_open())
        show_error();

    map<string, string> genome;
    read_genome(fa, genome, chr);
    if (genome.find(chr) == genome.end())
        show_error();




}

void extract_length(const int & argc, char ** argv)
{
    if (argc != 3)
        show_error();
    ifstream gff(argv[2]);
    if (!gff.is_open())
        show_error();

    string _line;
    size_t pos[2];
    string last_gene;
    size_t len = 0;
    while (getline(gff, _line))
    {
        istringstream line(_line);
        string word;
        while (line >> word)
        {
            if (word[0] == ANNO)
                continue;
            line >> word;
            line >> word;
            if (word != EXON)
                continue;
            line >> word;
            pos[0] = stoi(word);
            line >> word;
            pos[1] = stoi(word);
            if (pos[0] > pos[1])
            {
                cerr << "pos1 > pos2" << endl;
                show_error();
            }
            line >> word;
            line >> word;
            line >> word;
            line >> word;
            line >> word;
            string gene = word.substr(1, word.size() - 3);
            if (gene != last_gene)
            {
                if (last_gene.size() != 0)
                {
                    cout << last_gene << '\t' << len;
                    len = 0;
                    last_gene = gene;
                }
            }
            len += (pos[1] - pos[0]);
            break;
        }
    }
    cout << last_gene << '\t' << len;

}
bool read_gff(istream & gff, map<string, vector<size_t >> & genes, string & tag)
{
    string _line;
    size_t pos[2];
    while (getline(gff, _line))
    {
        istringstream line(_line);
        string word;
        while (line >> word)
        {
            if (word[0] == ANNO)
                continue;
            string chrom = word;
            chrom.push_back(' ');
            line >> word;
            line >> word;
            if (!(word == tag))
                continue;
            line >> word;
            pos[0] = stoi(word);
            line >> word;
            pos[1] = stoi(word);
            line >> word;
            line >> word;
            bool plus = (word[0] == PLUS);
            //line >> word;
            //line >> word;
            //line >> word;
            //line >> word;
            //line >> word;
            //string gene_id = word.substr(1, word.size() - 3);
            line >> word;
            line >> word;
            std::string::size_type st = word.find("Name=");
            std::string::size_type ed = word.find(";", st + 6);
            string gene_id = word.substr(st + 5, ed == string::npos ? word.size() : ed - st - 5);
            gene_id = chrom + gene_id;
            if (!plus && genes.find(gene_id) == genes.end())
                genes[gene_id].push_back(MINUS_FALG);
            genes[gene_id].push_back(pos[0]);
            genes[gene_id].push_back(pos[1]);
            break;
        }
    }
    return true;
}

bool read_genome(istream & fa, map<string, string> & genome)
{
    string line;
    string chrom;
    while (getline(fa, line))
    {
        if (line[0] == ANNO)
            continue;
        if (line[0] == CHROM)
            chrom = line.substr(1);
        else
            genome[chrom] += line;
    }
    return true;
}

bool read_genome(istream & fa, map<string, string> & genome, string & chr)
{
    string line;
    string chrom;
    bool meet = false;
    while (getline(fa, line))
    {
        if (line[0] == ANNO)
            continue;
        if (line[0] == CHROM)
        {
            if (meet)
                break;
            else {
                chrom = line.substr(1);
                if (chrom == chr)
                    meet = true;
            }
        }
        else
            genome[chrom] += line;
    }
    return true;
}

bool write_cds(ostream & os, map<string, string> & genome, map<string, vector<size_t >> & genes, set<string> & gene_set)
{
    os << "##CDS sequence from gff3" << endl;
    for (auto & it : genes)
    {
        if (!gene_set.empty())
        {
            bool within = false;
            for (auto & gene : gene_set)
            {
                if (it.first.find(gene) != std::string::npos)
                {
                    within = true;
                    break;
                }
            }
            if (!within)
                continue;
        }
        size_t st = it.first.find(' ');
        string chrom_name = it.first.substr(0, st) ;
        const string & sequence = genome[chrom_name];
        string line;
        size_t pos1, pos2;
        size_t len = 0;
        bool plus;
        os << '>' << it.first.substr(st + 1, it.first.size()) << '|';
        os << "chrom: " << chrom_name << '|';
        os << ((plus = !(it.second[0] == MINUS_FALG)) ? '+' : '-') << '|';
        os << "position: ";
        for (auto po : it.second)
        {
            if (po == 0)
                continue;
            os << po << ':';
        }
        for (size_t index = (plus ? 0 : 1);index != it.second.size(); index+=2)
        {
            pos1 = it.second[index] - 1;
            pos2 = it.second[index + 1] - 1;
            len += (pos2 - pos1 + 1);
            line += sequence.substr(pos1, pos2 - pos1 + 1);
        }
        os << "|length: " << len << endl;
        if (plus)
            os << line << endl;
        else
        {
            transcribe(line);
            for_each(line.rbegin(), line.rend(), [&os] (const char & ch) {os << ch;});
            os << endl;
        }
    }
    return true;
}

bool read_include(istream & include, set<string> & gene_set)
{
    string gene;
    while (getline(include, gene))
    {
        if (gene.size() > 2)
            gene_set.insert(gene);
    }
    return true;
}

void fetch_position(string & loc_string, vector<size_t > & pos_vec)
{
    size_t pos = 0;
    size_t last_p = 0;
    try
    {
        while ((pos = loc_string.find(':', pos)) != std::string::npos) {
            pos_vec.push_back(stoi(loc_string.substr(last_p, pos - last_p)));
            last_p = pos++ + 1;
        }
        pos_vec.push_back(stoi(loc_string.substr(last_p)));
    }
    catch (const std::exception &err)
    {
        cerr << err.what();
        cerr << "your input position format must like: 1:2000";
        show_error();
    }
}

void transcribe(string & line)
{
    for (auto &ch : line) {
        if (ch == 'A')
            ch = 'T';
        else if (ch == 'G')
            ch = 'C';
        else if (ch == 'C')
            ch = 'G';
        else if (ch == 'T')
            ch = 'A';
        else
            continue;
    }
}


bool write_bed(ostream & os, map<string, string> & genome, map<string, vector<size_t >> & genes, set<string> & gene_set)
{
    for (auto & it : genes) {
        if (!gene_set.empty()) {
            bool within = false;
            for (auto &gene : gene_set) {
                if (it.first.find(gene) != std::string::npos) {
                    within = true;
                    break;
                }
            }
            if (!within)
                continue;
        }
        size_t st = it.first.find(' ');
        string chrom_name = it.first.substr(0, st);
        const string &sequence = genome[chrom_name];
        string gene_name = it.first.substr(st + 1, it.first.size());
        bool plus = !(it.second[0] == MINUS_FALG) ? '+' : '-';
        cout << chrom_name << '\t';
        size_t pos1 = plus ? it.second[0] : it.second[1];
        size_t pos2 = plus ? it.second[1] : it.second[2];
        cout << pos1 << '\t';
        cout << pos2 << '\t';
        cout << gene_name << '\t';
        cout << "100" << '\t';
        cout << (plus ? '+' : '-') << '\t';
        cout << pos1 << '\t';
        cout << pos2 << '\t';
        cout << "100" << '\t';
        cout << '1' << '\t';
        cout << pos2 - pos1 << '\t';
        cout << '0' << endl;
    }
    return true;
}






