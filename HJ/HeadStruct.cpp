#include <iostream>
using namespace std;
/*˼·��ʹ��freadÿ�ζ���һ���ֽڴ����ַ��У�����һ���ֽ�Ϊ8λ������������ӦASCII��������ɲ�ͬ�ַ��������ֽڶ��룬��������ַ����ṹ��˳��ת��Ϊ��Ӧ���ݡ�
��C++��byte���������unsigned char����,����char��1���ֽڣ�int��4���ֽڣ�float��4���ֽڶ�Ӧ�ļ�ͷ�����ݽṹ���д洢��
�鿴��ͼ�����ݶ�Ӧ�����ǡ��������ͺţ�ͼ���ȣ������ʼ�����ģʽ�Ȼ�����Ϣ*/


unsigned char biti[180];	//����һ�����������ݴ�ȡ������dat��������

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
	char station_id[16];	//���ܸ����ݵĵ���վ��ʶ
	char satellite_id[16];	//��Ӧ�����Ǳ�ʶ
	char sensor_id[16];		//��Ӧ�Ĵ�������ʶ
	char work_mode[16];		//��Ӧ�Ĺ���ģʽ��Ϣ
	char JobTaskID[20];		//�����ʶ
	int orbit_num;		//�����
	int channel_num;	//ͨ����
	int totalfiles;		//�����񵥴�������ļ�����
	int files_num;		//���δ�����ļ������������е��ļ����
	int desample_num;		//���п�������ʱ�Ľ�����������һ���Ľ�������
	int data_width;		//��һ���������Ŀ�ȣ��������������������һ����С��
	int sample_bit_count;		//���Ӵ�����ͼ��������������ֻ��8Bit��16Bit�������
	int gray_image_flag;		//����ֵΪ��ʱ����ͼ��Ϊ��ͨ���Ҷ�ͼ�񣬷���Ϊ��ͨ��α��ɫͼ��
	_TIMESTAMP start_time;		//���ݽ��յĿ�ʼʱ��
	_TIMESTAMP end_time;		//���ݽ��ܵĽ���ʱ��
	LONLAT_POS station_pos; 	//��Ӧ�ĵ���վ�ڵ����ϵ�λ����Ϣ ����վ��λ��Ϣ
}QUIVIMAGE_HEAD_INFO;

