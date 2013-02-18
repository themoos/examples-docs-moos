#include "MOOS/libMOOS/Comms/MOOSAsyncCommClient.h"

bool OnConnect(void * pParam){
	CMOOSCommClient* pC =  reinterpret_cast<CMOOSCommClient*> (pParam);
	pC->Register("Greeting",0.0);
	return true;
}

bool OnMail(void *pParam){
	CMOOSCommClient* pC = reinterpret_cast<CMOOSCommClient*>(pParam);
	MOOSMSG_LIST M;
	pC->Fetch(M); //get the mail
	MOOSMSG_LIST::iterator q; //process it
	for(q=M.begin();q!=M.end();q++){
		q->Trace();
	}
	return true;
}

int main(int argc, char * argv[]){

	//configure the comms
	MOOS::MOOSAsyncCommClient Comms;
	Comms.SetOnMailCallBack(OnMail,&Comms);
	Comms.SetOnConnectCallBack(OnConnect,&Comms);

	//start the comms running
	Comms.Run("localhost",9000,"EX20");

	for(;;){
		MOOSPause(1000);
		Comms.Notify("Greeting","Hello");
	}
	return 0;
}
