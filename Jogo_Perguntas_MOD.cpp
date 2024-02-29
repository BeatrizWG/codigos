#include <iostream>
#include <cstdlib> 
#include <ctime> 
using namespace std;
#define MAX 15

struct questao {
    string pergunta;
    string alternativas;
    char resposta;
};

struct no{
    int num;
    no* prox;
};



int main(void) {
  
    show();

    const int linhas = 5;
    const int colunas = 15;

  
    questao  minhas_questoes [MAX][MAX];
    ler_biblioteca(minhas_questoes);

   
    srand(time(0)); 
    int** valor_rand1 =  criar_matriz_randomica(colunas, linhas);
    randomizar_valores(valor_rand1, colunas, linhas);
    int** valor_rand2 =  criar_matriz_randomica(colunas, linhas);
    randomizar_valores(valor_rand2, colunas, linhas);

    int pos_1 = 0, pos_2 = 0;
    int num_rodadas = 0;
    int indexQ_P1 = 0, indexQ_P2 = 0;
    int pontos_1 = 0, pontos_2 = 0;
    int rodadas = 0;
    bool endGame = false;

    string nome1, nome2;
    cout<<"Digite o nome do primeiro jogador: ";
    cin>>nome1;
    cout<<"Digite o nome do segundo jogador: ";
    cin>>nome2;
    sortear_jogador_inicial(nome1,nome2);

    no* verify_pl1 = NULL;
    no* verify_pl2 = NULL;

    do
    {
        int pos_atual = definir_vez(num_rodadas, pos_1, pos_2,nome1,nome2); 
        char resposta = '\0';


        if (rodadas % 2 == 0) {
            resposta = mostrar_questao(minhas_questoes, pos_atual, valor_rand1[pos_atual][indexQ_P1]);
            indexQ_P1++;
        } 
        else {
            resposta = mostrar_questao(minhas_questoes, pos_atual, valor_rand2[pos_atual][indexQ_P2]);
            indexQ_P2++;
        }

        char resposta_jog = '\0';
        cin >> resposta_jog;

        if (resposta == resposta_jog) {
            cout << "Parabens. Voce acertou!" <<endl;

            if (rodadas % 2 == 0) { 
                pos_1++;
                pontos_1++;
                indexQ_P1 = 0;
                verify_pl1 = NULL; 
            } else {
                pos_2++;
                pontos_2++;
                indexQ_P2 = 0;
                verify_pl2 = NULL;
            }
        } 
        else {
            cout << "Voce errou ;)" << endl;

            if (rodadas % 2 == 0) {
                append(verify_pl1); 

            } else {
                append(verify_pl2);
            }
        }

        if (rodadas % 2 == 0 && pontos_1 == 5) {
            cout<<nome1<<" ganhou o jogo! ";
            endGame = true;
        } else if (rodadas % 2 == 1 && pontos_2 == 5) {
            cout<<nome2<<" ganhou o jogo! ";;
            endGame = true;
        }

        rodadas++; 

    } while (!endGame && len(verify_pl1) < 15 && len(verify_pl2) < 15);

    if (len(verify_pl1) >= 15) {
        cout << nome1<<" voce perdeu o jogo por errar todas as perguntas disponiveis de uma materia"<<endl;
    } else if (len(verify_pl2) >= 15) {
        cout << nome2<<" voce perdeu o jogo por errar todas as perguntas disponiveis de uma materia"<<endl;
    }


    return 0;
}

void append(no*& L){

    no* novo = new no;
    novo->num = 1;
    novo->prox = NULL;

    if (L == NULL){
        L = novo;
    }
    else{
        no* run = L;
        while(run->prox != NULL){
            run = run->prox;
        }
        run->prox = novo;
    }
}

int len(no* L){

    int quant = 0;
    no* run = L;
    if (L == NULL){
        return quant;
    }
    else{
        while(run != NULL){
            run = run->prox;
            quant++;
        }
    }
    return quant;
}

