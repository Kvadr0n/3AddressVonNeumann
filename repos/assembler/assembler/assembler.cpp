#include <iostream>
#include <fstream>
#include <sstream>
#include "cheatsheet.h"

using namespace std;

string op, op1, op2, loc;
unsigned char opcode, adcode, op1code, op2code, loccode;
                              
#define CASE(value) if (name == #value) { code = value; return; }

void comEncode(string& name, unsigned char& code)
{
    CASE(SET);
    CASE(EQU);
    CASE(CON);
    CASE(SUM);
    CASE(SUB);
    CASE(JMP);
}

void regEncode(string& name, unsigned char& code)
{
    CASE(AR);
    CASE(CR);
    CASE(CC);
}

void opEncode(string& name, unsigned char& code, int num)
{
    int addigit = 0;
    if (name == "")
    {
        code = 0;
        return;
    }
    if (name[0] == '*')
    {
        addigit += MDVAL;
        name = name.substr(1);
    }
    else if (name[0] == '!')
    {
        addigit += MPVAL;
        name = name.substr(1);
    }
    switch (name[0])
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        {
            code = stoi(name);
            break;
        }
        default:
        {
            addigit += REG;
            regEncode(name, code);
            break;
        }
    }
    adcode += addigit * pow(6, num);
}

int main()
{
    ifstream input("assembly.txt");
    ofstream output("program.txt", ios::binary);

    string line;
    stringstream ss;

    while (!input.eof())
    {
        getline(input, line);
        ss = stringstream(line);
        ss >> op;
        if (ss.rdbuf()->in_avail())
        {
            ss >> op1;
            if (ss.rdbuf()->in_avail())
            {
                ss >> op2;
                if (ss.rdbuf()->in_avail())
                    ss >> loc;
                else
                    loc = "";
            }
            else
            {
                op2 = "";
                loc = "";
            }
        }
        else
        {
            op1 = "";
            op2 = "";
            loc = "";
        }
        
        comEncode(op, opcode);
        adcode = 0;
        opEncode(op1, op1code, 0);
        opEncode(op2, op2code, 1);
        opEncode(loc, loccode, 2);

        output << opcode << adcode << op1code << op2code << loccode;
    }

    input.close();
    output.close();
}