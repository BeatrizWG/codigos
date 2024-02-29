#include <iostream>
using namespace std;

struct NoList_fila{
    string nome;
    int n_pedido;
    int tempo;
    int qnt_pratos;
    string ** ped;
    NoList_fila* prox;
    NoList_fila* ant;
};

struct desc {
    NoList_fila * ini_f;
    NoList_fila * fim_f;
};

struct pilha {
    string dado;
    pilha * prox;
};

desc * criar_desc();

pilha * criar_pilha ();

void push (pilha * & Pilha, string nome);

pilha * pop (pilha * & Pilha);

int len_pilha (pilha * Pilha);

int lenf(NoList_fila * fila);

void add_fila (desc * fila);

void cadastrar_pedido (desc * fila, string cliente, string vet[]);

void imprimir_fila (desc * fila);

NoList_fila * checkout_cliente (desc * fila);

void show();

void ler_cardapio (string vet[]);

void imprimir_cardapio (string vet[]);


int main() {
    desc* controle = criar_desc();
    pilha * mesas = criar_pilha ();
    NoList_fila * check_out;
    string cardapio[15];
    string cliente;
    ler_cardapio (cardapio);
    int qnt_mesas = 10;
    int escolha = 0;
    show();
    cout << "Informe o numero para a opcao que deseja: ";
    cin >> escolha;

    while(escolha != -1){
        if (escolha == 1){
            if (qnt_mesas>len_pilha(mesas)){
                add_fila (controle);
                push (mesas, cliente);
                cout<<"----------------------------------------------"<<endl;
                cout<<"MESAS RESTANTES: "<< qnt_mesas<<endl;
            } else{
                cout<<"Sem mesas disponiveis no momento."<< endl;
            }
            cout<<endl;

        } else if (escolha == 2){
            cout<<"Digite o nome do cliente: ";
            cin>>cliente;
            cadastrar_pedido (controle, cliente, cardapio);
            cout<<endl;

        } else if (escolha == 3){
            imprimir_fila (controle);
            cout<<endl;
          
        } else if (escolha == 4){
            check_out = checkout_cliente (controle);
            if (check_out == NULL){
                cout<<"Lista vazia! Nao foi possivel realizar o checkout"<<endl;
            } else{
                cout<<check_out -> nome <<" fez o checkout"<<endl;
                pop (mesas);
            }
            cout<<endl;

        } else if (escolha == 5){
            imprimir_cardapio (cardapio);
            cout<<endl;
        }
        
        show();
        cout << "Informe o numero para a opcao que deseja: ";
        cin >> escolha;    
    }
    return 0;
}


desc * criar_desc(){
    desc * novo = new desc;
    novo->fim_f = NULL;
    novo->ini_f = NULL;
    return novo;
}

pilha * criar_pilha (){
    return NULL;
}

void push (pilha * & Pilha, string nome){
    pilha * Novo = new pilha;
    Novo -> dado = nome;
    Novo -> prox = Pilha;
    Pilha = Novo;
}

pilha * pop (pilha * & Pilha){
    if (Pilha == NULL)
        return NULL;
    else {
        pilha * aux = Pilha;
        Pilha = Pilha -> prox;
        return aux;
    }
}
    
int len_pilha (pilha * Pilha){
    int qnt = 0;
    while (Pilha != NULL){
        qnt ++;
        Pilha = Pilha -> prox;
    }
    return qnt;
}

int lenf(NoList_fila * fila){
    if (fila == NULL){
        return 0;
    }else{
        return 1 + lenf(fila->prox);
    }
}

void add_fila (desc * fila){
    NoList_fila * novo = new NoList_fila;
    cout << "Informe o nome do cliente: " << endl;
    cin >> novo->nome;
    novo -> n_pedido = 0;
    novo -> tempo = 0;
    novo -> qnt_pratos = 0;
    novo -> prox = NULL;
    novo -> ant = NULL;

    if (fila -> ini_f == NULL){
        fila -> ini_f = novo;
        fila -> fim_f = novo;
        novo -> tempo = 30;
        novo -> n_pedido = 1;

    } else{
        fila -> fim_f -> prox = novo ;         
        novo -> ant = fila -> fim_f ;         
        fila -> fim_f = novo ;         
        novo -> tempo +=  (lenf (fila->ini_f)  * 30); 
        novo -> n_pedido += lenf (fila->ini_f);
    }
}

void cadastrar_pedido (desc * fila, string cliente, string vet[]){
    NoList_fila * aux = fila -> ini_f;
    string ** matriz;

    while (aux != NULL && aux->nome != cliente){
        aux = aux -> prox;
    }
    if (aux == NULL){
        cout<<"Cliente nao encontrado"<<endl;
    } else{
        cout<<"Quantos pratos deseja pedir? ";
        cin>>aux->qnt_pratos;

        matriz = new string * [aux->qnt_pratos];
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
        while (aux_f != NULL){
            cout<<"CLIENTE: "<<aux_f-> nome<<endl;
            cout<<"NUMERO DO PEDIDO: "<<aux_f-> n_pedido<<endl;
            cout<<"TEMPO DE ESPERA ESTIMADO: "<<aux_f-> tempo<<endl;
            if (aux_f->qnt_pratos == 0){
                cout<<"O cliente ainda nao realizou o pedido"<<endl;
            } else {
                cout<<"PEDIDOS FEITOS: "<<endl;
                for (int i =0; i<aux_f->qnt_pratos;i++){
                    cout<<"PRATO: "<<aux_f->ped[i][0]<<". QUANTIDADE: "<<aux_f->ped[i][1]<<endl;
                } 
            }           
            aux_f = aux_f -> prox; 
            cout<<"--------------------------------------------------"<<endl;    
        }    
    }
}

NoList_fila * checkout_cliente (desc * fila){   
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
    cout<<"--------------------------------------------------"<<endl;   
    cout << "1 - Para cadastrar alguem na fila" << endl;
    cout << "2 - Para cadastrar pedido" << endl;
    cout << "3 - Para imprimir a fila de espera" << endl;
    cout << "4 - Para fazer checkout do cliente" << endl;
    cout << "5 - Para exibir cardapio" << endl;
    cout << "-1 Para encerrar o programa" << endl;
}

void ler_cardapio (string vet[]){
    vet [0] = "01 - Salada Caprese";
    vet [1] = "02 - Sopa de Legumes";
    vet [2] = "03 - Bruschetta Tradicional";
    vet [3] = "04 - Carpaccio de Abobrinha";
    vet [4] = "05 - Cesta de Paes Artesanais";
    vet [5] = "06 - Frango Grelhado com Limao";
    vet [6] = "07 - Espaguete a Bolonhesa";
    vet [7] = "08 - Tilapia ao Forno";
    vet [8] = "09 - Risoto de Cogumelos";
    vet [9] = "10 - Vegetais Salteados com Tofu";
    vet [10] = "11 - Mousse de Chocolate";
    vet [11] = "12 - Torta de Limao";
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