void sortear_jogador_inicial (string & nome1, string & nome2){

  
    cout<<"Vamos sortear quem vai jogar primeiro..."<<"\n";
    int pos = (rand () % 2) + 1; 
    if (pos == 1){ 
        cout<<nome1<<" sera o(a) primeiro(a) a jogar "<<"\n";
    } else{ 
        string aux = nome1;
        nome1=nome2;
        nome2=aux;
        cout<<nome1<<" sera o(a) primeiro(a) a jogar "<<"\n";
    }
}

int definir_vez(int& num_rodada, int pos1, int pos2,string n1, string n2) {


    int real_pos = -1; 
    if (num_rodada % 2 == 0) {  
        cout << "--------------------------------------------------------------------------------------------" << "\n";
        cout << "Eh a vez de "<<n1<<" jogar:" <<endl;
        cout << "\n";
        real_pos = pos1; 
    }
    else {
        cout << "--------------------------------------------------------------------------------------------" << "\n";
        cout << "Eh a vez de "<<n2<<" jogar:" <<endl;
        cout << "\n";
        real_pos = pos2;
    }
    num_rodada++; 
    return real_pos;
}

char mostrar_questao(questao questoes[MAX][MAX], int posicao, int pergunta) {


    cout << questoes[posicao][pergunta].pergunta <<endl;
    cout << "" << endl;
    cout << questoes[posicao][pergunta].alternativas <<endl;
    cout << "" << endl;
    return questoes[posicao][pergunta].resposta;
}

int** criar_matriz_randomica(int colunas, int linhas) {

 
    int** Matriz = new int* [linhas];
    for (uint8_t i = 0; i < linhas; i++) {
        Matriz[i] = new int[colunas];
    }
    return Matriz;
}

questao** criar_biblioteca_questao (int colunas, int linhas) {
    
    questao** matriz = new questao * [linhas];
    for (uint8_t i = 0; i < linhas; i++) {
        matriz [i] = new questao[colunas];
    }
    return matriz;
}

bool elemento_lista(int ** matriz, int lin, int col, int num){
    for (int j = 0; j < col; j++) {
        if (matriz[lin][j] == num) {
            return true; 
        }
    }
    return false; 
}

void randomizar_valores(int** matriz, int colunas, int linhas) {
    for (int i = 0;i<linhas;i++){
        for (int j =0; j<colunas; j++){
            matriz[i][j]=-1; 
        }
    }
    int num;
    for (int i = 0;i<linhas;i++){
        for (int j =0; j<colunas; j++){
            do {
                num = rand() % colunas; 
            } while (elemento_lista(matriz,i,colunas,num)==true); 
            matriz[i][j]=num;
        }
    }
}

void show() {

    cout << "----------------------------------------------------------------------------------------------" << "\n";
    cout << "                                         OLA JOGARES!                                         " << "\n";
    cout << "                  BEM-VINDOS E PREPAREM-SE PARA TESTAR OS SEUS CONHECIMENTOS                  " << "\n";
    cout << "----------------------------------------------------------------------------------------------" << "\n";
    cout << "                                       VAMOS AS REGRAS:                                       " << "\n";
    cout<<"- O objetivo do jogo eh responder corretamente a uma serie de perguntas"<<"\n";
    cout<<"- Existem cinco niveis diferentes: Historia, Matematica, Portugues, Ciencias e Variedades"<<"\n";
    cout<<"- Cada nivel possui varias perguntas relacionadas ao tema"<<"\n";
    cout<<"- O jogador deve escolher a resposta correta entre as opcoes fornecidas"<<"\n";
    cout<<"- Quando um jogador responde corretamente a pergunta de um nivel, ele avanca para a proxima fase"<<"\n";
    cout<<"- Os jogadores continuam avancando ate alcancar o Nivel 5"<<"\n";
    cout<<"- A vitoria final ocorre quando o jogador completa com sucesso todas as cinco fases"<<"\n";
    cout << "----------------------------------------------------------------------------------------------" << "\n";
    cout << "                                          BOA SORTE!                                          " << "\n";
    cout << "----------------------------------------------------------------------------------------------" << "\n";
}

