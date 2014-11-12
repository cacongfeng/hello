#include <iostream>
using namespace std;
/*思路：使用fread每次读入一个字节存入字符中，由于一个字节为8位二进制数，对应ASCII编码会生成不同字符，由于字节对齐，讲读入的字符按结构体顺序转化为相应数据。
在C++中byte被定义的是unsigned char类型,根据char型1个字节，int型4个字节，float型4个字节对应文件头的数据结构进行存储，
查看了图像数据对应的卫星、传感器型号，图像宽度，采样率及处理模式等基本信息*/


unsigned char biti[180];	//定义一个数组用于暂存取出来的dat二进制数

typedef struct _tadBL
{
	float longitude;
	float latituede;
}LONLAT_POS;

typedef struct _tagTimeInfo
{
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;
	int nsec;
}_TIMESTAMP;

typedef struct
{
	char station_id[16];	//接受该数据的地面站标识
	char satellite_id[16];	//对应的卫星标识
	char sensor_id[16];		//对应的传感器标识
	char work_mode[16];		//对应的工作模式信息
	char JobTaskID[20];		//任务标识
	int orbit_num;		//轨道号
	int channel_num;	//通道号
	int totalfiles;		//本任务单传输快视文件总数
	int files_num;		//本次传输的文件在所属任务中的文件序号
	int desample_num;		//进行快数处理时的降采样数，上一部的降采样数
	int data_width;		//上一步传进来的宽度（如果做降采样，这里会进一步变小）
	int sample_bit_count;		//快视处理后的图像量化比特数，只有8Bit和16Bit两种情况
	int gray_image_flag;		//当此值为真时，该图像为单通道灰度图像，否则为多通道伪彩色图像
	_TIMESTAMP start_time;		//数据接收的开始时间
	_TIMESTAMP end_time;		//数据接受的结束时间
	LONLAT_POS station_pos; 	//对应的地面站在地球上的位置信息 地面站的位信息
}QUIVIMAGE_HEAD_INFO;

int bytesToInt(unsigned char* bytes,int size = 4)	//char转int
{
    int addr = bytes[0] & 0xFF;
    addr |= ((bytes[1] << 8) & 0xFF00);
    addr |= ((bytes[2] << 16) & 0xFF0000);
    addr |= ((bytes[3] << 24) & 0xFF000000);
    return addr;
 }
 

int main()
{
	FILE *fi;
	unsigned char chi;//设置变量存放从dat中取出的字符变量
	if((fi=fopen("D:\\lINUX\\Work\\RADI\\HJ快视\\HJ1A_C1_032122_20140825_MY000_S1.dat","rb"))==NULL)
	{
		cout<<"Cannot open file，exit!";
		getchar();
		exit(1);
	}
	
	QUIVIMAGE_HEAD_INFO test;	//用结构体新建一个实例

	int i=0;
	while(!feof(fi)&&i<180)
	{	  
			fread(&chi,sizeof(unsigned char),1,fi);
			biti[i]=chi;
			i++;		
	}
	
	cout<<"接受该数据的地面站标识:"<<endl;
	for(int j=0;j<16;j++)
	{
		test.station_id[j]=biti[j];
		cout<<test.station_id[j];
	}
	cout<<endl;

	cout<<"对应的卫星标识:"<<endl;
	for(int j=0;j<16;j++)
	{
		test.satellite_id[j]=biti[j+16];
		cout<<test.satellite_id[j];
	}
	cout<<endl;

	cout<<"对应的传感器标识:"<<endl;
	for(int j=0;j<16;j++)
	{
		test.sensor_id[j]=biti[j+32];
		cout<<test.sensor_id[j];
	}
	cout<<endl;

	cout<<"对应的工作模式信息:"<<endl;
	for(int j=0;j<16;j++)
	{
		test.work_mode[j]=biti[j+48];
		cout<<test.work_mode[j];
	}
	cout<<endl;

	cout<<"任务标识:"<<endl;
	for(int j=0;j<20;j++)
	{
		test.JobTaskID[j]=biti[j+64];
		cout<<test.JobTaskID[j];
	}
	cout<<endl;

	cout<<"轨道号:"<<endl;
	test.orbit_num=bytesToInt(&biti[84]);
	cout<<test.orbit_num<<endl;

	cout<<"通道号:"<<endl;
	test.channel_num=bytesToInt(&biti[88]);
	cout<<test.channel_num<<endl;

	cout<<"本任务单传输快视文件总数:"<<endl;
	test.totalfiles=bytesToInt(&biti[92]);
	cout<<test.totalfiles<<endl;

	cout<<"本次传输的文件在所属任务中的文件序号:"<<endl;
	test.files_num=bytesToInt(&biti[96]);
	cout<<test.files_num<<endl;

	cout<<"进行快数处理时的降采样数:"<<endl;
	test.desample_num=bytesToInt(&biti[100]);
	cout<<test.desample_num<<endl;

	cout<<"上一步传进来的宽度:"<<endl;
	test.data_width=bytesToInt(&biti[104]);
	cout<<test.data_width<<endl;

	cout<<"快视处理后的图像量化比特数:"<<endl;
	test.sample_bit_count=bytesToInt(&biti[108]);
	cout<<test.sample_bit_count<<endl;


	cout<<"当此值为真时，该图像为单通道灰度图像，否则为多通道伪彩色图像:"<<endl;
	test.gray_image_flag=bytesToInt(&biti[112]);
	cout<<test.gray_image_flag<<endl;

	cout<<"数据接收的开始时间:"<<endl;
	test.start_time.year=bytesToInt(&biti[116]);
	test.start_time.mon=bytesToInt(&biti[120]);
	test.start_time.day=bytesToInt(&biti[124]);
	test.start_time.hour=bytesToInt(&biti[128]);
	test.start_time.min=bytesToInt(&biti[132]);
	test.start_time.sec=bytesToInt(&biti[136]);
	test.start_time.nsec=bytesToInt(&biti[140]);

	cout<<test.start_time.year<<"年"<<test.start_time.mon<<"月"<<test.start_time.day<<"日"<<test.start_time.hour<<"时"<<test.start_time.min<<"分"<<test.start_time.sec<<"秒"<<test.start_time.nsec<<"毫秒"<<endl;

	cout<<"数据接受的结束时间:"<<endl;
	test.end_time.year=bytesToInt(&biti[144]);
	test.end_time.mon=bytesToInt(&biti[148]);
	test.end_time.day=bytesToInt(&biti[152]);
	test.end_time.hour=bytesToInt(&biti[156]);
	test.end_time.min=bytesToInt(&biti[160]);
	test.end_time.sec=bytesToInt(&biti[164]);
	test.end_time.nsec=bytesToInt(&biti[168]);

	cout<<test.end_time.year<<"年"<<test.end_time.mon<<"月"<<test.end_time.day<<"日"<<test.end_time.hour<<"时"<<test.end_time.min<<"分"<<test.end_time.sec<<"秒"<<test.end_time.nsec<<"毫秒"<<endl;

	cout<<"对应的地面站在地球上的位置信息:"<<endl;
	test.station_pos.latituede=bytesToInt(&biti[172]);
	test.station_pos.longitude=bytesToInt(&biti[176]);

	cout<<"经度："<<test.station_pos.latituede<<"纬度："<<test.station_pos.longitude<<endl;

	cout<<"读取完毕";
	fclose(fi);
	getchar();
}