
#include <QApplication>
#include <QLibrary>
#include <QLabel>

typedef long(*M_Connect)(const char *, const char *, const char *, long);
typedef long(*M_Close)(long);

using namespace std;

