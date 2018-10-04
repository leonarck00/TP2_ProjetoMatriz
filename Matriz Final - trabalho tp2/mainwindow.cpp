#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Matriz.h"
#include<QString>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mA(0)
{
    ui->setupUi(this);
    ui->lineEditQuaLinhas->setValidator(new QRegExpValidator(QRegExp("[0-9]{0,9}"), this));//Validação para digitar somente numeros
    ui->lineEditQuaColunas->setValidator(new QRegExpValidator(QRegExp("[0-9]{0,9}"), this));
    ui->lineEditQuaLinhasB->setValidator(new QRegExpValidator(QRegExp("[0-9]{0,9}"), this));
    ui->lineEditQuaColunasB->setValidator(new QRegExpValidator(QRegExp("[0-9]{0,9}"), this));
    ui->lineEdit_Exponencial_A->setValidator(new QRegExpValidator(QRegExp("[0-9]{0,9}"),this));
    ui->lineEdit_Exponencial_B->setValidator(new QRegExpValidator(QRegExp("[0-9]{0,9}"),this));
    ui->lineEdit_Multiplicar_A->setValidator(new QRegExpValidator(QRegExp("[0-9]{0,9}"),this));
    ui->lineEdit_Multiplicar_B->setValidator(new QRegExpValidator(QRegExp("[0-9]{0,9}"),this));

    ui->pushButtonCriarMatrizB->setEnabled(false);//desabilitador de botoes
    ui->pushButton_adicao->setEnabled(false);
    ui->pushButton_subtracao->setEnabled(false);
    ui->pushButton_multiplicacao->setEnabled(false);
    ui->pushButton_Exponencial_A->setEnabled(false);
    ui->pushButton_Exponencial_B->setEnabled(false);
    ui->pushButton_Multiplicar_A->setEnabled(false);
    ui->pushButton_Multiplicar_B->setEnabled(false);
    ui->pushButton_transpostaA->setEnabled(false);
    ui->pushButton_transpostaB->setEnabled(false);
}

MainWindow::~MainWindow()
{
    if(mA)delete mA;//deletar matriz a
    delete ui;
    if(mB)delete mB;//deletar matriz b
    delete ui;
}
void MainWindow::on_pushButtonCriarMatrizA_clicked()
{
   try
    {
       int quantidadeLinhas;
       int quantidadeColunas;
       quantidadeLinhas=ui->lineEditQuaLinhas ->text().toInt();//conversao
       quantidadeColunas=ui->lineEditQuaColunas ->text().toInt();

       mA=new tp2::Matriz(quantidadeLinhas,quantidadeColunas);// criando a matriz com construtor
       for(int l=0;l<quantidadeLinhas;l++)
       {
          for(int c=0;c<quantidadeColunas;c++)
          {
              int elemento = QInputDialog::getInt(this , "Leitura",
              "Matriz A ["+QString::number(l)+","+QString::number(c)+"]=");
              mA->setElemento(elemento,l,c);
           }
       }


       ui->textEditSaidaMa->setText(mA->getMatriz());

       ui->pushButtonCriarMatrizB->setEnabled(true);//habilitador dos botoes
       ui->pushButton_Multiplicar_A->setEnabled(true);
       ui->pushButton_Exponencial_A->setEnabled(true);
       ui->pushButton_transpostaA->setEnabled(true);

       //Grid

       //Simetrica
       QString x = QString::number(mA->simetrica());
       if(x=="0") {x = "Não";}
       else {x="Sim";}
       QTableWidgetItem *itemE = new QTableWidgetItem(x);
       ui->tableWidget_resultado->setItem(6,0,itemE);

       //Triangular superior
       QString y = QString::number(mA->triangularsuperior());
       if(y=="0") {y = "Não";}
       else {y = "Sim";}
       QTableWidgetItem *itemF = new QTableWidgetItem(y);
       ui->tableWidget_resultado->setItem(3,0,itemF);

       //Triangular inferior
       QString z = QString::number(mA->triangularsuperior());
       if(z=="0") {z = "Não";}
       else {z = "Sim";}
       QTableWidgetItem *itemG = new QTableWidgetItem(z);
       ui->tableWidget_resultado->setItem(4,0,itemG);

       //Identidade
       QString w =QString::number(mA->identidade());
       if(w=="0"){w = "Não";}
       else {w = "Sim";}
       QTableWidgetItem *itemH = new QTableWidgetItem(w);
       ui->tableWidget_resultado->setItem(2,0,itemH);

       //Ortogonal
       QString o =QString::number(mA->ortogonal());
       if(o=="0"){o = "Não";}
       else {o = "Sim";}
       QTableWidgetItem *itemI = new QTableWidgetItem(o);
       ui->tableWidget_resultado->setItem(5,0,itemI);

       //Permutacao
       QString p =QString::number(mA->permutacao());
       if(p=="0"){p = "Não";}
       else {p = "Sim";}
       QTableWidgetItem *itemJ = new QTableWidgetItem(p);
       ui->tableWidget_resultado->setItem(7,0,itemJ);

    }catch(QString &erro)
        {
            QMessageBox::information(this,"ERRO NO SISTEMA",erro);
        }
        catch(std::bad_alloc&)
            {
               QMessageBox::information(this,"ERRO NO SISTEMA","Matriz nao pode ser criada");
            }



}

