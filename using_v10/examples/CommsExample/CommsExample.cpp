/*
 * ExampleA.cpp
 *
 *  Created on: Nov 10, 2012
 *      Author: pnewman
 */
#include "MOOS/libMOOS/Comms/MOOSAsyncCommClient.h"
#include "MOOS/libMOOS/Thirdparty/getpot/getpot.h"


bool OnConnect(void * pParam)
{
	CMOOSCommClient* pC =  reinterpret_cast<CMOOSCommClient*> (pParam);
	pC->Register("X",0.0);
	return true;
}

bool OnMail(void *pParam)
{
	CMOOSCommClient* pC = reinterpret_cast<CMOOSCommClient*>(pParam);

	//get the mail
	MOOSMSG_LIST M;
	pC->Fetch(M);

	//process it
	MOOSMSG_LIST::iterator q;
	for(q=M.begin();q!=M.end();q++){
		q->Trace();
	}

	return true;
}

int main(int argc, char * argv[])
{
	//understand the command line
	GetPot cl(argc,argv);
	std::string db_host = cl.follow("localhost",2,"-s","--server");
	int db_port = cl.follow(9000,2,"-p","--port");
	std::string my_name = cl.follow("exampleA",2,"-n","--name");

	//configure the comms
	MOOS::MOOSAsyncCommClient Comms;
	Comms.SetOnMailCallBack(OnMail,&Comms);
	Comms.SetOnConnectCallBack(OnConnect,&Comms);

	//start the comms running
	Comms.Run(db_host,db_port,my_name);

	//for ever loop sending data
	std::vector<unsigned char> X(100);
	for(;;)
	{
		MOOSPause(1000);
		Comms.Notify("X",X);
	}

	return 0;
}
