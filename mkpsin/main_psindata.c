//
//  main_psindata.c
//  mkpsin
//
//  Created by Noah Wooten on 2/14/22.
//

#include "root.h"
#include "psin/psin.h"

void main_loadinst(void) {
	psin_declare("SET = 0x00, // Set Register (SET [R:(4,4),DEST] [R:(4,4),SRC]):16");
	psin_declare("LDWM = 0x01, // Load Register Word from Memory (LDWM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16");
	psin_declare("STWM = 0x02, // Store Register Word in Memory (STWM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16");
	psin_declare("LDBM = 0x03, // Load Register Byte from Memory (LDBM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16");
	psin_declare("STBM = 0x04, // Store Register Byte in Memory (STBM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16");
	psin_declare("OR = 0x05, // Logical OR (OR [R:(4,4),DEST] [R:(4,4),SRC]):16");
	psin_declare("AND = 0x06, // Logical AND (AND [R:(4,4),DEST] [R:(4,4),SRC]):16");
	psin_declare("XOR = 0x07, // Logical XOR (XOR [R:(4,4),DEST] [R:(4,4),SRC]):16");
	psin_declare("NOT = 0x08, // Logical NOT (NOT [R:(4,4),DEST] [R:(4,4),SRC]):16");
	psin_declare("ADD = 0x09, // Summate Registers (ADD [R:(4,4),DEST] [R:(4,4),SRC]):16");
	psin_declare("SUB = 0x0A, // Subtract Registers (SUB [R:(4,4),DEST] [R:(4,4),SRC]):16");
	psin_declare("MUL = 0x0B, // Multiply Registers (MUL [R:(4,4),DEST] [R:(4,4),SRC]):16");
	psin_declare("DIV = 0x0C, // Divide Registers (DIV [R:(4,4),DEST] [R:(4,4),SRC]):16");
	psin_declare("SETI = 0x0D, // Set Register Immediate (SETI [R:(4,8),DEST] [I:(64,64),SRC]):80");
	psin_declare("LDWMI = 0x0E, // Load Register Word from Memory Immediate (LDWMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80");
	psin_declare("STWMI = 0x0F, // Store Register Word in Memory Immediate (STWMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80");
	psin_declare("LDBMI = 0x10, // Load Register Byte from Memory Immediate (LDBMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80");
	psin_declare("STBMI = 0x11, // Store Register Byte in Memory Immediate (STBMI [R:(4,8),DEST] [I:(64,64),SRC_PTR]):80");
	psin_declare("ORI = 0x12, // Logical OR Immediate (ORI [R:(4,8),DEST] [I:(64,64),SRC]):80");
	psin_declare("ANDI = 0x13, // Logical AND Immediate (ANDI [R:(4,8),DEST] [I:(64,64),SRC]):80");
	psin_declare("XORI = 0x14, // Logical XOR Immediate (XORI [R:(4,8),DEST] [I:(64,64),SRC]):80");
	psin_declare("ADDI = 0x15, // Sum Register and Immediate (ADDI [R:(4,8),DEST] [I:(64,64),SRC]):80");
	psin_declare("SUBI = 0x16, // Subtract Immediate from Register (SUBI [R:(4,8),DEST] [I:(64,64),SRC]):80");
	psin_declare("MULI = 0x17, // Multiply Register by Immediate (MULI [R:(4,8),DEST] [I:(64,64),SRC]):80");
	psin_declare("DIVI = 0x18, // Divide Register By Immediate (DIVI [R:(4,8),DEST] [I:(64,64),SRC]):80");
	psin_declare("SL = 0x19, // Shift Left (SL [R:(4,4),DEST] [R:(4,4),AMT]):16");
	psin_declare("SR = 0x1A, // Shift Right (SR [R:(4,4),DEST] [R:(4,4),AMT]):16");
	psin_declare("SLI = 0x1B, // Shift Left Immediate (SLI [R:(4,8),SRC] [I:(6,8),AMT]):24");
	psin_declare("SRI = 0x1C, // Shift Right Immediate (SRI [R:(4,8),SRC] [I:(6,8,AMT]):24");
	psin_declare("SA = 0x1D, // Stack Add (SA [R:(4,8),SRC]):16");
	psin_declare("SP = 0x1E, // Stack Pull (SP [R:(4,8),DEST]):16");
	psin_declare("SAI = 0x1F, // Stack Add Immediate (SAI [I:(64, 64)]):72");
	psin_declare("GO = 0x20, // Go (GO [R:(4,8),LOCATION]):16");
	psin_declare("ENT = 0x21, // Enter (GO [R:(4,8),LOCATION]):16");
	psin_declare("RT = 0x22, // Return (RT):8");
	psin_declare("RTF = 0x23, // Return if Flag (RTF [R:(4,8),FLAG]):16");
	psin_declare("RTFI = 0x24, // Return if Flag Immediate (RTFI [I:(64,64),FLAG]):72");
	psin_declare("GOI = 0x25, // Go Immediate (GOI [I:(64,64),LOCATION]):72");
	psin_declare("ENTI = 0x26, // Enter Immediate (ENTI [I:(64,64),LOCATION]):72");
	psin_declare("CMP = 0x27, // Compare Registers (CMP [R:(4,4),COMPARE0] [R:(4,4),COMPARE1]):16");
	psin_declare("CMPI = 0x28, // Compare Register with Immediate (CMPI [R:(4,8),COMPARE0] [I:(64,64),COMPARE1]):80");
	psin_declare("GOF = 0x29, // Go if Flag (GOF [R:(4,4),LOCATION] [R:(4,4),FLAG]):16");
	psin_declare("ENTF = 0x2A, // Enter if Flag (ENTF [R:(4,4),LOCATION] [R:(4,4),FLAG]):16");
	psin_declare("GOFI = 0x2B, // Go if Flag Immediate (GOFI [R:(4,8),LOCATION] [I:(64,64),FLAG]):80");
	psin_declare("ENTFI = 0x2C, // Enter if Flag Immediate (ENTFI [R:(4,8),LOCATION] [I:(64,64),FLAG]):80");
	psin_declare("GOFII = 0x2D, // Go if Flag Immediate Immediate  (GOFII [I:(64,64),LOCATION] [I:(64,64),FLAG]):136");
	psin_declare("ENTFII = 0x2E, // Enter if Flag Immediate Immediate (ENTFII [I:(64,64),LOCATION] [I:(64,64),FLAG]):136");
	psin_declare("NEG = 0x2F, // Signed Negate Register (NEG [R:(4,8)]):16");
	psin_declare("NOP = 0x30, // No Operation (NOP):8");
	psin_declare("EIH = 0x31, // Enable Interrupt Handling (EIH):8");
	psin_declare("DIH = 0x32, // Disable Interrupt Handling (DIH):8");
	psin_declare("HLT = 0x33, // Enter Halt State (HLT):8");
	psin_declare("INT = 0x34, // Call Interrupt (INT [R:(4,8),INTERRUPT]):8");
	psin_declare("INTI = 0x35, // Call Interrupt Immediate (INTI [I:(8,8),INTERRUPT]):16");
	psin_declare("HND = 0x36, // Handle Interrupt (HND [R:(4,4),INTERRUPT] [R:(4,4),LOCATION]):16");
	psin_declare("HNDI = 0x37, // Handle Interrupt Immediate (HNDI [I:(8,8),INTERRUPT] [R:(4,8),LOCATION]):24");
	psin_declare("HNDII = 0x38, // Handle Interrupt Immediate Immediate (HNDII [I:(8,8),INTERRUPT] [I:(64,64),LOCATION]):80");
	psin_declare("SPA = 0x39, // Stack Pull All (SPA):8");
	psin_declare("SPG = 0x3A, // Stack Pull General (SPG):8");
	psin_declare("SAA = 0x3B, // Stack Add (Push) All (SAA):8");
	psin_declare("SAG = 0x3C, // Stack Add (Push) General (SAG):8");
	psin_declare("LDSD = 0x3D, // Load System Descriptor (LDSD [R:(4,4),PART0] [R:(4,4),PART1]):16");
	psin_declare("LDSDI = 0x3E, // Load System Descriptor Immediate (LDSDI [I:(64,64),PART0] [I:(64,64),PART1]):136");
	psin_declare("STSD = 0x3F, // Store System Descriptor to Registers (STSD [R:(4,4),PART0] [R:(4,4),PART1]):16");
	psin_declare("LDVM = 0x40, // Load Virtual Descriptor from Registers (LDVM [R:(4,4),PART0] [R:(4,4),PART1]):16");
	psin_declare("LDVMI = 0x41, // Load Virtual Descriptor from Immediates (LDVMI [I:(64,64),PART0] [I:(64,64),PART1]):136");
	psin_declare("STVM = 0x42, // Store Virtual Descriptor to Registers (STVM [R:(4,4),PART0] [R:(4,4),PART1]):16");
	psin_declare("SPN = 0x43, // Stack Pull No Operand (SPN):8");
	psin_declare("MSP = 0x44, // Multiply Stack Pointer (DATA is multiplied by IMM) (MSP [R:(4,4),DATA] [I:(20,20),IMM]):32");
	psin_declare("SSP = 0x45, // Subtract Stack Pointer (DATA is multiplied by IMM) (SSP [R:(4,4),DATA] [I:(20,20),IMM]):32");
	psin_declare("ASP = 0x47, // Add Stack Pointer (DATA is multiplied by IMM) (ASP [R:(4,4),DATA] [I:(20,20),IMM]):32");
	psin_declare("SPB = 0x48, // Stack Pull Byte (SPB [R:(4,8),DEST]):16");
	psin_declare("SAB = 0x49, // Stack Add Byte (SAB [R:(4,8),SRC]):16");
	psin_declare("SAII = 0x4A, // Stack Add Byte Immediate (SAII [I:(8,8),SRC]):16");
	psin_declare("INC = 0x4B, // Increment (INC [R:(4,8),SRC]):16");
	psin_declare("DEC = 0x4C, // Decrement (DEC [R:(4,8),SRC]):16");
	psin_declare("SBN = 0x4D, // Stack Pull Byte No Operand (SBN):8");
	psin_declare("IOB = 0x4E, // IO Output Byte (IOB [R:(4,4),PORT] [R:(4,4),DATA]):16");
	psin_declare("IIB = 0x4F, // IO Input Byte (IIB [R:(4,4),PORT] [R:(4,4),DATA]):16");
	psin_declare("IOW = 0x50, // IO Output Word (IOW [R:(4,4),PORT] [R:(4,4),DATA]):16");
	psin_declare("IIW = 0x51, // IO Input Word (IIW [R:(4,4),PORT] [R:(4,4),DATA]):16");
	psin_declare("IOS = 0x52, // IO Output String (IOB [R:(4,4),PORT] [R:(4,4),DATA] [R:(4,8),LEN]):24");
	psin_declare("IIS = 0x53, // IO Input String (IOB [R:(4,4),PORT] [R:(4,4),STR] [R:(4,8),LEN]):24");
	psin_declare("LDHM = 0x54, // Load Register Half-Word from Memory (LDHM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16");
	psin_declare("STHM = 0x55, // Store Register Half-Word in Memory (STHM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16");
	psin_declare("LDHMI = 0x56, // Load Immediate Half-Word from Memory (LDHM [R:(4,8),DEST] [I:(32,32),SRC]):48");
	psin_declare("STHMI = 0x57, // Store Immediate Half-Word in Memory (STHM [R:(4,8),DEST] [I:(32,32),SRC]):48");
	psin_declare("LDQM = 0x58, // Load Register Quarter-Word from Memory (LDQM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16");
	psin_declare("STQM = 0x59, // Store Register Quarter-Word from Memory (STQM [R:(4,4),DEST] [R:(4,4),SRC_PTR]):16");
	psin_declare("LDQMI = 0x5A, // Load Immediate Quarter-Word from Memory (LDQM [R:(4,8),DEST] [I:(16,16),SRC]):32");
	psin_declare("STQMI = 0x5B, // Store Immediate Quarter-Word from Memory (STQM [R:(4,8),DEST] [I:(16,16),SRC]):32");
}