void MainWindow::on_pushButtonCriarMatrizB_clicked()
{
    try
     {
        int quantidadeLinhasB;
        int quantidadeColunasB;
        quantidadeLinhasB=ui->lineEditQuaLinhasB ->text().toInt();//conversao
        quantidadeColunasB=ui->lineEditQuaColunasB ->text().toInt();

        mB=new tp2::Matriz(quantidadeLinhasB,quantidadeColunasB);// criando a matriz com construtor
        for(int l=0;l<quantidadeLinhasB;l++)
        {
           for(int c=0;c<quantidadeColunasB;c++)
           {
               int elemento = QInputDialog::getInt(this , "Leitura",
               "Matriz B ["+QString::number(l)+","+QString::number(c)+"]=");
               mB->setElemento(elemento,l,c);
            }
        }
        ui->textEditSaidaMb->setText(mB->getMatriz());

        ui->pushButton_adicao->setEnabled(true);//habilitador dos botoes
        ui->pushButton_subtracao->setEnabled(true);
        ui->pushButton_multiplicacao->setEnabled(true);
        ui->pushButton_Exponencial_B->setEnabled(true);
        ui->pushButton_Multiplicar_B->setEnabled(true);
        ui->pushButton_transpostaB->setEnabled(true);

        //Grid

        //Iguais
        QString igual = QString::number((*mA) == mB);
        if(igual=="0"){igual="Não";}
        else{igual="Sim";}
        QTableWidgetItem *itemA = new QTableWidgetItem(igual);
        QTableWidgetItem *itemB = new QTableWidgetItem(igual);
        ui->tableWidget_resultado->setItem(1,0,itemA);
        ui->tableWidget_resultado->setItem(1,1,itemB);

        //Diferentes
        QString diferente = QString::number((*mA) != mB);
        if(diferente!="0"){diferente="Sim";}
        else{diferente="Não";}
        QTableWidgetItem *itemC = new QTableWidgetItem(diferente);
        QTableWidgetItem *itemD = new QTableWidgetItem(diferente);
        ui->tableWidget_resultado->setItem(0,0,itemC);
        ui->tableWidget_resultado->setItem(0,1,itemD);

        //Simetrica
        QString x = QString::number(mB->simetrica());
        if(x=="0") {x = "Não";}
        else {x="Sim";}
        QTableWidgetItem *itemE = new QTableWidgetItem(x);
        ui->tableWidget_resultado->setItem(6,1,itemE);

        //Triangular superior
        QString y = QString::number(mB->triangularsuperior());
        if(y=="0") {y = "Não";}
        else {y = "Sim";}
        QTableWidgetItem *itemF = new QTableWidgetItem(y);
        ui->tableWidget_resultado->setItem(3,1,itemF);

        //Triangular inferior
        QString z = QString::number(mB->triangularsuperior());
        if(z=="0") {z = "Não";}
        else {z = "Sim";}
        QTableWidgetItem *itemG = new QTableWidgetItem(z);
        ui->tableWidget_resultado->setItem(4,1,itemG);

        //Identidade
        QString w =QString::number(mB->identidade());
        if(w=="0"){w = "Não";}
        else {w = "Sim";}
        QTableWidgetItem *itemH = new QTableWidgetItem(w);
        ui->tableWidget_resultado->setItem(2,1,itemH);
        //Ortogonal
        QString o =QString::number(mB->ortogonal());
        if(o=="0"){o = "Não";}
        else {o = "Sim";}
        QTableWidgetItem *itemI = new QTableWidgetItem(o);
        ui->tableWidget_resultado->setItem(5,1,itemI);

        //Permutacao
        QString p =QString::number(mB->permutacao());
        if(p=="0"){p = "Não";}
        else {p = "Sim";}
        QTableWidgetItem *itemJ = new QTableWidgetItem(p);
        ui->tableWidget_resultado->setItem(7,1,itemJ);

     }catch(QString &erro)
         {
             QMessageBox::information(this,"ERRO NO SISTEMA",erro);
         }
         catch(std::bad_alloc&)
             {
                QMessageBox::information(this,"ERRO NO SISTEMA","Matriz nao pode ser criada");
             }
}


