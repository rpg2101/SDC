#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void conectarsock();
    void recibirsock();
    void cerrarsock();

private:
    Ui::MainWindow *ui;
    int socktcp;
    char datos[100];
};

#endif // MAINWINDOW_H
