#include "qt11.h"
// #include "my11.h"
#include <QApplication>
#include <QLibrary>
#include <QLabel>

typedef long(*M_Connect)(const char *, const char *, const char *, long);
typedef long(*M_Close)(long);

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qt11 w;
	w.show();
	
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
		QTextStream out(cout);
		out << "success : load dll !" << endl;
		M_Connect m_connect = (M_Connect)myLib.resolve("Fix_Connect");
		conn = m_connect("192.168.35.170@9103/tcp", "003636000306", "123321", 10L);

		M_Close m_close = (M_Close)myLib.resolve("Fix_Close");
		if (m_close(conn))
		{
			out << "close connection success !" << endl;
		}

	}
	else
	{
		cout << "failed : load dll !" << endl;
	}
}
