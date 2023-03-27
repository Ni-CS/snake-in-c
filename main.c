#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

typedef struct
{

    int hLinha;
    int hColuna;
    int cLinha;
    int cColuna;
    int hSimbol;
    int cSimbol;
    int hit;
} Cobra;

void iniciarCenario(int matriz[25][50])
{
    // fundo vazio
    for (int l = 0; l < 25; l++)
    {
        for (int c = 0; c < 50; c++)
        {
            matriz[l][c] = 32;
        }
    }

    for (int i = 1; i < 49; i++)
    { // cima
        int l = 0;
        matriz[l][i] = 205;
    }
    for (int i = 1; i < 49; i++)
    { // baixo
        int l = 24;
        matriz[l][i] = 205;
    }
    for (int i = 1; i < 24; i++)
    { // esquerda
        int l = 0;
        matriz[i][l] = 186;
    }
    for (int i = 1; i < 24; i++)
    { // esquerda
        int l = 49;
        matriz[i][l] = 186;
    }
    // cantos
    matriz[0][0] = 201;   // topo esquerdo
    matriz[24][0] = 200;  // baixo esquerda
    matriz[24][49] = 188; // baixo direita
    matriz[0][49] = 187;  // topo direita
}

void iniciarKobra(Cobra *kobra)
{
    kobra->hLinha = 1 + rand() % 23;
    kobra->hColuna = 1 + rand() % 48;
    kobra->hSimbol = 178;
    kobra->cSimbol = 177;
}

void printarMatriz(int matriz[25][50])
{
    for (int l = 0; l < 25; l++)
    {
        for (int c = 0; c < 50; c++)
        {
            printf("%c", matriz[l][c]);
        }
        printf("\n");
    }
}

void moverCobrinha(char tecla, Cobra *kobra, int cenario[25][50])
{
    if (tecla == 119) // w
    {
        // verifica se bateu nela mesma
        if (cenario[kobra->hLinha - 1][kobra->hColuna] == 177 || cenario[kobra->hLinha - 1][kobra->hColuna] == 254)
        {
            kobra->hit = 1;
        }

        kobra->hLinha--;
    }
    if (tecla == 97) // a
    {
        if (cenario[kobra->hLinha][kobra->hColuna - 1] == 177 || cenario[kobra->hLinha][kobra->hColuna - 1] == 254)
        {
            kobra->hit = 1;
        }
        kobra->hColuna--;
    }
    if (tecla == 115) // s
    {
        if (cenario[kobra->hLinha + 1][kobra->hColuna] == 177 || cenario[kobra->hLinha + 1][kobra->hColuna] == 254)
        {
            kobra->hit = 1;
        }
        kobra->hLinha++;
    }
    if (tecla == 100) // d
    {
        if (cenario[kobra->hLinha][kobra->hColuna + 1] == 177 || cenario[kobra->hLinha][kobra->hColuna + 1] == 254)
        {
            kobra->hit = 1;
        }
        kobra->hColuna++;
    }
}

void criarFruta(int cenario[25][50], int comidaL[2], int comidaC[2], int comida[2])
{
    // zero comida
    if (comida[0] == 0 && comida[1] == 0)
    {
        for (int i = 0; i < 2;)
        {
            comidaL[i] = 1 + rand() % 23;
            comidaC[i] = 1 + rand() % 48;
            if (cenario[comidaL[i]][comidaC[i]] == 32)
            {
                cenario[comidaL[i]][comidaC[i]] = 190;
                comida[i] = 1;
                i++;
            }
        }
    }
    // uma comida na posicao 0
    if (comida[0] == 1 && comida[1] == 0)
    {
        for (int i = 0; i < 1;)
        {
            comidaL[1] = 1 + rand() % 23;
            comidaC[1] = 1 + rand() % 48;
            if (cenario[comidaL[1]][comidaC[1]] == 32)
            {
                cenario[comidaL[1]][comidaC[1]] = 190;
                comida[1] = 1;
                i++;
            }
        }
    }
    // uma comida na posicao 1
    if (comida[0] == 0 && comida[1] == 1)
    {
        for (int i = 0; i < 1;)
        {
            comidaL[0] = 1 + rand() % 23;
            comidaC[0] = 1 + rand() % 48;
            if (cenario[comidaL[0]][comidaC[0]] == 32)
            {
                cenario[comidaL[0]][comidaC[0]] = 190;
                comida[0] = 1;
                i++;
            }
        }
    }
}