void ler_biblioteca(questao** mat) {
     
     
    // ------------------------------- HISTORIA --------------------------------
    mat[0][0].pergunta = "Quem foi o lider do movimento pela independencia do Brasil?";
    mat[0][0].alternativas = "a) Dom Joao VI; b) Tiradentes; c) Dom Pedro II; d) Dom Pedro I";
    mat[0][0].resposta = 'd';

    mat[0][1].pergunta = "Em que ano a Lei Aurea foi assinada, oficialmente abolindo a escravidao no Brasil?";
    mat[0][1].alternativas = "a) 1808; b) 1822; c) 1888; d) 1964";
    mat[0][1].resposta = 'c';

    mat[0][2].pergunta = "Em que ano o Brasil se tornou uma republica?";
    mat[0][2].alternativas = "a) 1822; b) 1889; c) 1500; d) 1964";
    mat[0][2].resposta = 'b';

    mat[0][3].pergunta = "Quem liderou o movimento conhecido como Cabanagem na regiao do Grao-Para no seculo XIX?";
    mat[0][3].alternativas = "a) Dom Pedro I; b) Tiradentes; c) Maria Quiteria; d) Francisco Pedro Vinagre";
    mat[0][3].resposta = 'd';

    mat[0][4].pergunta = "Qual foi a primeira capital do Brasil?";
    mat[0][4].alternativas = "a) Sao Paulo; b) Rio de Janeiro; c) Salvador; d) Brasilia";
    mat[0][4].resposta = 'c';

    mat[0][5].pergunta = "Quem foi o primeiro presidente eleito do Brasil pelo voto popular apos o periodo militar?";
    mat[0][5].alternativas = "a) Getulio Vargas; b) Janio Quadros; c) Fernando Collor de Mello; d) Tancredo Neves";
    mat[0][5].resposta = 'c';

    mat[0][6].pergunta = "Qual foi o periodo conhecido como Era Vargas na historia do Brasil?";
    mat[0][6].alternativas = "a) A decada de 1920; b) A decada de 1950; c) A decada de 1930 e 1940; d) A decada de 1960";
    mat[0][6].resposta = 'c';

    mat[0][7].pergunta = "Quem foi a primeira mulher a ser eleita presidente do Brasil?";
    mat[0][7].alternativas = "a) Dilma Rousseff; b) Marina Silva; c) Marta Suplicy; d) Ligia Fagundes Teles";
    mat[0][7].resposta = 'a';

    mat[0][8].pergunta = "Qual foi o movimento de resistencia a escravidao liderado por Zumbi dos Palmares?";
    mat[0][8].alternativas = "a) Revolta dos Males; b) Revolta da Chibata; c) Revolta de Canudos; d) Quilombo dos Palmares";
    mat[0][8].resposta = 'd';

    mat[0][9].pergunta = "Quem foi o lider da Inconfidencia Mineira?";
    mat[0][9].alternativas = "a) Joaquim Silverio dos Reis; b) Tiradentes; c) Jose Bonifacio; d) D. Joao VI";
    mat[0][9].resposta = 'b';

    mat[0][10].pergunta = "Em que periodo o Brasil foi uma colonia de Portugal?";
    mat[0][10].alternativas = "a) 1530-1822; b) 1822-1889; c) 1889-1930; d) 1930-1945";
    mat[0][10].resposta = 'a';

    mat[0][11].pergunta = "Qual foi o presidente do Brasil durante a realizacao da Rio-92, a Conferencia das Nacoes Unidas sobre Meio Ambiente e Desenvolvimento?";
    mat[0][11].alternativas = "a) Fernando Henrique Cardoso; b) Luiz Inacio Lula da Silva; c) Juscelino Kubitschek; d) Collor de Mello";
    mat[0][11].resposta = 'd';

    mat[0][12].pergunta = "Quem liderou o governo provisorio apos a Proclamacao da Republica?";
    mat[0][12].alternativas = "a) Dom Pedro II; b) Marechal Deodoro da Fonseca; c) Duque de Caxias; d) Getulio Vargas";
    mat[0][12].resposta = 'b';

    mat[0][13].pergunta = "Qual foi o periodo do governo de Getulio Vargas conhecido como Estado Novo?";
    mat[0][13].alternativas = "a) 1937-1945; b) 1945-1964; c) 1964-1985; d) 1985-1990";
    mat[0][13].resposta = 'a';

    mat[0][14].pergunta = "Qual evento historico marcou o inicio da Guerra dos Farrapos no Rio Grande do Sul?";
    mat[0][14].alternativas = "a) A Guerra de Canudos; b) A Revolta da Armada; c) A Revolta dos Males; d) A Revolucao Farroupilha";
    mat[0][14].resposta = 'd';

    // ------------------------------- MATEMATICA --------------------------------
    mat[1][0].pergunta = "Dois cursos A e B foram propostos para os guardas civis de um determinado municipio. Sabe-se que, de todo o efetivo, 17 guardas cursaram ambos os cursos, 82 cursaram o curso A, 53 cursaram o curso B, e 31 guardas nao cursaram esses cursos. Logo, o numero do efetivo de guardas desse municipio eh:";
    mat[1][0].alternativas = "a) 183 ; b) 149 ; c) 166 ; d) 124 ";
    mat[1][0].resposta = 'b';

    mat[1][1].pergunta = "De mesada, Julia recebe mensalmente do seu pai o dobro que recebe de sua mae. Se em 5 meses ela recebeu R$ 375,00, entao, de sua mae ela recebe, por mes,";
    mat[1][1].alternativas = "a) 15,00 ; b) 20,00 ; c) 25,00 ; d) 30,00  ";
    mat[1][1].resposta = 'c';

    mat[1][2].pergunta = "No sitio tem 7 patos, 12 marrecos, 9 cachorros e 16 gatos. A razao entre o numero de patos pelo numero total de animais, eh de, aproximadamente:";
    mat[1][2].alternativas = "a) 0,45 ; b) 0,37 ; c) 0,21 ; d) 0,16";
    mat[1][2].resposta = 'd';

    mat[1][3].pergunta = "Em uma festa, ha 42 convidados e a razao entre adultos e criancas, nessa ordem, eh de 2 para 5. Se estivessem presentes mais 3 adultos e 3 criancas nao tivessem comparecido, a razao entre adultos e criancas seria";
    mat[1][3].alternativas = "a) 5/3 ; b) 5/4 ; c) 5/7 ; d) 5/9";
    mat[1][3].resposta = 'd';

    mat[1][4].pergunta = "Determine 14,8 por cento de 210.";
    mat[1][4].alternativas = "a) 28,80 ; b) 31,08 ; c) 30,00 ; d) 27,08";
    mat[1][4].resposta = 'b';

    mat[1][5].pergunta = "Um tanque armazena oleo e encontra-se cheio. Para a transferencia deste conteudo, estao conectados 3 registros de igual vazao que quando abertos, sao capazes de escoar todo o conteudo em 1 hora e 45 minutos. Se estivessem conectados 5 registros, com a mesma vazao individual dos atuais, o tempo gasto para o escoamento de todo o seu conteudo, quando os 5 registros fossem abertos simultaneamente, seria de: ";
    mat[1][5].alternativas = "a) 1 hora e 12 minutos; b) 1 hora e 7 minutos; c) 1 hora e 3 minutos; d) 1 hora";
    mat[1][5].resposta = 'c';

    mat[1][6].pergunta = "Dentre os numeros descritos nas alternativas, o unico que nao eh divisivel por 9 eh:";
    mat[1][6].alternativas = "a) 123456; b)21744; c) 8766; d) 23130";
    mat[1][6].resposta = 'a';

    mat[1][7].pergunta = "Uma concessionaria comercializa dois carros de mesmo modelo. O valor do carro basico eh 60 por cento do valor do carro completo. Apos um reajuste de precos, o carro completo sofreu uma reducao, em reais, de 5 por cento do que custava o carro basico, ou seja, o carro completo sofreu uma reducao, em porcentagem, de: ";
    mat[1][7].alternativas = "a) 5; b) 3; c) 4; d) 1";
    mat[1][7].resposta = 'b';

    mat[1][8].pergunta = "Uma pessoa comprou garrafas de suco e de refrigerante, no total de 15 unidades. Se o numero de garrafas de suco foi igual a 2/3 do numero de garrafas de refrigerante, entao o numero de garrafas de refrigerante superou o numero de garrafas de suco em: ";
    mat[1][8].alternativas = "a) 1 unidade; b) 2 unidades; c) 3 unidades; d) 4 unidades";
    mat[1][8].resposta = 'c';

    mat[1][9].pergunta = "Na oficina de trabalhos manuais, uma equipe de detentos realizou 2/5 de um trabalho em 8 dias, trabalhando 6 horas por dia. Mantendo a mesma produtividade por hora e trabalhando 2 horas a mais por dia, essa mesma equipe terminara o projeto em mais: ";
    mat[1][9].alternativas = "a) 8 dias; b) 9 dias; c) 10 dias; d) 11 dias";
    mat[1][9].resposta = 'b';

    mat[1][10].pergunta = "Em um deposito, ha 108 latas de tinta empilhadas, e cada pilha tem o mesmo numero de latas. Sabendo-se que o numero de pilhas eh o triplo do numero de latas de uma pilha, entao o numero de pilhas eh: ";
    mat[1][10].alternativas = "a) 18; b) 15; c) 12; d) 9";
    mat[1][10].resposta = 'a';

    mat[1][11].pergunta = "Uma pessoa recebe R$ 1800,00 de salario e gasta 15 por cento dele em um plano de saude. Outra pessoa que recebe R$ 5400,00 de salario e paga o mesmo valor de plano de saude gasta quantos por cento do seu salario?";
    mat[1][11].alternativas = "a) 45; b) 15; c) 5; d) 3";
    mat[1][11].resposta = 'c';

    mat[1][12].pergunta = "Para a producao de certa quantidade de pecas, 4 prensas identicas trabalham juntas, com a mesma capacidade de producao, durante 6 horas e meia de trabalho ininterrupto. Sendo assim, para a producao da mesma quantidade de pecas, por apenas 3 dessas prensas, nas mesmas condicoes de trabalho, o tempo de trabalho ininterrupto esperado eh de ";
    mat[1][12].alternativas = "a) 9 horas e 06 minutos; b) 8 horas e 40 minutos; c) 8 horas e 16 minutos; d)  7 horas e 50 minutos";
    mat[1][12].resposta = 'b';

    mat[1][13].pergunta = "Contratei 10 pedreiros e eles fizeram 600 m de muro trabalhando durante 36 dias. Se eu contratar 18 pedreiros, em quantos dias eles farao 3.000 metros do muro?";
    mat[1][13].alternativas = "a) 25; b) 50; c) 75; d) 100";
    mat[1][13].resposta = 'd';

    mat[1][14].pergunta = "Cinco guardas civis metropolitanos, ao participarem de uma solenidade, foram colocados um ao lado do outro para uma fotografia. Levando em conta apenas a posicao deles entre si, existem exatamente k arrumacoes diferentes, de modo que as pessoas do sexo feminino fiquem nas extremidades. O valor de k eh:";
    mat[1][14].alternativas = "a) 8; b) 12; c) 18; d) 24";
    mat[1][14].resposta = 'b';

    // ------------------------------- PORTUGUES --------------------------------
    mat[2][0].pergunta = "Qual eh a classe gramatical da palavra rapido na frase: 'O carro eh muito rapido'?";
    mat[2][0].alternativas = "a) Substantivo; b) Adjetivo; c) Verbo; d) Adverbio";
    mat[2][0].resposta = 'b';

    mat[2][1].pergunta = "Qual eh o sujeito da frase: 'O menino correu para a escola'?";
    mat[2][1].alternativas = "a) Menino; b) Correu; c) Escola; d) O ";
    mat[2][1].resposta = 'a';

    mat[2][2].pergunta = "Qual eh a figura de linguagem em 'Aquele livro custou os olhos da cara'?";
    mat[2][2].alternativas = "a) Metafora; b) Hiperbole; c) Metonimia; d) Eufemismo ";
    mat[2][2].resposta = 'b';

    mat[2][3].pergunta = "Qual eh o complemento direto na frase: 'Ela comprou um presente'?";
    mat[2][3].alternativas = "a) Ela; b) Comprou; c) Um; d) Presente";
    mat[2][3].resposta = 'd';

    mat[2][4].pergunta = "Qual eh o plural de cidadao? ";
    mat[2][4].alternativas = "a) Cidadanias; b) Cidadoes; c) Cidadaes; d) Cidadaos ";
    mat[2][4].resposta = 'd';

    mat[2][5].pergunta = "Qual eh o tempo verbal da frase: 'Eles cantarao no concurso' ?";
    mat[2][5].alternativas = "a) Futuro do presente; b) Preterito perfeito; c) Presente do indicativo; d) Futuro do preterito";
    mat[2][5].resposta = 'a';

    mat[2][6].pergunta = "Qual eh a classe gramatical da palavra 'sempre'?";
    mat[2][6].alternativas = "a) Substantivo; b) Adjetivo; c) Verbo; d) Adverbio";
    mat[2][6].resposta = 'd';

    mat[2][7].pergunta = "Qual eh a funcao da virgula na frase: 'Ele, um homem gentil, sempre ajuda os outros.'? ";
    mat[2][7].alternativas = "a) Separar o sujeito do predicado; b) Separar elementos em uma enumeracao; c) Indicar uma acao concluida; d) Marcar uma pergunta";
    mat[2][7].resposta = 'b';

    mat[2][8].pergunta = "Qual eh o tempo verbal da frase: 'Eles estavam estudando para a prova'?";
    mat[2][8].alternativas = "a) Futuro; b) Preterito imperfeito; c) Presente; d) Preterito perfeito";
    mat[2][8].resposta = 'b';

    mat[2][9].pergunta = "Qual eh a figura de linguagem em 'O sol esta sorrindo para nos'?";
    mat[2][9].alternativas = "a) Metafora; b) Hiperbole; c) Personificacao; d) Antitese";
    mat[2][9].resposta = 'c';

    mat[2][10].pergunta = "Qual eh o significado da palavra paradoxo?";
    mat[2][10].alternativas = "a) Algo simples e facil de entender; b) Uma afirmacao que parece contraditoria, mas pode ser verdadeira; c) Uma afirmacao obvia e incontestavel; d) Uma situacao totalmente previsivel";
    mat[2][10].resposta = 'b';

    mat[2][11].pergunta = "Qual e o adjetivo na frase: 'O ceu estava nublado e escuro' ?";
    mat[2][11].alternativas = "a) Ceu; b) Estava; c) Nublado; d) Escuro";
    mat[2][11].resposta = 'c';

    mat[2][12].pergunta = "Qual eh a forma correta da frase: 'Eles se ___ a festa'?";
    mat[2][12].alternativas = "a) Dirigiram; b) Dirijiram; c) Dirjeram; d) Dirigem";
    mat[2][12].resposta = 'a';

    mat[2][13].pergunta = "Qual eh a funcao da conjuncao na frase: 'Ele estudou muito, mas nao passou na prova'?";
    mat[2][13].alternativas = "a) Indicar uma acao concluida; b) Separar elementos em uma enumeracao; c) Marcar uma pergunta; d) Estabelecer uma relacao de oposicao";
    mat[2][13].resposta = 'd';

    mat[2][14].pergunta = "Qual eh a figura de linguagem em 'O silencio da noite'?";
    mat[2][14].alternativas = "a) Metafora; b) Hiperbole; c) Personificacao; d) Pleonasmo";
    mat[2][14].resposta = 'c';

    // ------------------------------- CIENCIAS --------------------------------
    mat[3][0].pergunta = "Qual eh a camada mais externa da Terra?";
    mat[3][0].alternativas = "a) Nucleo; b) Manto; c) Litosfera; d) Crosta";
    mat[3][0].resposta = 'd';

    mat[3][1].pergunta = "Qual eh o processo pelo qual as plantas produzem seu proprio alimento usando luz solar?";
    mat[3][1].alternativas = "a) Respiracao; b) Fotossintese; c) Transpiracao; d) Fermentacao";
    mat[3][1].resposta = 'b';

    mat[3][2].pergunta = "Qual eh a funcao principal dos rins no corpo humano?";
    mat[3][2].alternativas = "a) Produzir insulina; b) Filtrar o sangue e remover residuos; c) Controlar a temperatura corporal; d) Produzir anticorpos";
    mat[3][2].resposta = 'b';

    mat[3][3].pergunta = "Qual eh a forca que atrai dois objetos com massa?";
    mat[3][3].alternativas = "a) Energia cinetica; b) Forca centrifuga; c) Gravidade; d) Forca eletromagnetica";
    mat[3][3].resposta = 'c';

    mat[3][4].pergunta = "Qual eh o nome da principal molecula de energia usada pelas celulas?";
    mat[3][4].alternativas = "a) Proteina; b) DNA; c) RNA; d) ATP";
    mat[3][4].resposta = 'd';

    mat[3][5].pergunta = "Qual eh o nome do processo pelo qual o DNA eh copiado?";
    mat[3][5].alternativas = "a) Transcricao; b) Traducao; c) Replicacao; d) Mutacao";
    mat[3][5].resposta = 'c';

    mat[3][6].pergunta = "Qual eh o orgao humano responsavel pela producao de insulina?";
    mat[3][6].alternativas = "a) Figado; b) Pancreas; c) Rim; d) Pulmoes";
    mat[3][6].resposta = 'b';

    mat[3][7].pergunta = "Qual eh o gas mais abundante na atmosfera da Terra?";
    mat[3][7].alternativas = "a) Hidrogenio; b) Oxigenio; c) Nitrogenio; d) Dioxido de carbono";
    mat[3][7].resposta = 'c';

    mat[3][8].pergunta = "Qual eh o nome do processo pelo qual a luz eh quebrada em suas cores componentes?";
    mat[3][8].alternativas = "a) Refracao; b) Reflexao; c) Difracao; d) Absorcao";
    mat[3][8].resposta = 'c';

    mat[3][9].pergunta = "Qual eh a unidade basica da eletricidade?";
    mat[3][9].alternativas = "a) Volt; b) Ampere; c) Watt; d) Ohm";
    mat[3][9].resposta = 'b';

    mat[3][10].pergunta = "Qual eh o nome do processo pelo qual a energia termica eh transferida atraves de colisoes entre particulas?";
    mat[3][10].alternativas = "a) Conducao; b) Conveccao; c) Radiacao; d) Refracao";
    mat[3][10].resposta = 'a';

    mat[3][11].pergunta = "Qual eh o nome do fenomeno pelo qual um objeto parece mais leve quando esta submerso em um liquido?";
    mat[3][11].alternativas = "a) Lei de Boyle; b) Lei de Hooke; c) Lei de Pascal; d) Empuxo";
    mat[3][11].resposta = 'd';

    mat[3][12].pergunta = "Qual eh o nome do processo pelo qual as substancias quimicas sao quebradas em substancias mais simples?";
    mat[3][12].alternativas = "a) Decomposicao; b) Combustao; c) Sintese; d) Reacao quimica";
    mat[3][12].resposta = 'a';

    mat[3][13].pergunta = "Qual eh o nome do processo de transformacao de um solido diretamente em vapor, sem passar pelo estado liquido?";
    mat[3][13].alternativas = "a) Sublimacao; b) Evaporacao; c) Fusao; d) Solidificacao";
    mat[3][13].resposta = 'a';

    mat[3][14].pergunta = "Qual eh a estrutura responsavel por produzir energia nas celulas por meio da respiracao celular?";
    mat[3][14].alternativas = "a) Ribossomos; b) Lisossomos; c) Mitocondrias; d) Reticulo endoplasmatico";
    mat[3][14].resposta = 'c';

    // ------------------------------- VARIEDADES --------------------------------
    mat[4][0].pergunta = "Quem eh o autor da obra 'Dom Casmurro'?";
    mat[4][0].alternativas = "a) Jose de Alencar; b) Machado de Assis; c) Carlos Drummond de Andrade; d) Cecilia Meireles";
    mat[4][0].resposta = 'b';

    mat[4][1].pergunta = "Qual eh o maior planeta do sistema solar?";
    mat[4][1].alternativas = "a) Marte; b) Venus; c) Terra; d) Jupiter";
    mat[4][1].resposta = 'd';

    mat[4][2].pergunta = "Qual eh o rio mais longo do mundo?";
    mat[4][2].alternativas = "a) Nilo; b) Amazonas; c) Yangtzeh; d) Mississippi";
    mat[4][2].resposta = 'a';

    mat[4][3].pergunta = "Qual eh o acido encontrado em limoes e responsavel por seu sabor azedo?";
    mat[4][3].alternativas = "a) Acido acetico; b) Acido sulfurico; c) Acido ascorbico; d) Acido citrico";
    mat[4][3].resposta = 'd';

    mat[4][4].pergunta = "Quem eh conhecido como o pai da psicanalise?";
    mat[4][4].alternativas = "a) Carl Jung; b) Sigmund Freud; c) B.F. Skinner; d) Ivan Pavlov";
    mat[4][4].resposta = 'b';

    mat[4][5].pergunta = "Qual eh o processo de movimento de agua do solo para a atmosfera atraves das plantas? ";
    mat[4][5].alternativas = "a) Evaporacao; b) Condensacao; c) Transpiracao; d) Precipitacao";
    mat[4][5].resposta = 'c';

    mat[4][6].pergunta = "Qual eh o maior orgao do corpo humano?";
    mat[4][6].alternativas = "a) Figado; b) Pulmoes; c) Pele; d) Coracao";
    mat[4][6].resposta = 'c';

    mat[4][7].pergunta = "Quem escreveu a obra O Pequeno Principe?";
    mat[4][7].alternativas = "a) Antoine de Saint-Exupehry; b) Victor Hugo; c) Jules Verne; d) Voltaire";
    mat[4][7].resposta = 'a';

    mat[4][8].pergunta = "Quem eh considerado o fundador do surrealismo na arte?";
    mat[4][8].alternativas = "a) Pablo Picasso; b) Salvador Dali; c) Vincent van Gogh; d) Claude Monet";
    mat[4][8].resposta = 'b';

    mat[4][9].pergunta = "Qual eh a capital da Russia?";
    mat[4][9].alternativas = "a) Moscou; b) Sao Petersburgo; c) Kiev; d) Varsovia";
    mat[4][9].resposta = 'a';

    mat[4][10].pergunta = "Quem eh a autora do livro Harry Potter?";
    mat[4][10].alternativas = "a) J.R.R. Tolkien; b) George Orwell; c) J.K. Rowling; d) C.S. Lewis";
    mat[4][10].resposta = 'c';

    mat[4][11].pergunta = "Qual eh o simbolo quimico para o elemento ouro?";
    mat[4][11].alternativas = "a) Go; b) Au; c) Ag; d) Fe";
    mat[4][11].resposta = 'b';

    mat[4][12].pergunta = "Qual eh o maior oceano do mundo?";
    mat[4][12].alternativas = "a) Oceano Atlantico; b) Oceano Pacifico; c) Oceano Indico; d) Oceano Artico";
    mat[4][12].resposta = 'b';

    mat[4][13].pergunta = "Qual eh a capital do Canada?";
    mat[4][13].alternativas = "a) Ottawa; b) Toronto; c) Vancouver; d) Montreal";
    mat[4][13].resposta = 'a';

    mat[4][14].pergunta = "Qual eh o elemento quimico mais abundante no universo?";
    mat[4][14].alternativas = "a) Hidrogenio; b) Oxigenio; c) Carbono; d) Ferro";
    mat[4][14].resposta = 'a';
}