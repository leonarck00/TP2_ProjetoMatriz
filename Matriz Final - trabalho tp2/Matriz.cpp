#include "Matriz.h"
namespace tp2
{//inicio
Matriz::Matriz(int qLinhas, int qColunas)://construtor
    quantidadeDeLinhas(0),
    quantidadeDeColunas(0),
    ptMatriz(0)
{
    if(qLinhas<=0) throw QString("Quantidade de Linhas somente positiva");
    if(qColunas<=0) throw QString("Quantidade de Colunas somente positiva");
    try{
        ptMatriz = new int[qLinhas*qColunas];
    }catch(std::bad_alloc&){
        throw QString("Vai comprar Memoria");
    }
    quantidadeDeLinhas = qLinhas;
    quantidadeDeColunas = qColunas;
}

void Matriz::setElemento(int elemento, int linha, int coluna)const{
    if(linha<0 || linha>=quantidadeDeLinhas)
        throw QString("Linha fora do intervalo valido");
    if(coluna<0 || coluna>=quantidadeDeColunas)
        throw QString("Coluna fora do intervalo valido");
    int pos = linha*quantidadeDeColunas+coluna;
    *(ptMatriz+pos) = elemento;
}

int Matriz::getElemento(int linha, int coluna)const{
    if(linha<0 || linha>=quantidadeDeLinhas)
        throw QString("Linha fora do intervalo valido");
    if(coluna<0 || coluna>=quantidadeDeColunas)
        throw QString("Coluna fora do intervalo valido");
    int pos = linha*quantidadeDeColunas+coluna;
    return *(ptMatriz+pos);
}

QString Matriz::getMatriz()const{
    QString saida = "";
    for(int linha = 0; linha < getQuantidadeDeLinhas(); linha++)
    {
        for(int coluna = 0; coluna < getQuantidadeDeColunas(); coluna++)
        {
            saida += QString::number(getElemento(linha,coluna));
            saida += "  ";
        }
        saida += "\n";
    }
    return saida;
}

Matriz* Matriz::operator + (Matriz const * const mat)const{
    if( quantidadeDeLinhas  != mat->getQuantidadeDeLinhas() ||
        quantidadeDeColunas != mat->getQuantidadeDeColunas())
        throw QString("Operação nao pode ser realizada !!! Matriz de tamanhos diferentes");
    try{
        Matriz *aux = new Matriz(quantidadeDeLinhas,quantidadeDeColunas);
        for(int linha=0; linha<quantidadeDeLinhas; linha++){
            for(int coluna=0; coluna<quantidadeDeColunas; coluna++){
                int valor = this->getElemento(linha,coluna) +
                        mat->getElemento(linha,coluna);
                aux->setElemento(valor,linha,coluna);
            }
        }
        return aux;
    }
    catch(std::bad_alloc&){
        throw QString("Vai comprar Memoria");
    }
    catch(QString &erro){
        throw QString("Matriz auxiliar nao Criada nao podemos adicionar as matrizes");
    }
}

Matriz* Matriz::operator - (Matriz const * const mat)const{
    if( quantidadeDeLinhas  != mat->getQuantidadeDeLinhas() ||
        quantidadeDeColunas != mat->getQuantidadeDeColunas())
        throw QString("Operação nao pode ser realizada !!! Matriz de tamanhos diferentes");
    try{
        Matriz *aux = new Matriz(quantidadeDeLinhas,quantidadeDeColunas);
        for(int linha=0; linha<quantidadeDeLinhas; linha++){
            for(int coluna=0; coluna<quantidadeDeColunas; coluna++){
                int valor = this->getElemento(linha,coluna) -
                        mat->getElemento(linha,coluna);
                aux->setElemento(valor,linha,coluna);
            }
        }
        return aux;
    }
    catch(std::bad_alloc&){
        throw QString("Vai comprar Memoria");
    }
    catch(QString &erro){
        throw QString("Matriz auxiliar nao Criada nao podemos subtrair as matrizes");
    }
}

Matriz* Matriz::operator *(const Matriz * const mat) const
{
    if(quantidadeDeColunas  != mat->getQuantidadeDeLinhas())
            throw QString("Quantidade de coluna da Matriz A deve ser igual ao numero de linhas da Matriz B ");
    try{
        Matriz *aux = new Matriz(quantidadeDeLinhas, mat->quantidadeDeColunas);
        for(int linha = 0; linha < quantidadeDeLinhas; linha++){
            for(int colunas = 0; colunas < mat->quantidadeDeColunas; colunas++){
                int valor = 0;
                for(int obj = 0; obj < quantidadeDeColunas; obj++){
                    valor += this->getElemento(linha, obj) * mat->getElemento(obj, colunas);
                    aux->setElemento(valor, linha, colunas);
                }
            }
        }
        return aux;
    }
    catch(std::bad_alloc&){
        throw QString("Vai comprar Memoria");
    }
    catch(QString &erro){
        throw QString("Matriz auxiliar nao Criada nao podemos adicionar as matrizes");
    }
}

bool Matriz::operator ==(const Matriz * const mat) const
{
    if(quantidadeDeLinhas != mat->quantidadeDeLinhas || quantidadeDeColunas != mat->quantidadeDeColunas)
    return false;
    for(int linhas = 0; linhas < quantidadeDeLinhas; linhas++){
        for(int colunas = 0; colunas < quantidadeDeColunas; colunas++){
            if(this->getElemento(linhas, colunas) != mat->getElemento(linhas, colunas))
                return false;
        }
    }
    return true;
}

bool Matriz::operator !=(const Matriz * const mat) const
{
    return(!(this->operator ==(mat)));
}

bool Matriz::triangularsuperior() const
{
    if(quantidadeDeLinhas==quantidadeDeColunas){
        for(int linha=0;linha<quantidadeDeLinhas;linha++){
            for(int coluna=linha+1;coluna<quantidadeDeColunas;coluna++){
                if(this->getElemento(linha,coluna)!=0)
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Matriz::triangularinferior() const
{
    if(quantidadeDeLinhas==quantidadeDeColunas){
        for(int coluna=0;coluna<quantidadeDeLinhas;coluna++){
            for(int linha=coluna+1;linha<quantidadeDeColunas;linha++){
                if(this->getElemento(linha,coluna)!=0)
                return false;
            }
        }
        return true;
    }

}

bool Matriz::simetrica() const
{
    if(quantidadeDeLinhas==quantidadeDeColunas){
        for(int linha=0;linha<quantidadeDeLinhas;linha++){
            for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
                if(this->getElemento(linha,coluna)!=this->transposta()->getElemento(linha,coluna))
                return false;
            }
        }
    }
    return true;
}

bool Matriz::identidade() const
{
    if(this->triangularsuperior()&&this->triangularinferior()){
        for(int aux=0;aux<quantidadeDeLinhas;aux++){
            if(this->getElemento(aux,aux)!=1)
                return false;
        }
        return true;
    }
}

bool Matriz::ortogonal() const
{
    if(quantidadeDeLinhas!=quantidadeDeColunas)
    return false;
    Matriz *obj=0;
    Matriz *aux = this->transposta();
    Matriz *aux2 = new Matriz(quantidadeDeLinhas, quantidadeDeColunas);
    for(int linha=0;linha<quantidadeDeLinhas;linha++){
        for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
            aux2->setElemento(this->getElemento(linha,coluna),linha,coluna);
        }
    }
    obj = (*aux2) * aux;
    delete aux;
    delete aux2;
    if(obj->identidade()){
        delete obj;
        return true;
    }else{
        delete obj;
        return false;
    }
}

bool Matriz::permutacao() const
{
    for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
        for(int linha=0;linha<quantidadeDeLinhas;linha++){
            if(this->getElemento(linha,coluna)!=1 && this->getElemento(linha,coluna)!=0)
                return false;
        }
    }
    //colunas
    for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
        int aux=0;
        for(int linha=0;linha<quantidadeDeLinhas;linha++){
            if(this->getElemento(linha,coluna) == 1){
                aux++;
                if(aux<1||aux>1)
                    return false;
            }
        }
    }
    //linhas
    for(int linha=0;linha<quantidadeDeLinhas;linha++){
        int aux = 0;
        for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
            if(this->getElemento(linha,coluna) == 1){
                aux++;
                if(aux<1||aux>1)
                    return false;
            }
        }
    }
}

