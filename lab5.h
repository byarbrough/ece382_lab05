//-----------------------------------------------------------------
// Name:	Brian Yarbrough
// Start:	Dr. Coulston
// File:	lab5.h
// Date:	Fall 2014
// Purp:	Include file for the MSP430 - contains lookup table for remote
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Page 76 : MSP430 Optimizing C/C++ Compiler v 4.3 User's Guide
//-----------------------------------------------------------------
typedef		unsigned char		int8;
typedef		unsigned short		int16;
typedef		unsigned long		int32;
typedef		unsigned long long	int64;

#define		TRUE				1
#define		FALSE				0

//-----------------------------------------------------------------
// Function prototypes found in lab5.c
//-----------------------------------------------------------------
void initMSP430();
__interrupt void pinChange (void);
__interrupt void timerOverflow (void);


//-----------------------------------------------------------------
// Each PxIES bit selects the interrupt edge for the corresponding I/O pin.
//	Bit = 0: The PxIFGx flag is set with a low-to-high transition
//	Bit = 1: The PxIFGx flag is set with a high-to-low transition
//-----------------------------------------------------------------

#define		IR_PIN			(P2IN & BIT6)
#define		HIGH_2_LOW		P2IES |= BIT6
#define		LOW_2_HIGH		P2IES &= ~BIT6


#define		averageLogic0Pulse	0x0200
#define		averageLogic1Pulse	0x0645
#define		averageStartPulse	0x1100
#define		minLogic0Pulse		averageLogic0Pulse - 100
#define		maxLogic0Pulse		averageLogic0Pulse + 100
#define		minLogic1Pulse		averageLogic1Pulse - 100
#define		maxLogic1Pulse		averageLogic1Pulse + 100
#define		minStartPulse		averageStartPulse - 100
#define		maxStartPulse		averageStartPulse + 100

//buttons on the Hitachi remote are commented out.
//buttons for my phone remote are active
#define		UP		0x20DF02FD //0x0AF50EF1
#define		DOWN	0x20DF827D //0x0AF58E71
#define		LEFT	0x20DFE01F //0x0AF5CE31
#define		RIGHT	0x20DF609F //0x0AF54EB1

#define		CH_UP	0x20DF718E //0x0AF59867
#define		CH_DW	0x20DFF10E //0x0AF518E7
#define		MUTE	0x20DF8D72 //0x0AF5D02F
#define		EXIT	0x20DFDA25 //0x0AF508F7

void handlePress();

//added for A functionality
extern void init();
extern void initNokia();
extern void clearDisplay();
extern void drawBlock(unsigned char row, unsigned char col, unsigned char shade);



