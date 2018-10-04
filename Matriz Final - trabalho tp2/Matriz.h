#ifndef MATRIZ_H
#define MATRIZ_H
#include<QString>
namespace tp2
{//inicio
class Matriz
{
private:
    int quantidadeDeColunas;
    int quantidadeDeLinhas;
    int *ptMatriz;
public:
    Matriz(int qLinhas, int qColunas);
    ~Matriz(){if(ptMatriz) delete[] ptMatriz;}
    int getQuantidadeDeLinhas()const{return quantidadeDeLinhas;}
    int getQuantidadeDeColunas()const{return quantidadeDeColunas;}
    int getElemento(int linha, int coluna)const;
    QString getMatriz()const;
    void setElemento(int elemento, int linha, int coluna)const;
    Matriz* operator + (Matriz const * const mat)const;
    Matriz* operator - (Matriz const * const mat)const;
    Matriz* operator * (Matriz const * const mat)const;
    bool operator == (Matriz const * const mat)const;
    bool operator != (Matriz const * const mat)const;
    bool triangularsuperior()const;
    bool triangularinferior()const;
    bool simetrica()const;
    bool identidade()const;
    bool ortogonal()const;
    bool permutacao()const;
    Matriz* constante(int k)const;
    Matriz* exponecial(int expl)const;
    Matriz* transposta()const;
};
}
#endif // MATRIZ_H
