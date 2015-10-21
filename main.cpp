#include <iostream>
#include <fstream>
#include "AVLTreeSet.h"
 
using namespace std;
 
void remove(string command, ifstream& in, ofstream& out, AVLTreeSet <string>& MySet, string data);
void insert(string command, ifstream& in, ofstream& out, string data, AVLTreeSet <string>& MySet);
void clear(string command, ofstream& out, AVLTreeSet <string>& MySet);
void find(string command, ifstream& in, ofstream& out, string data, AVLTreeSet <string>& MySet);
void print(string command,  ofstream& out_file, AVLTreeSet <string>& MySet);
 
 
int main(int argc, char*argv[]) {
 
    AVLTreeSet<string> MySet;
 
    ifstream in;
    string data;
    string command;
    in.open(argv[1]);
    ofstream out;
    out.open(argv[2]);
 
 
 
    while (in >> command)
    {
        if (command == "remove")
        {
            remove(command, in, out, MySet, data);
        }
        else if (command == "add")
        {
            insert(command, in, out, data, MySet);
        }
        else if (command == "clear")
        {
            clear(command, out, MySet);
        }
        else if (command == "find")
        {
            find(command, in, out, data, MySet);
        }
        else if (command == "print")
        {
            print(command, out, MySet);
        }
    }
    out.close();
    in.close();
 
 
    return 0;
}
void remove(string command, ifstream& in, ofstream& out, AVLTreeSet <string>& MySet, string data)
{
    in >> data;
    MySet.remove(data);
    out << command << " " << data << "\n";
}
void insert(string command, ifstream& in, ofstream& out, string data, AVLTreeSet <string>& MySet)
{
    in >> data;
    MySet.add(data);
    out << command << " " << data << "\n";
}
void clear(string command, ofstream& out, AVLTreeSet <string>& MySet)
{
    MySet.clear();
    out << command << "\n";
}
void find(string command, ifstream& in, ofstream& out, string data, AVLTreeSet <string>& MySet) {
    in >> data;
    out << command << " " << data << " "; if(MySet.find(data) == false){ out << "false";} else {out << "true";} out << "\n";
}
void print(string command, ofstream& out, AVLTreeSet <string>& MySet)
{
    out << command << "\n";
    MySet.print(out);
 
}