Matriz *Matriz::constante(int k) const
{
    try{
        Matriz* MatrizK = new Matriz(quantidadeDeLinhas, quantidadeDeColunas);
        for(int linha=0;linha<quantidadeDeLinhas;linha++){
            for(int coluna=0;coluna<quantidadeDeColunas;coluna++){
                int aux = ((this->getElemento(linha,coluna))* k);
                MatrizK->setElemento(aux,linha,coluna);
            }
        }
        return MatrizK;
    }
    catch(std::bad_alloc&){
        throw QString("Vai comprar Memoria");
    }
    catch(QString &erro){
        throw QString("Matriz auxiliar nao Criada nao podemos adicionar as matrizes");
    }
}

Matriz *Matriz::exponecial(int expl) const
{
    try{
        if(expl<0) throw QString (" Expoente não pode ser menor que zero!!!");
        if(expl==0){
            Matriz* matrizaux = new Matriz(quantidadeDeLinhas, quantidadeDeColunas);
            if(quantidadeDeColunas != quantidadeDeLinhas) throw QString("Quantidade de colunas tem que ser igual a quantidade de linhas");
            for(int linha = 0; linha < quantidadeDeLinhas; linha++){
                for(int coluna=0; coluna<quantidadeDeColunas; coluna++){
                    if(linha==coluna)
                     matrizaux->setElemento(1,linha,coluna);
                    else{
                        matrizaux->setElemento(0,linha,coluna);
                    }
                }
            }
            return matrizaux;
        }
             Matriz* saidaMatriz = new Matriz(quantidadeDeLinhas, quantidadeDeColunas);
             int novaLinha = this->quantidadeDeLinhas;
             int novaColunas = this->quantidadeDeLinhas;

             for(int linha = 0; linha < novaLinha; linha++){
                 for(int coluna = 0; coluna < novaColunas; coluna++){
                    saidaMatriz->setElemento(this->getElemento(linha, coluna), linha, coluna);
                 }
             }
             if(expl==1)
             return saidaMatriz;
             for(int obj=0;obj < expl - 1;obj++){
                 saidaMatriz = (*saidaMatriz) * this;
             }
            return saidaMatriz;
        }catch(std::bad_alloc&){
            throw QString("Vai comprar Memoria");
        }
}

Matriz *Matriz::transposta() const
{
    int qcoluna=quantidadeDeColunas;
    int qlinha=quantidadeDeLinhas;
    try{
        Matriz *transposta = new Matriz(qcoluna,qlinha);
        for(int linha = 0; linha < qlinha
            ; linha++){
            for(int colunas = 0; colunas < qcoluna; colunas++){
                    int aux = this->getElemento(linha,colunas);
                    transposta->setElemento(aux, colunas,linha);
            }
        }
        return transposta;
    }
    catch(std::bad_alloc&){
        throw QString("Vai comprar Memoria");
    }
    catch(QString &erro){
        throw QString("Matriz auxiliar nao Criada nao podemos adicionar as matrizes");
    }
}


}
