#include <iostream> 
#include <string>
#include <fstream>
#include "wordlist.h"

using namespace std;

static const char ENDOFWORD='$';
static const int ENDOFREAD=-1; 
static const string MAGICWL="WORDLIST-MP";

TrieNode::TrieNode() 
{ 
        children = new shared_ptr<TrieNode>[ALPHABET_SIZE];
        for (int i = 0; i < ALPHABET_SIZE; i++) { 
                children[i] = shared_ptr<TrieNode>(); 
        } 
        isWord = false; 
} 

TrieNode::~TrieNode() 
{ 
    delete[]children;
} 

Trie::Trie() 
{ 
    clear();
} 

Trie::~Trie() 
{ 
        // Need not delete anything 
                        // as shared_ptr deallocates 
                        // all memory automatically 
} 

// To convert characters of string into 
// integer like hashing of character 
int c2i(char c) 
{ 
    return ALPHABET.find(c);
        //return static_cast<int>(c - 'a'); 
} 

char i2c(int i) {
    return ALPHABET[i];
}

int Trie::size() const {
    return this->Total_words;
}
// Insert word function 
bool Trie::insertWord(string trieS) 
{ 
        string trieString = normalizeWord(trieS);
        if (trieString.find(ALPHABET[0])!=string::npos) {
//            cerr << trieString << " discarded for insertion" << endl;
            return false;
        }
        if (this->searchWord(trieString)) {
//            cerr << trieString << " already existing" << endl;
            return false;
        }
        shared_ptr<TrieNode> current = root; 
        for (int i = 0; i < trieString.size(); i++) { 

                // If word after some prefix is not 
                                        // present then creates new node 
                if (current->children[c2i(trieString[i])] == 
                                        shared_ptr<TrieNode>(nullptr)) 
                { 
                        current->children[c2i(trieString[i])] = 
                                shared_ptr<TrieNode>(new TrieNode()); 
                } 
                current = (current->children[c2i(trieString[i])]); 
        } 

        // Now word is added in Trie so at leaf node 
        // for that word isWord=true 
        current->isWord = true;
        this->Total_words++;
        return true;
} 

// Searching for word whether it is 
// present in Trie 
bool Trie::searchWord(string trieS) const
{ 
        string trieString = trieS; //normalizeWord(trieS);
        shared_ptr<TrieNode> current = root; 

        for (int i = 0; i < trieString.size(); i++) 
        { 
                // If at any point in Trie Node for particular 
                // character is not present means nullptr then 
                // return false 
                if (current->children[c2i(trieString[i])] == 
                                                shared_ptr<TrieNode>(nullptr)) 
                        return false; 
                current = current->children[c2i(trieString[i])]; 
        } 

        // At the end of the word checking whether this 
        // word is really present or not 
        if (current->isWord == true) 
                return true; 

        return false; 
} 


bool Trie::Partdelete(string trieString, shared_ptr<TrieNode>& checkout) 
{ 
        // Word is not present in the Trie then returns 
        // false and stops further recursion 
        if (checkout == nullptr) 
                return false; 

        // At the end of the word if the word is 
        // present in trie then setting isWord to 
        // false either returing false 
        if (trieString.size() == 0) { 
                if (checkout->isWord == true) { 
                        checkout->isWord = false; 
                        return true; 
                } 
                return false; 
        } 

        // String excluding first character 
        string part = trieString.substr(1); 

        // Recusive call to Partdelete for 
        // rest of the string(part) 
        if (Partdelete(part, checkout-> 
                                children[c2i(trieString[0])])) { 

                // Checks whether it is empty node 
                // then delete this node 
                if (isEmptyNode(checkout-> 
                                children[c2i(trieString[0])])) { 

                        // Resetting memory and making it nullptr 
                        checkout->children[c2i(trieString[0])]. 
                                                                                        reset(); 

                        checkout->children[c2i(trieString[0])] = 
                                                                                        nullptr; 

                        return true; 
                } 
                else
                        return true; 
        } 
        else
                return false; 

        return false; 
} 

// For ease of recursion; passing 
// root to Partdelete 
bool Trie::deleteWord(string trieString) 
{ 
        if (Partdelete(trieString, root))  {
            this->Total_words--;
            return true; 
        }
        return false; 
} 

// Checks whether there is no children present 
bool Trie::isEmptyNode(shared_ptr<TrieNode> check) const
{ 
        for (int i = 0; i < ALPHABET_SIZE; i++) { 
                if (check->children[i] != nullptr || 
                                                check->isWord == true) 
                        return false; 
        } 
        return true; 
} 

ostream & operator<<(ostream & os, const Trie & t) {
    t.rSave(os,t.root,0);
    return os;
}

