#include <QApplication>

#include "header/mainviewer.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainViewer w;
  Settings s;
  w.show();
  return a.exec();
}
