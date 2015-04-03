#include "qt1.h"
#include "my.h"

//#include "libFixApi.h"

//#include "WINDEF.H"

#include <iostream>
#include <QPushButton>


using namespace std;

void QTAPI_invoke_DLL();

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qt1 w;
	w.show();

	//QPushButton qBtn("quit",0);
	//qBtn.resize(100, 300);
	//QObject::connect(&qBtn, SIGNAL(click()), &a, SLOT(quit()));
	
	QTAPI_invoke_DLL();

	return a.exec();
}

void QTAPI_invoke_DLL()
{
	typedef bool(*myClose)(long);

	QLibrary myLib("FixApi.dll");
	long conn;
	if (myLib.load())
	{
		cout << "success : load dll !" << endl;
		M_Connect m_connect = (M_Connect)myLib.resolve("Fix_Connect");
		conn = m_connect("192.168.35.170@9103/tcp","003636000306","123321",10L);

		M_Close m_close = (M_Close)myLib.resolve("Fix_Close");
		if (m_close(conn))
		{
			cout << "close connection success !" << endl;
		}
		
	}
	else
	{
		cout << "failed : load dll !" << endl;
	}
}

