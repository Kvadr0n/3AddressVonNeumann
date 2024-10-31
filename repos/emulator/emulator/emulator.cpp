#include <iostream>
#include <fstream>
#include <string>
#include "cheatsheet.h"

#define program_offset 100
#define program_maxlength 156

unsigned char memory[program_offset + program_maxlength]{};
unsigned char registers[reg_count]{};
unsigned long long* ir{};
unsigned char command, address, operand1, operand2, location;
unsigned char result;
unsigned char operand1type, operand2type, locationtype;
unsigned char operand1tmp, operand2tmp, locationtmp;
std::string regDict[] = {"AR", "CR", "CC", "FR"};
std::string comDict[] = {"END", "SET", "EQU", "CON", "SUM", "SUB", "JMP"};
std::string operandStr;
unsigned char* writeLocation;
unsigned checker;

void init()
{
    using namespace std;
    ifstream data("data.txt"), program("program.txt", ios::binary);
    string line;
    for (int i = 0; !data.eof(); ++i)
    {
        getline(data, line);
        memory[i] = unsigned char(stoi(line));
    }
    unsigned char* programMemory = memory + program_offset;
    for (; !program.eof(); ++programMemory)
        *programMemory = program.get();
    programMemory[-1] = 0;
    data.close();
    program.close();
}

std::string commandDisplay = "                      ";

std::string binaryfrom8(unsigned char a)
{
    using namespace std;
    string res = "";
    for (int i = 0; i < 8; ++i)
        res = to_string((a >> i) & 1) + res;
    return(res);
}

std::string binaryfrom40(unsigned long long a)
{
    using namespace std;
    string res = "";
    int tmp = a;
    for (int j = 0; j < 5; ++j)
    {
        tmp = a >> (8 * (4 - j));
        for (int i = 0; i < 8; ++i)
            res = to_string((tmp >> i) & 1) + res;
        if (j != 4)
            res = " " + res;
    }
    return(res);
}

void display()
{
    std::string instructions = binaryfrom40(*ir);
    std::string flags = binaryfrom8(registers[FR]);
    using namespace std;
    system("cls");
    cout << "Accumulator register: " << int(registers[AR]) << '\n'
         << "    Counter register: " << int(registers[CR]) << '\n'
         << "     Command counter: " << int(registers[CC]) << '\n'
         << "Instruction register: " << instructions << '\n'
         << commandDisplay << '\n'
         << "       Flag register: " << flags << '\n';
    system("pause");
}

#define ADDRESS_OPERAND(operand)                                            \
operand##tmp = operand;                                                     \
switch (address % 6)                                                        \
{                                                                           \
    case VAL:                                                               \
    {                                                                       \
        operand = operand;                                                  \
        operand##type = VAL;                                                \
        break;                                                              \
    }                                                                       \
    case REG:                                                               \
    {                                                                       \
        operand = registers[operand];                                       \
        operand##type = REG;                                                \
        break;                                                              \
    }                                                                       \
    case MDVAL:                                                             \
    {                                                                       \
        operand = memory[operand];                                          \
        operand##type = MDVAL;                                              \
        break;                                                              \
    }                                                                       \
    case MDREG:                                                             \
    {                                                                       \
        operand = memory[registers[operand]];                               \
        operand##type = MDREG;                                              \
        break;                                                              \
    }                                                                       \
    case MPVAL:                                                             \
    {                                                                       \
        operand = memory[program_offset + operand];                         \
        operand##type = MPVAL;                                              \
        break;                                                              \
    }                                                                       \
    case MPREG:                                                             \
    {                                                                       \
        operand = memory[program_offset + registers[operand]];              \
        operand##type = MPVAL;                                              \
        break;                                                              \
    }                                                                       \
}                                                                           \
address /= 6;

#define FORMAT_OPERAND(operand)                                             \
switch (operand##type)                                                      \
{                                                                           \
    case VAL:                                                               \
    {                                                                       \
        operandStr = " " + std::to_string(operand##tmp);                    \
        break;                                                              \
    }                                                                       \
    case REG:                                                               \
    {                                                                       \
        operandStr = " " + regDict[operand##tmp];                           \
        break;                                                              \
    }                                                                       \
    case MDVAL:                                                             \
    {                                                                       \
        operandStr = " *" + std::to_string(operand##tmp);                   \
        break;                                                              \
    }                                                                       \
    case MDREG:                                                             \
    {                                                                       \
        operandStr = " *" + regDict[operand##tmp];                          \
        break;                                                              \
    }                                                                       \
    case MPVAL:                                                             \
    {                                                                       \
        operandStr = " !" + std::to_string(operand##tmp);                   \
        break;                                                              \
    }                                                                       \
    case MPREG:                                                             \
    {                                                                       \
        operandStr = " !" + regDict[operand##tmp];                          \
        break;                                                              \
    }                                                                       \
}                                                                           \
commandDisplay += operandStr;


int main()
{
    init();
    while (memory[registers[CC] + program_offset])
    {
        ir = (unsigned long long*)(memory + program_offset + registers[CC]);
        command  = ((unsigned char*)(ir))[0];
        address  = ((unsigned char*)(ir))[1];
        operand1 = ((unsigned char*)(ir))[2];
        operand2 = ((unsigned char*)(ir))[3];
        location = ((unsigned char*)(ir))[4];

        ADDRESS_OPERAND(operand1);
        ADDRESS_OPERAND(operand2);

        switch (command)
        {
            case SET:
            {
                result = operand1;
                location = operand2;
                checker = operand1;
                operand2tmp = 0;
                break;
            }
            case EQU:
            {
                result = operand1 == operand2;
                checker = operand1 == operand2;
                break;
            }
            case CON:
            {
                result = operand1 & operand2;
                checker = operand1 & operand2;
                break;
            }
            case SUM:
            {
                result = operand1 + operand2;
                checker = operand1 + operand2;
                break;
            }
            case SUB:
            {
                result = operand1 - operand2;
                checker = operand1 - operand2;
                break;
            }
            case JMP:
            {
                location = operand1;
                operand1tmp = 0;
                checker = result;
                break;
            }
        }

        locationtype = address % 6;
        switch (locationtype)
        {
            case REG:
            {
                writeLocation = registers + location;
                break;
            }
            case MDVAL:
            {
                writeLocation = memory + location;
                break;
            }
            case MDREG:
            {
                writeLocation = memory + registers[location];
                break;
            }
            case MPVAL:
            {
                writeLocation = memory + program_offset + location;
                break;
            }
            case MPREG:
            {
                writeLocation = memory + program_offset + registers[location];
                break;
            }
        }

        locationtmp = location;
        commandDisplay = "                      " + comDict[command];
        FORMAT_OPERAND(operand1);
        FORMAT_OPERAND(operand2);
        FORMAT_OPERAND(location);
        display();

        switch (command)
        {
            case JMP:
            {
                registers[CC] = location * 5;
                break;
            }
            default:
            {
                *writeLocation = result;
                registers[CC] += 5;
                registers[FR] &= 0;
                if (checker != result)
                    registers[FR] |= 0b0001'0000;
                if (!result)
                    registers[FR] |= 0b0000'0001;
                break;
            }
        }
    }
}