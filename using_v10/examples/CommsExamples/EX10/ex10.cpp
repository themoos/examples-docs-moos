#include "MOOS/libMOOS/Comms/MOOSAsyncCommClient.h"

//this is called when the client connects to the MOOSDB
bool OnConnect(void * pParam){
	CMOOSCommClient* pC =  reinterpret_cast<CMOOSCommClient*> (pParam);
	pC->Register("Greeting",0.0);
	return true;
}


int main(int argc, char * argv[]){

	//configure the comms
	MOOS::MOOSAsyncCommClient Comms;

	//set up the connect callback
	Comms.SetOnConnectCallBack(OnConnect,&Comms);

	//start the comms running
	Comms.Run("localhost",9000,"EX10");

	while(1){

		//make this loop run once a second
		MOOSPause(1000);

		//send a message (to ourself)
		Comms.Notify("Greeting","Hello");

		//pick up any mesages
		MOOSMSG_LIST M;
		Comms.Fetch(M);

		//print them all out
		MOOSMSG_LIST::iterator q;
		for(q = M.begin();q!=M.end();q++)
		{
			//print out details about the message
			q->Trace();
		}
	}
	return 0;
}