void criarObstaculo(int cenario[25][50])
{
    int obsL, obsC;
    for (int i = 0; i < 2;)
    {
        obsL = 1 + rand() % 23;
        obsC = 1 + rand() % 48;
        if (cenario[obsL][obsC] == 32)
        {
            cenario[obsL][obsC] = 254;
            i++;
        }
    }
}

int main()
{
    srand(time(NULL));
    // definir variaveis
    Cobra kobra;
    int status = 1;
    int cenario[25][50];
    int pastLinha[5000], pastColuna[5000], control = 0, tamanho = 1, comida[2], comidaL[2], comidaC[2], movimento = 0, pontos = 0;
    char tecla;

    iniciarCenario(cenario);
    iniciarKobra(&kobra);
    // printf("aqui2");

    while (status == 1)
    {

        if (kbhit())
        {
            tecla = getch();
            movimento += 1;
        }

        // posicao da cabeca na execucao passada
        pastLinha[control] = kobra.hLinha;
        pastColuna[control] = kobra.hColuna;

        moverCobrinha(tecla, &kobra, cenario);
        if (kobra.hit == 1)
        {

            status = 0;
            printf("\n\n\nVoce morreu\n");
            system("pause");
            break;
        }

        // coloca a cauda
        cenario[pastLinha[control]][pastColuna[control]] = kobra.cSimbol;
        control += 1;

        // define a posicao da cauda como local da cabeca na ultima execucao na posicao controle menos o tamanho
        kobra.cLinha = pastLinha[control - tamanho];
        kobra.cColuna = pastColuna[control - tamanho];

        // apaga posicao anterior
        cenario[kobra.cLinha][kobra.cColuna] = 32;

        // cria a fruta a cada dez movimentos
        if (movimento % 10 == 0 && movimento > 0 && ((comida[0] == 0 && comida[1] == 0) || (comida[0] == 0 && comida[1] == 1) || (comida[0] == 1 && comida[1] == 0)))
        {
            criarFruta(cenario, comidaL, comidaC, comida);
        }
        // cria obstaculo a cada dez movimentos
        if (movimento % 10 == 0 && movimento > 0)
        {
            movimento++;
            criarObstaculo(cenario);
        }

        // cria  a cabeca da cobra
        cenario[kobra.hLinha][kobra.hColuna] = kobra.hSimbol;
        printarMatriz(cenario);
        printf("\nPontos: %i", pontos);
        printf("\n movimentos: %i", movimento);

        // verifica se bateu em parede
        if (kobra.hColuna == 0 || kobra.hColuna == 49 || kobra.hLinha == 0 || kobra.hLinha == 24)
        {
            status = 0;
            printf("\n\n\nVoce bateu na parede\n");
            system("pause");
        }
        // verifica se pegoua comida da posicao 0
        if (kobra.hLinha == comidaL[0] && kobra.hColuna == comidaC[0])
        {
            comida[0] = 0;
            pontos += 10;
            tamanho += 1;
        }
        // verifica se pegou a comida da posicao 1
        if (kobra.hLinha == comidaL[1] && kobra.hColuna == comidaC[1])
        {
            comida[1] = 0;
            pontos += 15;
            tamanho += 1;
        }

        Sleep(50);
        system("cls");
    }
    printf("\nGame Over :(");
}