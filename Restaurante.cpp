#include <iostream>
using namespace std;

struct NoList_fila{
    string nome;
    int n_pedido;
    int tempo;
    NoList_fila* prox;
    NoList_fila* ant;
};

struct NoList_ped{
    int n_pedido;
    int qnt_pratos;
    string ** ped;
    NoList_ped * prox;
    NoList_ped * ant;
};

struct desc {
    NoList_fila * ini_f;
    NoList_fila * fim_f;
    NoList_ped * ini_p;
    NoList_ped * fim_p;
};

desc * criar_desc(){
    desc * novo = new desc;
    novo->fim_f = NULL;
    novo->fim_p = NULL;
    novo->ini_f = NULL;
    novo->ini_p = NULL;
    return novo;
}

struct pilha {
    int dado;
    pilha * prox;
    pilha * ant;
};

int lenf(NoList_fila * fila){
    if (fila == NULL){
        return 0;
    }else{
        return 1+ lenf(fila->prox);
    }
}

void add_fila (desc * fila){
    NoList_fila * novo = new NoList_fila;
    int time = 30;
    cout<<"Informe o nome do cliente: "<<endl;
    cin>> novo -> nome;
    cout<<"Informe o numero do pedido: "<<endl;
    cin>> novo -> n_pedido;
    novo -> tempo = 0;
    novo -> prox = NULL;
    novo -> ant = NULL;

    if (fila -> ini_f == NULL){
        fila -> ini_f = novo;
        fila -> fim_f = novo;
        novo->tempo = time;

    } else{
        fila -> fim_f -> prox = novo ;         
        novo -> ant = fila -> fim_f ;         
        fila -> fim_f = novo ;         
        novo -> tempo +=  (lenf (fila->ini_f)  * time); 
    }
}

void cadastrar_pedido (desc * fila, int n_pedido, string vet[]){
    NoList_ped * aux = fila -> ini_p;
    string ** matriz;

    while (aux != NULL && aux -> n_pedido != n_pedido){
        aux = aux -> prox;
    }
    if (aux == NULL){
        cout<<"Cliente nao encontrado"<<endl;
    } else{
        cout<<"Quantos pratos deseja pedir? ";
        cin>>aux->qnt_pratos;

        string ** matriz = new string * [aux->qnt_pratos];
        for (int i = 0; i < aux->qnt_pratos; i ++){
            matriz [i] = new string [2];
        }

        int pedido;
        for (int i = 0; i < aux->qnt_pratos; i++){
            cout<<"Numero do Prato "<<i+1<<": ";
            cin>> pedido;
            while (pedido <= 0 || pedido > 15){
                cout<<"Pedido invalido"<<endl;
                cout<<"Numero do Prato "<<i+1<<": ";
                cin>> pedido;
            }
            matriz[i][0] = vet [pedido-1];

            cout<<"Quantidade do prato: ";
            cin>>matriz[i][1];            
        }

        aux->ped = matriz;
        cout<<"Pedido realizado"<<endl;
    }
}

void imprimir_fila (desc * fila){

    if (fila -> ini_f == NULL)
        cout<<"Fila vazia"<<endl;
    else { 
        NoList_fila * aux_f = fila -> ini_f;
        NoList_ped * aux_p = fila -> ini_p;

        while (aux_f != NULL){
            cout<<"CLIENTE: "<<aux_f-> nome<<endl;
            cout<<"NUMERO DO PEDIDO: "<<aux_f-> n_pedido<<endl;
            cout<<"TEMPO DE ESPERA ESTIMADO: "<<aux_f-> tempo<<endl;
            
            while (aux_p != NULL && aux_p -> n_pedido != aux_f -> n_pedido){
                aux_p = aux_p -> prox;
            }
            if (aux_p != NULL){
                cout<<"PEDIDOS FEITOS: "<<endl;
                for (int i =0; i<aux_p->qnt_pratos;i++){
                    cout<<"PRATO: "<<aux_p->ped[i][0]<<". QUANTIDADE: "<<aux_p->ped[i][1]<<endl;
                }    
            } else{
                cout<<"Esse cliente ainda nao realizou o pedido"<<endl;
            }
            aux_f = aux_f -> prox;  
        }
    }
}

NoList_fila * checkout_cliente (desc * fila){   
    NoList_ped * aux_p = fila -> ini_p;
    if (fila -> ini_f == NULL){
        return NULL;
    } else {
        NoList_fila * aux_f = fila -> ini_f;;
        fila -> ini_f = aux_f  -> prox;
        if (fila -> ini_f == NULL){
            fila -> fim_f = NULL;
        } else{
            fila -> ini_f -> ant = NULL;
        }
        return aux_f ;
    } 
}

void show(){
    cout << "1 - Para cadastrar alguem na fila" << endl;
    cout << "2 - Para cadastrar pedido" << endl;
    cout << "3 - Para imprimir a fila de espera" << endl;
    cout << "4 - Para fazer checkout do cliente" << endl;
    cout << "5 - Para fazer checkin do cliente" << endl;
    cout << "6 - Para exibir cardapio" << endl;
    cout << "-1 Para encerrar o programa" << endl;
}

void ler_cardapio (string vet[]){
    vet [0] = "01 - Salada Caprese";
    vet [1] = "02 - Sopa de Legumes";
    vet [2] = "03 - Bruschetta Tradicional";
    vet [3] = "04 - Carpaccio de Abobrinha";
    vet [4] = "05 - Cesta de Pães Artesanais";

    vet [5] = "06 - Frango Grelhado com Limão";
    vet [6] = "07 - Espaguete à Bolonhesa";
    vet [7] = "08 - Tilápia ao Forno";
    vet [8] = "09 - Risoto de Cogumelos";
    vet [9] = "10 - Vegetais Salteados com Tofu";

    vet [10] = "11 - Mousse de Chocolate";
    vet [11] = "12 - Torta de Limão";
    vet [12] = "13 - Sorvete de Baunilha com Calda de Chocolate";
    vet [13] = "14 - Pudim de Caramelo ";
    vet [14] = "15 - Salada de Frutas Frescas";
}

void imprimir_cardapio (string vet[]){
    cout<<"ENTRADAS: "<<endl;
    for (int i = 0; i < 5; i++){
        cout<<vet[i]<<endl;
    }
    cout<<"PRATOS PRINCIPAIS: "<<endl;
    for (int i = 5; i < 10; i++){
        cout<<vet[i]<<endl;
    }
    cout<<"SOBREMESAS: "<<endl;
    for (int i = 10; i < 15; i++){
        cout<<vet[i]<<endl;
    }
}

int main() {
    desc* controle = criar_desc();

    string cardapio[15];
    ler_cardapio (cardapio);

    int escolha = 0;
    show();
    cout << "Informe o numero para a opcao que deseja: ";
    cin >> escolha;

    while(escolha != -1){
        if (escolha == 1){
            //Para cadastrar alguem na fila
        } else if (escolha == 2){
            // Para cadastrar pedido
        } else if (escolha == 3){
            imprimir_fila (controle);
            cout<<endl;
            
        } else if (escolha == 4){
            // Para fazer checkout do cliente
        } else if (escolha == 5){
            //Para fazer checkin do cliente
        } else if (escolha == 6){
            imprimir_cardapio (cardapio);
            cout<<endl;
        }
        
        show();
        cout << "Informe o numero para a opcao que deseja: ";
        cin >> escolha;    
    }
    return 0;
}