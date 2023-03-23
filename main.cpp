#include "PlaneSlice.h"
#include <QApplication>
#include <vtkOutputWindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    vtkOutputWindow::SetGlobalWarningDisplay(false);
    PlaneSlice w;
    w.show();
    return a.exec();
}
