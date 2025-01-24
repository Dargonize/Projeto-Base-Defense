#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

template <typename T>
struct No {
    T dados;
    No* proximo;
    No(const T& valor) : dados(valor), proximo(nullptr) {}
};

template <typename T>
class ListaEncadeada {
private:
    No<T>* inicio;
    int tamanho;

public:
    ListaEncadeada() : inicio(nullptr), tamanho(0) {}
    
    void inserir_inicio(const T& valor) {
        No<T>* novoNo = new No<T>(valor);
        novoNo->proximo = inicio;
        inicio = novoNo;
        tamanho++;
    }
    
    void remover(No<T>* no) {
        if (!inicio || !no) return;
        
        if (inicio == no) {
            inicio = no->proximo;
            delete no;
            tamanho--;
            return;
        }
        
        No<T>* atual = inicio;
        while (atual->proximo && atual->proximo != no) {
            atual = atual->proximo;
        }
        
        if (atual->proximo) {
            atual->proximo = no->proximo;
            delete no;
            tamanho--;
        }
    }
    
    No<T>* começo() { return inicio; }
    const No<T>* começo() const { return inicio; }
    int getTamanho() const { return tamanho; }
    
    ~ListaEncadeada() {
        while (inicio) {
            No<T>* temp = inicio;
            inicio = inicio->proximo;
            delete temp;
        }
    }
};

#endif