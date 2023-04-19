#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <unistd.h>

struct No{
    int valor;
    time_t timestamp;
    No *prox;
};

//Na lista encadeada e será somente em uma direção, pois exluimos endereço anterior.
struct Lista {
    No *cabeca, *cauda;
    int n;
    int ttl;

    Lista(int _ttl) {
        cabeca = cauda = NULL;
        n = 0;
        ttl = _ttl;
    }

    Lista(){
        cabeca = cauda = NULL;
    }

    bool vazia(){
        return (cabeca==NULL);
    }

    void inserirInicio(int v){
        No *novo = new No();
        novo->valor = v;
        novo->timestamp = time(NULL);

        if(vazia()){
            novo->prox = NULL;
            cabeca = novo; //Deixa de apontar para NULL e aponta para o novo No
            cauda = novo; 
        }else {
            novo->prox = cabeca;
            cabeca = novo;
        }
    }

     void inserirFinal(int v){
        No *novo = new No();
        novo->valor = v;
        novo->timestamp = time(NULL);

        if(vazia()){
            novo->prox = NULL;
            cabeca = novo;
            cauda = novo; 
        }else {
            novo->prox = NULL;
            cauda->prox = novo;
            cauda = novo;
        }
    }

    void limparExpirados() {
        time_t agora = time(NULL);

        while(cabeca != NULL && difftime(agora, cabeca->timestamp) > ttl) {
            No *aux = cabeca;
            cabeca = cabeca->prox;
            delete aux;
        }

        if(cabeca == NULL) {
            cauda = NULL;
        }

        No *ant = cabeca;
        No *atual = cabeca->prox;

        while(atual != NULL) {
            if(difftime(agora, atual->timestamp) > ttl) {
                ant->prox = atual->prox;
                delete atual;
                atual = ant->prox;
            } else {
                ant = atual;
                atual = atual->prox;
            }
        }

        cauda = ant;
    }

    void imprimir(){
        limparExpirados();

        No *aux = cabeca;
        //for(No *au = cabeca; aux != NULL; aux = aux->prox);
        while(aux!=NULL){
            printf("%d -> ", aux->valor);
            aux = aux->prox;
        }
    }

    int tamanho(){
        int t = 0;
        No *aux = cabeca;

        //1 forma de encontrar o tamanho da lista
        while (aux!=NULL){
            t++;
            aux = aux->prox;
        }
        return t;//retorna o tamanho
    }

    void removerInicio(){ // BigO notation O(1)
        if(!vazia()){
            if(tamanho() == 1){
                No *aux = cabeca;
                cabeca = NULL;
                cauda = NULL;
                delete(aux);
            }else{
                No *aux = cabeca;//a partir do end do inicio percorremos a lista
                cabeca = cabeca->prox;
                delete(aux);
            }
            n--;//reduzindo o tamanho da lista
        }
    }


    void removerFinal(){ // BigO notation O(n)
        if(!vazia()){
            if(tamanho() == 1){
                No *aux = cabeca;
                cabeca = NULL;
                cauda = NULL;
                delete(aux);
            }else{
                No *penultimo = cabeca;
                while(penultimo->prox!=cauda){
                    penultimo = penultimo->prox;
                }
                delete(cauda);
                cauda = penultimo;
                cauda->prox = NULL;
            }
            n--;
        }
    }
};


int main(){
    Lista l(4);//4 segundos

    l.inserirInicio(2);
    l.inserirInicio(1);
    l.inserirFinal(3);

    l.imprimir();

    sleep(5);
    
    l.limparExpirados();

    l.inserirInicio(-1);
    l.imprimir();


    //l.removerInicio();
    //l.removerInicio();
    //l.removerFinal();
    //printf("Tamanho da lista = %d\n", l.tamanho());

    return 0;
}