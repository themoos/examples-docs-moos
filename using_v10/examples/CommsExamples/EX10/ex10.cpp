#include "MOOS/libMOOS/Comms/MOOSAsyncCommClient.h"

bool OnConnect(void * pParam){
	CMOOSCommClient* pC =  reinterpret_cast<CMOOSCommClient*> (pParam);
	pC->Register("Greeting",0.0);
	return true;
}



int main(int argc, char * argv[]){

	//configure the comms
	MOOS::MOOSAsyncCommClient Comms;
	Comms.SetOnConnectCallBack(OnConnect,&Comms);

	//start the comms running
	Comms.Run("localhost",9000,"EX10");

	MOOSMSG_LIST M;
	for(;;){
		MOOSPause(1000);
		Comms.Notify("Greeting","Hello");
		Comms.Fetch(M);
		MOOSMSG_LIST::iterator q;
		for(q = M.begin();q!=M.end();q++)
		{
			q->Trace();
		}
	}
	return 0;
}
