#include <QApplication>

#include "auth.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Auth authW;
    authW.show();

    return app.exec();
}