bool Trie::save(std::string filename) const {
    ofstream f(filename, ios::out);
    cout << "Saving tree file "<< filename << endl;
    if (f) {
        f << MAGICWL << endl << this->Total_words<<endl;
        f << *this;
        f << ENDOFREAD;
        if (f)  {
            f.close();
            return true;
        }
        cerr << "*** Error saving data in " << filename << endl;
        return false;
    }
    cerr << "*** Error opening file "<< filename << endl;
    return false;
    
}

void Trie::rSave(ostream &os, shared_ptr<TrieNode> p, int level) const 
{ 
        if (p == shared_ptr<TrieNode>(nullptr)){
            return;
        }
        if (p->isWord)
            os << level << ENDOFWORD << endl;
        for (int i = 0; i < ALPHABET_SIZE; i++) 
        { 
            if (p->children[i] != shared_ptr<TrieNode>(nullptr)) {
                os<<level<<i2c(i);
                rSave(os,p->children[i],level+1);
            }
        }
} 
bool Trie::load(const string filename) {
    ifstream f(filename);
    string magic;
    int n;
    clear();
    cout << "Opening tree file "<< filename << endl;
    if (f) {
        f >> magic;
        if (magic != MAGICWL)  {
            cerr << "*** Error: Unknown format"<<endl;
            return false;
        }
        f>>n;
        cout << "Trying to read "<< n << " words"<< endl;
        f >> *this;
        if (f) {
            f.close();
            if (this->Total_words != n) {
                cout << "*** Error: "<< this->Total_words << " words read, out of "<<n<< endl;
                return false;
            }
            else {
                cout << "OK "<< n << " words read"<< endl;
                return true;
            }
        }
        cerr << "*** Data error in in " << filename << endl;
        return false;
    } 
    cerr << "*** Error opening "<< filename << endl;
    return false;
}

istream & operator>>(istream & is, Trie & t) {
    int clevel=0, level;
    is >> clevel;
    level=0;
    t.rLoad(is,t.root,level, clevel);
    return is;
}


void Trie::rLoad(istream &is, shared_ptr<TrieNode> p, int level, int &clevel)  
{ 
    char c;
    int count = 0;
    while (true)  {
        if (clevel < level){
            return;
        }
        is >> c;
//        c = toUTF(c)[0];
//        cerr << count++ << "(" << c<<")";
        if (c==ENDOFWORD) {
            is >> clevel;
            if (!is) clevel = -1;
            p->isWord=true;
            this->Total_words++;

        } else {
            if (p->children[c2i(c)] == shared_ptr<TrieNode>(nullptr))
                p->children[c2i(c)] = shared_ptr<TrieNode>(new TrieNode());
            is >> clevel;
            rLoad(is, p->children[c2i(c)],level+1,clevel);
        }
    }
}

void Trie::toWords() const 
{ 
    int wo =0;
    rtoWords(cout , root, "", wo);
} 

bool Trie::toWords(string filename) const 
{ 
    ofstream f(filename, ios::out);
    cout << "Saving words file "<< filename << endl;
    if (f) {
        if (f)  {
            int wo =0;
            f << this->Total_words << endl;
            rtoWords(f , root, "", wo);
            f.close();
            return true;
        }
        cerr << "ERROR saving data in " << filename << endl;
        return false;
    }
    cerr << "ERROR opening file "<< filename << endl;
    return false;
    
} 
bool Trie::fromWords(string filename)  
{ 
    ifstream f(filename);
    int nwords;
    string word;
    clear();
    cout << "Loading words file "<< filename << endl;
    if (f) {
        f >> nwords;
        for (int i=0; i<nwords; i++)  {
            f>> word;
            this->insertWord(word);
        }
        if (f)  {
            f.close();
            return false;
        }
        cerr << "ERROR reading data in " << filename << endl;
        return false;
    }
    cerr << "ERROR opening file "<< filename << endl;
    return false;
    
} 

void Trie::rtoWords(ostream &os, shared_ptr<TrieNode> p, const string s, int &wo) const 
{ 
        if (p == shared_ptr<TrieNode>(nullptr))
            return;
        if (p->isWord)
            os << wo++ <<" "<< s << endl;
        
        for (int i = 0; i < ALPHABET_SIZE; i++) 
        { 
            rtoWords(os, p->children[i],s+i2c(i), wo);
        } 
} 


void Trie::clear() {
    this->root = shared_ptr<TrieNode> (new TrieNode()); 
    this->Total_words = 0;
    
}

std::string toUTF(char in) {
    string s="-";
    s[0] = in;
    return toUTF(s.c_str());
}

std::string toUTF(std::string in) {
    return toUTF(in.c_str());
}



