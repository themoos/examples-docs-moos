#include "MOOS/libMOOS/App/MOOSApp.h"
#include "MOOS/libMOOS/Thirdparty/getpot/getpot.h"

/*
 * ExampleB.cpp
 *
 *  Created on: Nov 11, 2012
 *      Author: pnewman
 */

class ExampleBApp : public CMOOSApp
{
	bool OnNewMail(MOOSMSG_LIST & Mail)
	{
		//process it
		MOOSMSG_LIST::iterator q;
		for(q=Mail.begin();q!=Mail.end();q++){
			//q->Trace();
		}
		return true;
	}
	bool OnConnectToServer()
	{
		return Register("X",0.0);
	}
	bool Iterate()
	{
		std::vector<unsigned char> X(100);
		Notify("X",X);
		return true;
	}
};

int main(int argc, char * argv[])
{
	//understand the command line
	GetPot cl(argc,argv);
	std::string db_host = cl.follow("localhost",2,"-s","--server");
	int db_port = cl.follow(9000,2,"-p","--port");
	std::string my_name = cl.follow("exampleA",2,"-n","--name");

	ExampleBApp App;

	App.Run(my_name.c_str(),"Mission.moos");

	return 0;
}