int bytesToInt(unsigned char* bytes,int size = 4)	//charתint
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
	unsigned char chi;//���ñ�����Ŵ�dat��ȡ�����ַ�����
	if((fi=fopen("D:\\lINUX\\Work\\RADI\\HJ����\\HJ1A_C1_032122_20140825_MY000_S1.dat","rb"))==NULL)
	{
		cout<<"Cannot open file��exit!";
		getchar();
		exit(1);
	}
	
	QUIVIMAGE_HEAD_INFO test;	//�ýṹ���½�һ��ʵ��

	int i=0;
	while(!feof(fi)&&i<180)
	{	  
			fread(&chi,sizeof(unsigned char),1,fi);
			biti[i]=chi;
			i++;		
	}
	
	cout<<"���ܸ����ݵĵ���վ��ʶ:"<<endl;
	for(int j=0;j<16;j++)
	{
		test.station_id[j]=biti[j];
		cout<<test.station_id[j];
	}
	cout<<endl;

	cout<<"��Ӧ�����Ǳ�ʶ:"<<endl;
	for(int j=0;j<16;j++)
	{
		test.satellite_id[j]=biti[j+16];
		cout<<test.satellite_id[j];
	}
	cout<<endl;

	cout<<"��Ӧ�Ĵ�������ʶ:"<<endl;
	for(int j=0;j<16;j++)
	{
		test.sensor_id[j]=biti[j+32];
		cout<<test.sensor_id[j];
	}
	cout<<endl;

	cout<<"��Ӧ�Ĺ���ģʽ��Ϣ:"<<endl;
	for(int j=0;j<16;j++)
	{
		test.work_mode[j]=biti[j+48];
		cout<<test.work_mode[j];
	}
	cout<<endl;

	cout<<"�����ʶ:"<<endl;
	for(int j=0;j<20;j++)
	{
		test.JobTaskID[j]=biti[j+64];
		cout<<test.JobTaskID[j];
	}
	cout<<endl;

	cout<<"�����:"<<endl;
	test.orbit_num=bytesToInt(&biti[84]);
	cout<<test.orbit_num<<endl;

	cout<<"ͨ����:"<<endl;
	test.channel_num=bytesToInt(&biti[88]);
	cout<<test.channel_num<<endl;

	cout<<"�����񵥴�������ļ�����:"<<endl;
	test.totalfiles=bytesToInt(&biti[92]);
	cout<<test.totalfiles<<endl;

	cout<<"���δ�����ļ������������е��ļ����:"<<endl;
	test.files_num=bytesToInt(&biti[96]);
	cout<<test.files_num<<endl;

	cout<<"���п�������ʱ�Ľ�������:"<<endl;
	test.desample_num=bytesToInt(&biti[100]);
	cout<<test.desample_num<<endl;

	cout<<"��һ���������Ŀ��:"<<endl;
	test.data_width=bytesToInt(&biti[104]);
	cout<<test.data_width<<endl;

	cout<<"���Ӵ�����ͼ������������:"<<endl;
	test.sample_bit_count=bytesToInt(&biti[108]);
	cout<<test.sample_bit_count<<endl;


	cout<<"����ֵΪ��ʱ����ͼ��Ϊ��ͨ���Ҷ�ͼ�񣬷���Ϊ��ͨ��α��ɫͼ��:"<<endl;
	test.gray_image_flag=bytesToInt(&biti[112]);
	cout<<test.gray_image_flag<<endl;

	cout<<"���ݽ��յĿ�ʼʱ��:"<<endl;
	test.start_time.year=bytesToInt(&biti[116]);
	test.start_time.mon=bytesToInt(&biti[120]);
	test.start_time.day=bytesToInt(&biti[124]);
	test.start_time.hour=bytesToInt(&biti[128]);
	test.start_time.min=bytesToInt(&biti[132]);
	test.start_time.sec=bytesToInt(&biti[136]);
	test.start_time.nsec=bytesToInt(&biti[140]);

	cout<<test.start_time.year<<"��"<<test.start_time.mon<<"��"<<test.start_time.day<<"��"<<test.start_time.hour<<"ʱ"<<test.start_time.min<<"��"<<test.start_time.sec<<"��"<<test.start_time.nsec<<"����"<<endl;

	cout<<"���ݽ��ܵĽ���ʱ��:"<<endl;
	test.end_time.year=bytesToInt(&biti[144]);
	test.end_time.mon=bytesToInt(&biti[148]);
	test.end_time.day=bytesToInt(&biti[152]);
	test.end_time.hour=bytesToInt(&biti[156]);
	test.end_time.min=bytesToInt(&biti[160]);
	test.end_time.sec=bytesToInt(&biti[164]);
	test.end_time.nsec=bytesToInt(&biti[168]);

	cout<<test.end_time.year<<"��"<<test.end_time.mon<<"��"<<test.end_time.day<<"��"<<test.end_time.hour<<"ʱ"<<test.end_time.min<<"��"<<test.end_time.sec<<"��"<<test.end_time.nsec<<"����"<<endl;

	cout<<"��Ӧ�ĵ���վ�ڵ����ϵ�λ����Ϣ:"<<endl;
	test.station_pos.latituede=bytesToInt(&biti[172]);
	test.station_pos.longitude=bytesToInt(&biti[176]);

	cout<<"���ȣ�"<<test.station_pos.latituede<<"γ�ȣ�"<<test.station_pos.longitude<<endl;

	cout<<"��ȡ���";
	fclose(fi);
	getchar();
}