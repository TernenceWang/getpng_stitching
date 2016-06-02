
#include <opencv2\opencv.hpp>
#include <direct.h>  //mkdir
#include <io.h>      //access
using namespace cv;
using namespace std;

//������
int main()
{
	//����·��
	string video_path;
	do
	{
		cout << "�����뺬·�����ļ��������磺D:\\Record\\in.avi��:" << endl;
		cin >> video_path;
	}while( strstr(video_path.c_str(),".avi") == NULL );
	
	//������Ӧ�ļ���
	int n = video_path.rfind(".");
	string folder_path = video_path.substr( 0, n );
	cout << folder_path <<endl;
	if(access( folder_path.c_str(), 0) == -1 )
	{
		if( mkdir ( folder_path.c_str() ) == 1 )                         //��������·�����ļ���
		cout << "����·��:" << folder_path <<  endl;
		else cout << "�����ļ���ʧ��" << endl;
	}
	else
	{
		//char cmd[128];
		
		system(( "del /f /s /q "+folder_path).c_str());
		cout << "·���Ѵ��ڣ������ͼƬ" << endl;
	}

	//��ȡͼƬ
	Mat frame;
	VideoCapture capture(video_path);    //��ȡ·��
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
	cout << "����ȡͼƬ: " << i/pass << endl << "��ȡ���Ϊ: " << pass << endl;
	waitKey();
	return 0;
}