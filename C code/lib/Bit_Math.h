/*
 * Bit_Math.h
 *
 *  Created on: Jan 25, 2021
 *      Author: abdoo
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_BIT(Reg,Bit)                 ( (Reg) |=  ( (1) << (Bit) )  )
#define CLR_BIT(Reg,Bit)                 ( (Reg) &= ~( (1) << (Bit) )  )
#define TGL_BIT(Reg,Bit)                 ( (Reg) ^=  ( (1) << (Bit) )  )

#define GET_BIT(Reg,Bit)        		 ( ( (Reg) >> (Bit) ) & (1)    )

#define ASSIGN_REG(Reg,Value)			 ( (Reg)  =  ( Value )  )
#define ASSIGN_NIB_HIGH(Reg,Value)		 ( (Reg)  =  ( ( (Value) << (4) ) | ((Reg)   & (0x0F)) )  )
#define ASSIGN_NIB_LOW(Reg,Value)		 ( (Reg)  =  ( ( (Reg) & (0xF0))  | ((Value) & (0x0F)) )  )

#define SET_REG(Reg)					 ( (Reg)  =  (0xFF)  )
#define RST_REG(Reg)					 ( (Reg)  =  (0x00)  )

#define SET_NIB_HIGH(Reg)			     ( (Reg)  |=  (0xF0)  )
#define SET_NIB_LOW(Reg)				 ( (Reg)  |=  (0x0F)  )

#define RST_NIB_HIGH(Reg) 				 ( (Reg)  &=  (0x0F)  )
#define RST_NIB_LOW(Reg)			     ( (Reg)  &=  (0xF0)  )

#define GET_NIB_HIGH(Reg)                ( ( (Reg) & (0xF0)) >> (4)  )
#define GET_NIB_LOW(Reg)				 (   (Reg) & (0x0F)  )
/* CONV_TO_ONES(Num) takes the decimal or hex number and converts it to the corresponding number of ones (e.g: 3 --> 0000 0111)*/
#define CONV_TO_ONES(Num)				~( (0xFF) << (Num) )
#define ROT_REG_RIGHT(Reg,Step)			 ( (Reg) = ( ( ( (Reg) & CONV_TO_ONES(Step) ) << (8-Step) ) 			  | ( (Reg) >> (Step) ) ) )
#define ROT_REG_LEFT(Reg,Step)			 ( (Reg) = ( ( ( (Reg) & ( CONV_TO_ONES(Step) << (8-Step) ) >> (8-Step) ) | ( (Reg) << (Step) ) ) )

/*Concatenate seven bits together*/
#define RCONC(b7,b6,b5,b4,b3,b2,b1,b0)			0b##b7##b6##b5##b4##b3##b2##b1##b0
#define CONC(b7,b6,b5,b4,b3,b2,b1,b0)			RCONC(b7,b6,b5,b4,b3,b2,b1,b0)


#endif /* BIT_MATH_H_ */