std::string toUTF(const char * i) {
    const unsigned char *in = (unsigned char*)i;
    string res="";
    while (*in)
        if (*in<128) res.append(1, static_cast<char>(*in++));
        else res.append(1, static_cast<char>(0xc2+(*in>0xbf))), res.append(1, static_cast<char>((*in++&0x3f)+0x80));//    string out;
    return res;
}

std::string toISO(std::string in) {
    return toISO(in.c_str());
}

std::string toISO(const char * in)
{
    std::string out;
    if (in == NULL)
        return out;
    if (!is_utf8(in))
        return in;
    unsigned int codepoint;
    while (*in != 0)
    {
        unsigned char ch = static_cast<unsigned char>(*in);
        if (ch <= 0x7f)
            codepoint = ch;
        else if (ch <= 0xbf)
            codepoint = (codepoint << 6) | (ch & 0x3f);
        else if (ch <= 0xdf)
            codepoint = ch & 0x1f;
        else if (ch <= 0xef)
            codepoint = ch & 0x0f;
        else
            codepoint = ch & 0x07;
        ++in;
        if (((*in & 0xc0) != 0x80) && (codepoint <= 0x10ffff))
        {
            if (codepoint <= 255)
            {
                out.append(1, static_cast<char>(codepoint));
            }
            else
            {
                // do whatever you want for out-of-bounds characters
            }
        }
    }
    return out;
}

string normalizeWord(const string & w)  {
    string word = toISO(w); //UTF8toISO8859(w.c_str());
    string res(word.size(),ALPHABET[0]), 
            accents=toISO("ÁÉÍÓÚáéíóúäëïöüñÄËÏÖÜäëïöüÇçàèìòùâêîôû"), 
            noaccents=toISO("AEIOUAEIOUAEIOUÑAEIOUAEIOUCCAEIOUAEIOU");
            //"aeiouaeiouaeiouñaeiouaeioucc";
    char letter;
    for (int i=0; i<word.size() && i<res.size(); i++)  {
        int pos = accents.find(word[i]);
        if (pos!=string::npos) {
            letter = noaccents[pos];
        } else {
            letter = word[i];
        }
        if (ALPHABET.find(toupper(letter)) == string::npos)
            res[i] = ALPHABET[0];
        else {                
            res[i] = toupper(letter);
        }
    }
    return res;
}

bool is_utf8(const char * string)
{
    if(!string)
        return false;

    const unsigned char * bytes = (const unsigned char *)string;
    while(*bytes)
    {
        if( (// ASCII
             // use bytes[0] <= 0x7F to allow ASCII control characters
                bytes[0] == 0x09 ||
                bytes[0] == 0x0A ||
                bytes[0] == 0x0D ||
                (0x20 <= bytes[0] && bytes[0] <= 0x7E)
            )
        ) {
            bytes += 1;
            continue;
        }

        if( (// non-overlong 2-byte
                (0xC2 <= bytes[0] && bytes[0] <= 0xDF) &&
                (0x80 <= bytes[1] && bytes[1] <= 0xBF)
            )
        ) {
            bytes += 2;
            continue;
        }

        if( (// excluding overlongs
                bytes[0] == 0xE0 &&
                (0xA0 <= bytes[1] && bytes[1] <= 0xBF) &&
                (0x80 <= bytes[2] && bytes[2] <= 0xBF)
            ) ||
            (// straight 3-byte
                ((0xE1 <= bytes[0] && bytes[0] <= 0xEC) ||
                    bytes[0] == 0xEE ||
                    bytes[0] == 0xEF) &&
                (0x80 <= bytes[1] && bytes[1] <= 0xBF) &&
                (0x80 <= bytes[2] && bytes[2] <= 0xBF)
            ) ||
            (// excluding surrogates
                bytes[0] == 0xED &&
                (0x80 <= bytes[1] && bytes[1] <= 0x9F) &&
                (0x80 <= bytes[2] && bytes[2] <= 0xBF)
            )
        ) {
            bytes += 3;
            continue;
        }

        if( (// planes 1-3
                bytes[0] == 0xF0 &&
                (0x90 <= bytes[1] && bytes[1] <= 0xBF) &&
                (0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
                (0x80 <= bytes[3] && bytes[3] <= 0xBF)
            ) ||
            (// planes 4-15
                (0xF1 <= bytes[0] && bytes[0] <= 0xF3) &&
                (0x80 <= bytes[1] && bytes[1] <= 0xBF) &&
                (0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
                (0x80 <= bytes[3] && bytes[3] <= 0xBF)
            ) ||
            (// plane 16
                bytes[0] == 0xF4 &&
                (0x80 <= bytes[1] && bytes[1] <= 0x8F) &&
                (0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
                (0x80 <= bytes[3] && bytes[3] <= 0xBF)
            )
        ) {
            bytes += 4;
            continue;
        }

        return false;
    }

    return true;
}