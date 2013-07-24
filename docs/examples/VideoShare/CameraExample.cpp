#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "MOOS/libMOOS/App/MOOSApp.h"


using namespace cv;
class CameraApp : public CMOOSApp
{
public:
	bool Iterate()
	{
		if(server_){
			vc_>>capture_frame_;
			if(capture_frame_.data!=NULL)
			{
				cv::cvtColor(capture_frame_, bw_image_, COLOR_BGR2GRAY);
				cv::resize(bw_image_, image_, image_.size(), 0, 0, cv::INTER_NEAREST);
				Notify("Image",(void*)image_.data,image_.size().area(),MOOSLocalTime());
			}
			else
			{
				std::cerr<<"no image read from camera..\n";
			}
		}
		else{
	        cv::imshow("display", image_);
	        cv::waitKey(10);
		}
        return true;
	}
	bool OnStartUp()
	{
		SetAppFreq(20,400);
		SetIterateMode(COMMS_DRIVEN_ITERATE_AND_MAIL);

		image_ = cv::Mat(378,512,CV_8UC1);
		bw_image_ = cv::Mat(378,512,CV_8UC1);

		if(server_){
			if(!vc_.open(0))
			{
				std::cerr<<"camera open FAIL\n";

				return false;
			}
			else
				std::cerr<<"camera opened OK\n";

			//vc_.set(cv::CAP_PROP_SATURATION,0);
		}
		else{
		    cv::namedWindow("display",1);
		}

		return true;
	}
	void OnPrintHelpAndExit()
	{
		PrintDefaultCommandLineSwitches();
		std::cout<<"\napplication specific help:\n";
		std::cout<<"  --serve            : be a video server grabs and sends images (no window)\n";
		exit(0);
	}
	void OnPrintExampleAndExit()
	{
		std::cout<<" ./video_share --serve    \n";
		std::cout<<" and on another terminal..\n";
		std::cout<<" ./video_share       \n";
		exit(0);
	}

	bool OnProcessCommandLine()
	{
		server_=m_CommandLineParser.GetFlag("--serve");

		return true;
	}
	bool OnNewMail(MOOSMSG_LIST & mail)
	{
		MOOSMSG_LIST::iterator q;
		for(q = mail.begin();q!=mail.end();q++){
			if(q->IsName("Image")){
				std::cerr<<"bytes: "<<q->GetBinaryDataSize()<<" latency "<<
						std::setprecision(3)<<(MOOSLocalTime()-q->GetTime())*1e3<<" ms\r";

				memcpy(image_.data,q->GetBinaryData(),
						q->GetBinaryDataSize());
			}
		}
		return true;
	}
	bool OnConnectToServer()
	{
		if(!server_)
			Register("Image",0.0);
		return true;
	}
protected:
	cv::VideoCapture vc_;
	cv::Mat capture_frame_,bw_image_,image_;
	bool server_;


};
int main(int argc, char* argv[])
{
	//here we do some command line parsing...
	MOOS::CommandLineParser P(argc,argv);
	//mission file could be first free parameter
	std::string mission_file = P.GetFreeParameter(0, "Mission.moos");
	//app name can be the  second free parameter
	std::string app_name = P.GetFreeParameter(1, "CameraTest");

    CameraApp App;
	App.Run(app_name,mission_file,argc,argv);

    return 0;
}
