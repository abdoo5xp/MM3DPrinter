/*
 * Bit_Math.h
 *
 *  Created on: Jan 2, 2021
 *      Author: micro
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(Reg,Bit)	  	( (Reg) |= ( (1) << (Bit) ) )
#define CLR_BIT(Reg,Bit)	  	( (Reg) &= (~((1) << (Bit)) ) )
#define TGL_BIT(Reg,Bit)		( (Reg) ^= ( (1) << (Bit) ) )

#define GET_BIT(Reg,Bit)		( ( (Reg) >> (Bit) ) & (1) )
#define GET_NIB_HIGH(Reg)		( ((Reg) & 0xf0) >> 4 )
#define GET_NIB_LOW(Reg)		( (Reg) & 0x0f )

#define ASSIGN_REG(Reg,Value)   	( (Reg) = (Value) )
#define ASSIGN_NIB_HIGH(Reg,Value)	( ( (Reg) &= 0x0f ) |= ( (Value) << 4)  & 0xf0 )
#define ASSIGN_NIB_LOW(Reg,Value)	( ( (Reg) &= 0xf0 ) |= ( (Value) & 0x0f )
#define SET_REG(Reg) 				( (Reg) = 0xff ) 						 //all is  one's'
#define SET_NIB_HIGH(Reg)			( (Reg) |= 0xf0 )
#define SET_NIB_LOW(Reg)			( (Reg) |= 0x0f )

#define RST_REG(Reg) 				( (Reg) = 0x00) )						// all is zeros
#define RST_NIB_HIGH(Reg)			( (Reg) &= 0x0f )
#define RST_NIB_LOW(Reg)			( (Reg) &= 0xf0 )

#define ROT_REG_RIGHT(Reg,Step)		( Reg =  (Reg >> Step) |  ( Reg << (8-Step) ) )
#define ROT_REG_LEFT(Reg,Step)		( Reg =  (Reg << Step) |  ( Reg >> (8-Step) ) )

#define CONC(A,B,C,D,E,F,G,H)		CONC2(A,B,C,D,E,F,G,H)
#define CONC2(A,B,C,D,E,F,G,H)		0b##A##B##C##D##E##F##G##H


#define BIT_BAND(Addr,Bitnum)		*((volatile uint32_t *)((Addr & 0xF0000000)+0x2000000+((Addr & 0xFFFFF)<<5)+(Bitnum <<2)))

#endif /* BIT_MATH_H_ */




//#define SET_BIT(Reg,Bit)                 ( (Reg) |=  ( (1) << (Bit) )  )
//#define CLR_BIT(Reg,Bit)                 ( (Reg) &= ~( (1) << (Bit) )  )
//#define TGL_BIT(Reg,Bit)                 ( (Reg) ^=  ( (1) << (Bit) )  )
//
//#define GET_BIT(Reg,Bit)
//
//#define ASSIGN_REG(Reg,Value)
//#define ASSIGN_NIB_HIGH(Reg,Value)
//#define ASSIGN_NIB_LOW(Reg,Value)
//
//#define SET_REG(Reg)
//#define RST_REG(Reg)
//
//#define SET_NIB_HIGH(Reg)
//#define SET_NIB_LOW(Reg)
//
//#define RST_NIB_HIGH(Reg)
//#define RST_NIB_LOW(Reg)
//
//#define GET_NIB_HIGH(Reg)
//#define GET_NIB_LOW(Reg)
//
//#define ROT_REG_RIGHT(Reg,Step)
//#define ROT_REG_LEFT(Reg,Step)
