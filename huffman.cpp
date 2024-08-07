#include <iostream>
#include <vector>
#include <iterator>
#include <map>
#include <queue>
#include <fstream>

using namespace std;
map<char, string> codes;
map<char, int> freq;
struct MinHeapNode
{
    char data;
    int freq;
    MinHeapNode *left, *right;

    MinHeapNode(char data, int freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

class Huff
{
public:
    priority_queue<MinHeapNode *, vector<MinHeapNode *>> minHeap;

    void HuffmanCodes(int);
    void calculate_frequency(string);
    void print_frequency();
    string decode_file(string);
    string file_to_text();
    void Code(MinHeapNode *, string);
    string file_encode(string);
    void file_decode(string);
};
void Huff::HuffmanCodes(int size)
{
    struct MinHeapNode *left, *right, *top;
    for (map<char, int>::iterator v = freq.begin(); v != freq.end(); v++)
        minHeap.push(new MinHeapNode(v->first, v->second));
    while (minHeap.size() != 1)
    {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        top = new MinHeapNode('*', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    Code(minHeap.top(), "");
}

void Huff::Code(struct MinHeapNode *root, string str)
{
    if (root == NULL)
        return;
    if (root->data != '*')
        codes[root->data] = str;
    Code(root->left, str + "0");
    Code(root->right, str + "1");
}

void Huff::calculate_frequency(string str)
{
    for (int i = 0; i < str.size(); i++)
        freq[str[i]]++;
}

string Huff ::decode_file(string s)
{
    MinHeapNode *root;
    string ans = "";
    root = minHeap.top();
    struct MinHeapNode *curr = root;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;

        // reached leaf node
        if (curr->left == NULL and curr->right == NULL)
        {
            ans += curr->data;
            curr = root;
        }
    }

    return ans + '\0';
}
string Huff::file_to_text()
{
    string str1;
    char ch;
    ifstream fin;
    fin.open("sample.txt");
    while (fin)
    {

        fin.get(ch);
        if (ch == ' ' || ch == '\n')
        {
            continue;
        }
        str1 += ch;
    }
    return str1;
    fin.close();
}
void Huff::print_frequency()
{

    for (map<char, int>::iterator v = freq.begin(); v != freq.end(); v++)
        cout << v->first << ' ' << v->second << endl;
}
string Huff::file_encode(string str)
{
    string encodedstring;
    for (auto i : str)
        encodedstring += codes[i];
    ofstream out("encoded.dat", ios::out | ios::binary);
    out << encodedstring;
    out.close();
    return encodedstring;
}
void Huff::file_decode(string decodedstring)
{

    ofstream out1;
    out1.open("decode.txt");
    out1 << decodedstring;
    out1.close();
}

int main()
{
    string str1;
    string decodedString, encodedString;
    int ch;
    Huff h;
    cout << "\n********************FILE COMPRESSOR USING HUFFMAN CODE ALGORITHM**********************************";
    cout << "\nPROJECT BY PIYUSH 2022CEB1019\n";
    cout << "\n****************************************************************************************************";
    do
    {
        cout << "\n1.CALCULATE FREQUENCY \n2.ENCODE FILE \n3.DECODE FILE \n4.EXIT";
        cout << "\n ENTER YOUR CHOICE:";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "\nFREQUENCY OF EACH CHARACTER IS:\n";
            str1 = h.file_to_text();
            h.calculate_frequency(str1);
            h.print_frequency();
            break;
        case 2:
            h.HuffmanCodes(str1.length());
            encodedString = h.file_encode(str1);
            cout << "\n************************FILE ENCODED SUCCESSFULLY***********************************";
            break;
        case 3:
            decodedString = h.decode_file(encodedString);
            h.file_decode(decodedString);
            cout << "\n************************FILE DECODED SUCCESSFULLY***********************************";
            break;
        case 4:
            cout << "\nEXIT";
            break;
        }

    } while (ch != 4);

    return 0;
}