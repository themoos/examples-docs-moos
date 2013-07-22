/*
 * simple MOOSApp example
 */

#include "MOOS/libMOOS/App/MOOSApp.h"

class ExampleApp : public CMOOSApp
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
	//here we do some command line parsing...
	MOOS::CommandLineParser P(argc,argv);

	//mission file could be first free parameter
	std::string mission_file = P.GetFreeParameter(0, "Mission.moos");

	//app name can be the  second free parameter
	std::string app_name = P.GetFreeParameter(1, "ex1000");

	ExampleApp App;

	App.Run(app_name,mission_file,argc,argv);

	return 0;
}
