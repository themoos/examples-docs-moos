/*
 * A simple example showing how to use a comms client
 */
#include "MOOS/libMOOS/Comms/MOOSAsyncCommClient.h"
#include "MOOS/libMOOS/Utils/CommandLineParser.h"
#include "MOOS/libMOOS/Utils/ConsoleColours.h"
#include "MOOS/libMOOS/Utils/ThreadPrint.h"

MOOS::ThreadPrint gPrinter(std::cout);

bool OnConnect(void * pParam){
	CMOOSCommClient* pC =  reinterpret_cast<CMOOSCommClient*> (pParam);

	//wildcard registration any two character name beginning with V
	pC->Register("V?","*",0.0);

	return true;
}

bool DefaultMail(CMOOSMsg & M, void * TheParameterYouSaidtoPassOnToCallback)
{
	gPrinter.SimplyPrintTimeAndMessage("default handler "+M.GetKey(), MOOS::ThreadPrint::CYAN);
	return true;
}

bool funcA(CMOOSMsg & M, void * TheParameterYouSaidtoPassOnToCallback)
{
	gPrinter.SimplyPrintTimeAndMessage("funcA "+M.GetKey(), MOOS::ThreadPrint::CYAN);
	return true;
}


int main(int argc, char * argv[]){

	//understand the command line
	MOOS::CommandLineParser P(argc,argv);

	std::string db_host="localhost";
	P.GetVariable("--moos_host",db_host);

	int db_port=9000;
	P.GetVariable("--moos_port",db_port);

	std::string my_name ="ex50";
	P.GetVariable("--moos_name",my_name);

	//configure the comms
	MOOS::MOOSAsyncCommClient Comms;
	Comms.SetOnConnectCallBack(OnConnect,&Comms);

	//here we add per message callbacks
	//first parameter is the channel nick-name, then the function
	//to call, then a parameter we want passed when callback is
	//invoked
	Comms.AddMessageRouteToActiveQueue("callbackA","V1",funcA,NULL);

	//add a default handler
	Comms.AddMessageRouteToActiveQueue("default","*",DefaultMail,NULL);

	//start the comms running
	Comms.Run(db_host,db_port,my_name);

	//for ever loop sending data
	std::vector<unsigned char> data(1000);
	for(;;){
		MOOSPause(10);
		Comms.Notify("V1",data); //for funcA
		Comms.Notify("V2","This is stuff"); //will be caught by default
	}
	return 0;
}
