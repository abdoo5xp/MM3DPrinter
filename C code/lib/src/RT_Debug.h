#ifndef RT_Debug_H_
#define RT_Debug_H_


// Return Status***********************************************************************
typedef enum {
	RT_SUCCESS,
	RT_PARAM,
	RT_ERROR,
	RT_TIME_OUT,
	RT_BUFFER_FULL,
	RT_ALIGNMENT_ERROR,
	RT_PARALLISM_ERROR,
	RT_SEQUENCE_ERROR,
	RT_BUSY,
	RT_OK,
}RT_Debug;

// Printing Debug Messeges**************************************************************
#define debug_status(status)						do{												\
													switch (status){								\
													case 0:											\
													trace_printf("success!\n");						\
													break;											\
													case 1:											\
													trace_printf("Wrong Parameter!\n");				\
													break;											\
													case 2:											\
													trace_printf("Error Configuration!\n");			\
													break;											\
													case 3:											\
													trace_printf("%s\n","Time out");				\
													break;											\
													}}while(0)


#endif /* RT_Debug_H_ */
