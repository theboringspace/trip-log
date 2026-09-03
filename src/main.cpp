/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-09-03
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[])
{   
    QApplication app(argc, argv);

    QMainWindow window;
    window.setWindowTitle("Trip Log");
    window.resize(800, 600);
    window.show();

    return app.exec();
}