
#ifdef WIN32  
#include <WTypes.h>  
#endif 
typedef struct  PCmdWlanToCPU
{
	char  StartID =0;
	char  Res1= 0;
	short VolVal = 0;

	int   FreqVal = 0;
	int DutyVal1= 0;              //D high 
	int DutyVal2 =0;				//D low

	char  Channle[2];
	//short  Res2 ;
	char  mode= 0;
	char  EndID = 0;
	//char  Phase;
}PCmdWlanToCPU;

