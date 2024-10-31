#define reg_count 4
enum reg : unsigned char
{
	AR,					// Accumulator Register, аккумул€тор.
	CR,					// Counter Register, регистр счЄтчик.
	CC,					// Command Counter, счЄтчик команд.
	FR					// Flag Register, регистр флагов.
};

enum addressType : unsigned char
{
	VAL,				// Value, непосредственно значение.
	REG,				// Register, регистр.
	MDVAL,				// MemoryDataValue, €чейка пам€ти данных по непосредственному адресу.
	MDREG,				// MemoryDataRegister, €чейка пам€ти данных по адресу из регистра.
	MPVAL,				// MemoryProgramValue, €чейка пам€ти программы по непосредственному адресу.
	MPREG				// MemoryProgramRegister, €чейка пам€ти программы по адресу из регистра.
};

enum com : unsigned char
{
	SET = 1,			// SetData, установить значение в пам€ть данных.			SET <операнд> <назначение>
	EQU,				// —равнение, 1 если значени€ равны, 0 если нет.			EQU <операнд1> <операнд2> <назначение>
	CON,				// Conjunction, поразр€дна€ конъюнкици€.					CON <операнд1> <операнд2> <назначение>
	SUM,				// —умма двух операндов.									SUM <операнд1> <значение> <назначение>
	SUB,				// –азность двух операндов.									sSUM <операнд1> <операнд2> <назначение>
	JMP					// ѕереход к исполнению инструкции по номеру.				JMP <назначение>
};