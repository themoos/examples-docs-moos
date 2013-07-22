/*
 * A simple example showing how to use a comms client
 */
#include "MOOS/libMOOS/Comms/MOOSAsyncCommClient.h"
#include "MOOS/libMOOS/Utils/CommandLineParser.h"
#include "MOOS/libMOOS/Utils/ConsoleColours.h"
#include "MOOS/libMOOS/Utils/ThreadPrint.h"

MOOS::ThreadPrint gPrinter(std::cout);


bool OnConnect1(void * pParam){
	CMOOSCommClient* pC =  reinterpret_cast<CMOOSCommClient*> (pParam);

	//wildcard registration for any variable from a client who's name begins with C
	return pC->Register("*","C*",0.0);
}

bool OnConnect2(void * pParam){
	CMOOSCommClient* pC =  reinterpret_cast<CMOOSCommClient*> (pParam);

	//wildcard registration any two character name beginning with V
	//from a client who's name ends in "2"
	return pC->Register("V?","*2",0.0);
}

bool OnConnect3(void * pParam){
	CMOOSCommClient* pC =  reinterpret_cast<CMOOSCommClient*> (pParam);

	//wildcard registration for everything
	return pC->Register("*","*",0.0);
}


bool DefaultMail(CMOOSMsg & M, void * TheParameterYouSaidtoPassOnToCallback)
{
	CMOOSCommClient* pC =  reinterpret_cast<CMOOSCommClient*> (TheParameterYouSaidtoPassOnToCallback);

	gPrinter.SimplyPrintTimeAndMessage(pC->GetMOOSName()+ " : Rx : "+M.GetKey()+
			" from "+ M.GetSource(),
			MOOS::ThreadPrint::GREEN);

	return true;
}


int main(int argc, char * argv[]){

	//understand the command line
	MOOS::CommandLineParser P(argc,argv);

	std::string db_host="localhost";
	P.GetVariable("--moos_host",db_host);

	int db_port=9000;
	P.GetVariable("--moos_port",db_port);

	std::string my_name ="ex60";
	P.GetVariable("--moos_name",my_name);

	//configure the comms
	MOOS::MOOSAsyncCommClient Comms1;
	Comms1.SetOnConnectCallBack(OnConnect1,&Comms1);
	Comms1.AddMessageCallback("default","*",DefaultMail,&Comms1);
	Comms1.Run(db_host,db_port,"C-"+my_name+"-1");

	MOOS::MOOSAsyncCommClient Comms2;
	Comms2.SetOnConnectCallBack(OnConnect2,&Comms2);
	Comms2.AddMessageCallback("default","*",DefaultMail,&Comms2);
	Comms2.Run(db_host,db_port,"C-"+my_name+"-2");

	MOOS::MOOSAsyncCommClient Comms3;
	Comms3.SetOnConnectCallBack(OnConnect3,&Comms3);
	Comms3.AddMessageCallback("default","*",DefaultMail,&Comms3);
	Comms3.Run(db_host,db_port,"C-"+my_name+"-3");

	//for ever loop sending data
	std::vector<unsigned char> data(1000);
	for(;;){
		MOOSPause(10);
		Comms1.Notify("V1",data);
		Comms1.Notify("V1",data);

		Comms1.Notify("V2","This is stuff");
		Comms2.Notify("V2","This is stuff");
	}
	return 0;
}
