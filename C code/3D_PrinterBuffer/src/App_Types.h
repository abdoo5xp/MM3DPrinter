/*
 * App_Types.h
 *
 *  Created on: Jun 25, 2021
 *      Author: abdoo
 */

#ifndef APP_TYPES_H_
#define APP_TYPES_H_

typedef enum{
	GcodeParser_ExtrudeMaterial,
	GcodeParser_ChangeFeedRate,
	GcodeParser_SwapMaterial
}GcodeParser_ActionTypes_e;

typedef enum {
	APP_GcodeNotEnd ,
	APP_GcodeEnd	,
}APP_GcodeEndStatus_e;

typedef struct {
	GcodeParser_ActionTypes_e action;
	uint32_t MaterialLength_um;
	uint32_t Direction;  			 /*one of the Extruder DIR Macros*/
	uint32_t FeedRate;
	uint8_t  Material;				 /* EXTRUDER_M_1, EXTRUDER_M_2, EXTRUDER_M_3, EXTRUDER_E */
	uint8_t OldMaterial;			/*This will contain the old material if swap maerial type is selected */
}GcodeParser_Action_t;



#endif /* APP_TYPES_H_ */