void MainWindow::on_pushButton_adicao_clicked()//botao de adiçao de matrizes "A" com "B"
{
    try{
            tp2::Matriz *mR = (*mA) + mB;

            ui->textEditSaida_resultado->setText(mR->getMatriz());

        delete mR;

        } catch (QString &erro){
            QMessageBox::information(this, "Erro no sistema", erro);
        }
}

void MainWindow::on_pushButton_subtracao_clicked()//botao de subtraçao de matrizes "A" com "B"
{
    try{
            tp2::Matriz *mR = (*mA) - mB;

            ui->textEditSaida_resultado->setText(mR->getMatriz());

        delete mR;

        } catch (QString &erro){
            QMessageBox::information(this, "Erro no sistema", erro);
        }
}

void MainWindow::on_pushButton_multiplicacao_clicked()//botao de multiplicaçao de matrizes "A" com "B"
{
    try{
        tp2::Matriz *mR = (*mA) * mB;

        ui->textEditSaida_resultado->setText(mR->getMatriz());

        delete mR;

    } catch (QString &erro){
        QMessageBox::information(this, "Erro no sistema", erro);
    }
}


void MainWindow::on_pushButton_transpostaA_clicked()//botao mostrar a matriz transposta de "A"
{
    try {
        ui->textEditSaida_resultado->setText(mA->transposta()->getMatriz());
    } catch(QString &erro){
        QMessageBox::information(this,"Erro no Sistema",erro);
    }
}



void MainWindow::on_pushButton_transpostaB_clicked()//botao mostrar a matriz transposta de "B"
{
    try {
        ui->textEditSaida_resultado->setText(mB->transposta()->getMatriz());
    } catch(QString &erro){
        QMessageBox::information(this,"Erro no Sistema",erro);
    }
}

void MainWindow::on_pushButton_Exponencial_A_clicked()//botao para calcular o exponencial de "A"
{
    try{
        int txtexponencial = ui->lineEdit_Exponencial_A->text().toInt();
        ui->textEditSaida_resultado->setText(mA->exponecial(txtexponencial)->getMatriz());
    }catch(QString &erro){
        QMessageBox::information(this,"Erro no sistema",erro);
    }
}

void MainWindow::on_pushButton_Exponencial_B_clicked()//botao para calcular o exponencial de "B"
{
    try{
        int txtexponencial = ui->lineEdit_Exponencial_B->text().toInt();
        ui->textEditSaida_resultado->setText(mB->exponecial(txtexponencial)->getMatriz());
    }catch(QString &erro){
        QMessageBox::information(this,"Erro no sistema",erro);
    }
}

void MainWindow::on_pushButton_Multiplicar_A_clicked()//botao para multiplicar uma constante qualquer na matriz "A"
{
    try{
        int txtk = ui->lineEdit_Multiplicar_A->text().toInt();
        ui->textEditSaida_resultado->setText(mA->constante(txtk)->getMatriz());
    }catch(QString &erro){
        QMessageBox::information(this,"Erro no sistema",erro);
    }
}

void MainWindow::on_pushButton_Multiplicar_B_clicked()//botao para multiplicar uma constante qualquer na matriz "B"
{
    try{
        int txtk = ui->lineEdit_Multiplicar_B->text().toInt();
        ui->textEditSaida_resultado->setText(mB->constante(txtk)->getMatriz());
    }catch(QString &erro){
        QMessageBox::information(this,"Erro no sistema",erro);
    }
}
