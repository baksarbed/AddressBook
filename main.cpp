#include "addressbook.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    AddressBook book;
    book.show();

    return app.exec();
}
