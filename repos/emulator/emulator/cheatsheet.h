#define reg_count 4
enum reg : unsigned char
{
	AR,					// Accumulator Register, �����������.
	CR,					// Counter Register, ������� �������.
	CC,					// Command Counter, ������� ������.
	FR					// Flag Register, ������� ������.
};

enum addressType : unsigned char
{
	VAL,				// Value, ��������������� ��������.
	REG,				// Register, �������.
	MDVAL,				// MemoryDataValue, ������ ������ ������ �� ����������������� ������.
	MDREG,				// MemoryDataRegister, ������ ������ ������ �� ������ �� ��������.
	MPVAL,				// MemoryProgramValue, ������ ������ ��������� �� ����������������� ������.
	MPREG				// MemoryProgramRegister, ������ ������ ��������� �� ������ �� ��������.
};

enum com : unsigned char
{
	SET = 1,			// SetData, ���������� �������� � ������ ������.			SET <�������> <����������>
	EQU,				// ���������, 1 ���� �������� �����, 0 ���� ���.			EQU <�������1> <�������2> <����������>
	CON,				// Conjunction, ����������� �����������.					CON <�������1> <�������2> <����������>
	SUM,				// ����� ���� ���������.									SUM <�������1> <��������> <����������>
	SUB,				// �������� ���� ���������.									sSUM <�������1> <�������2> <����������>
	JMP					// ������� � ���������� ���������� �� ������.				JMP <����������>
};