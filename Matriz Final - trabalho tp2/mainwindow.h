#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Matriz.h"
#include "QMessageBox"
#include <QInputDialog>
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

private slots:
    void on_pushButtonCriarMatrizA_clicked();

    void on_pushButtonCriarMatrizB_clicked();

    void on_pushButton_adicao_clicked();

    void on_pushButton_subtracao_clicked();

    void on_pushButton_multiplicacao_clicked();

    void on_pushButton_transpostaA_clicked();

    void on_pushButton_Exponencial_A_clicked();

    void on_pushButton_transpostaB_clicked();

    void on_pushButton_Exponencial_B_clicked();

    void on_pushButton_Multiplicar_A_clicked();

    void on_pushButton_Multiplicar_B_clicked();

private:
    Ui::MainWindow *ui;
    tp2::Matriz *mA;
    tp2::Matriz *mB;
};

#endif // MAINWINDOW_H
