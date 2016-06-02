
#include <opencv2\opencv.hpp>
#include <direct.h>  //mkdir
#include <io.h>      //access
using namespace cv;
using namespace std;

//主程序
int main()
{
	//输入路径
	string video_path;
	do
	{
		cout << "请输入含路径的文件名（例如：D:\\Record\\in.avi）:" << endl;
		cin >> video_path;
	}while( strstr(video_path.c_str(),".avi") == NULL );
	
	//创建对应文件夹
	int n = video_path.rfind(".");
	string folder_path = video_path.substr( 0, n );
	cout << folder_path <<endl;
	if(access( folder_path.c_str(), 0) == -1 )
	{
		if( mkdir ( folder_path.c_str() ) == 1 )                         //创建保存路径的文件夹
		cout << "保存路径:" << folder_path <<  endl;
		else cout << "创建文件夹失败" << endl;
	}
	else
	{
		//char cmd[128];
		
		system(( "del /f /s /q "+folder_path).c_str());
		cout << "路径已存在，已清空图片" << endl;
	}

	//提取图片
	Mat frame;
	VideoCapture capture(video_path);    //读取路径
	if(!capture.isOpened())
	{
		cout<<"-- Open error !"<<endl;
		return -1;
	}
	Size s=Size((int)capture.get(CAP_PROP_FRAME_WIDTH),(int)capture.get(CAP_PROP_FRAME_HEIGHT));
	int fps=capture.get(CAP_PROP_FPS);
	double count=capture.get(CAP_PROP_FRAME_COUNT);
	cout<<"fps\t"<<fps<<endl;
	cout<<"count\t"<<count<<endl;
	cout<<"Size\t"<<s.width<<"    "<<s.height<<endl;
	int i,pass;
	pass = fps * 3;
	for( i=1;  ;i++)
	{
		capture >> frame;
		if (frame.empty())
		{
			break; 
		}
		if( i%pass == 0 )
		{
			stringstream sout;
			sout << i/pass;
			imwrite( folder_path + "/" + sout.str()+".png" ,frame);
			std::cout << i/pass << std::endl;
		}
	}
	cout << "共提取图片: " << i/pass << endl << "提取间隔为: " << pass << endl;
	waitKey();
	return 0;
}