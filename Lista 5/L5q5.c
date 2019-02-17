#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NOMEMAX 21
//L5q5
typedef struct vetor3d
{
  float x;
  float y;
  float z;
}Vetor3d;
typedef struct flecha
{
  Vetor3d* posicao;
  Vetor3d* velocid;
  char nome[NOMEMAX];
}Flecha;
Flecha** criaFlechaVazia(Flecha** matriz, int *qntFlechas)
{
  int i;
  matriz = (Flecha**) realloc(matriz, (*qntFlechas + 1) * (sizeof(Flecha*)));
  if(matriz != NULL)
  {
    (*qntFlechas)++;
    //primeira flecha
    matriz[*qntFlechas - 1] = (Flecha*) malloc(sizeof(Flecha));
    if(matriz[*qntFlechas - 1] != NULL)
    {
      //zero string
      for(i = 0;i < NOMEMAX - 1; i++)
      {
        matriz[*qntFlechas - 1]->nome[i] = ' ';
      }
      matriz[*qntFlechas - 1]->nome[i] = '\0';
      //malloco posica
      matriz[*qntFlechas - 1]->posicao = NULL;
      matriz[*qntFlechas - 1]->velocid = NULL;
    }
    else
    {
      printf("Erro:Alloc");
      exit(1);
    }
  }
  else
  {
    printf("Erro:Alloc");
    exit(1);
  }
  return matriz;
}
int preencheFlecha(Flecha** matriz, int qntFlechas)
{
  int resultado = 0;
  matriz[qntFlechas - 1]->posicao = (Vetor3d*) malloc(sizeof(Vetor3d));
  if(matriz[qntFlechas - 1]->posicao != NULL)
  {
    matriz[qntFlechas - 1]->velocid = (Vetor3d*) malloc(sizeof(Vetor3d));
    if(matriz[qntFlechas - 1]->velocid != NULL)
    {
      printf("Posicao separada por virgula: x,y,z: ");
      scanf("%f,%f,%f", &matriz[qntFlechas - 1]->posicao->x, &matriz[qntFlechas - 1]->posicao->y, &matriz[qntFlechas - 1]->posicao->z);
      printf("Velocidade separada por virgula: x,y,z: ");
      scanf("%f,%f,%f", &matriz[qntFlechas - 1]->velocid->x, &matriz[qntFlechas - 1]->velocid->y, &matriz[qntFlechas - 1]->velocid->z);
      printf("Nome da Flecha [20]Char:");
      scanf("%20s[^\n]", matriz[qntFlechas - 1]->nome);
      resultado = 1;
    }
    else
    {
      printf("Erro:Alloc");
      exit(1);
    }
  }
  else
  {
    printf("Erro:Alloc");
    exit(1);
  }
  return resultado;
}
void printStatus(Flecha** matriz, Vetor3d* gravidade, int qntFlechas, int tempo)//status do sistema
{
  int i;
  printf("Status do Sistema:\n");
  printf("Tempo Atual: %d s\n", tempo);
  if(gravidade > 0)
  {
    printf("Vetor [Gravidade]:\nValores:(%.3f)[i] + (%.3f)[j] + (%.3f)[k] |%.3f| m/s^2\n", gravidade->x, gravidade->y, gravidade->z, sqrt(pow(gravidade->x, 2) + pow(gravidade->y, 2) + pow(gravidade->z, 2)));
  }
  else
  {
    printf("Gravidade igual a zero\n");
  }
  if(qntFlechas > 0)
  {
    for(i = 0; i < qntFlechas; i++)
    {
      printf("Vetor[%s]:\nPosicao:(%.3f)[i] + (%.3f)[j] + (%.3f)[k] |%.3f| m\n", matriz[i]->nome, matriz[i]->posicao->x, matriz[i]->posicao->y, matriz[i]->posicao->z, sqrt(pow(matriz[i]->posicao->x, 2) + pow(matriz[i]->posicao->y, 2) + pow(matriz[i]->posicao->z, 2)));
      printf("Velocid:(%.3f)[i] + (%.3f)[j] + (%.3f)[k] |%.3f| m/s\n", matriz[i]->velocid->x, matriz[i]->velocid->y, matriz[i]->velocid->z, sqrt(pow(matriz[i]->velocid->x, 2) + pow(matriz[i]->velocid->y, 2) + pow(matriz[i]->velocid->z, 2)));
    }
  }
  else
  {
    printf("Sem flechas\n");
  }
}
void removeFlecha(Flecha** matriz, int* qntFlechas)
{
  //primeira flecha
  free(matriz[*qntFlechas - 1]->velocid);
  free(matriz[*qntFlechas - 1]->posicao);
  free(matriz[*qntFlechas - 1]);
  matriz = (Flecha**) realloc(matriz, ((*qntFlechas - 1) * (sizeof(Flecha*))));
  (*qntFlechas)--;//Qnd tudo saiu bem
}
int colisoes(Flecha** matriz, Vetor3d* gravidade, int qntFlechas, float* qntTempo)
{
  //tempo incremental tempo a mais
  //qntTempo == total, guarde para o fim do while
  //tempoParcial == Tempo do encontro
  //tempo restante = o que falta ser consumido (vou tirando valores com tempoParcial até fizar zero)
  int i, j;
  float tempocolisaoX = 0, tempocolisaoY = 0, tempocolisaoZ = 0;//Tempos de colisao devem ser iguais
  float tempoParcial = 0, tempoRestante;
  float Auxiliar;//ajuda na troca de velocidade
  int flechaParcialI, flechaParcialJ;//guarda os vetores da primeira colisao

  tempoRestante = *qntTempo;//quero manter o valor inicial do qntTempo para um if abaixo
  do
  {
    tempoParcial = tempoRestante;//tempoparcial me dara a menor colisao (primeira)
    for(i = 0; i < qntFlechas; i++)//primeiro vetor
    {
      for(j = i + 1; j < qntFlechas; j++)//testo com demais
      {
        //S = S >> So + Vot + gt/2 = So + Vot + gt/2  >> gravidade eh a mesma na componente >> So + Vot + gt/2 = So + Vot + gt/2 >> So + Vot + gt/2 - So - Vot - gt/2 >> So + Vot - So - Vot >> tcol = (So - So)/(Vo-Vo) == As/At numa mesma componente e mru
        tempocolisaoX = -((matriz[j]->posicao->x - matriz[i]->posicao->x)/(matriz[j]->velocid->x - matriz[i]->velocid->x));
        tempocolisaoY = -((matriz[j]->posicao->y - matriz[i]->posicao->y)/(matriz[j]->velocid->y - matriz[i]->velocid->y));
        tempocolisaoZ = -((matriz[j]->posicao->z - matriz[i]->posicao->z)/(matriz[j]->velocid->z - matriz[i]->velocid->z));
        if(tempocolisaoX == tempocolisaoY && tempocolisaoY == tempocolisaoZ)//tempo valido?
        {
//          if(tempocolisaoZ < 0)
//          {
//            //modulo
//            tempocolisaoX = -tempocolisaoX;
//            tempocolisaoY = -tempocolisaoY;
//            tempocolisaoZ = -tempocolisaoZ;
            //cntinuo validando dados
            if(tempocolisaoZ < tempoRestante && tempocolisaoZ > 0)
            {
              if(tempocolisaoZ < tempoParcial)//podia ser qualquer um X == Y == Z
              {//guado o menor tempo
                tempoParcial = tempocolisaoZ;
                flechaParcialI = i;
                flechaParcialJ = j;
              }
            }
//          }
        }
      }
    }
    if(tempoParcial < *qntTempo && tempocolisaoZ > 0)//tempo original//pelo menos  colisao
    {
      //Descobrir o menor tempo de encontro

      //aviso ao usuario da primeira colisao
      printf("Colisao: vetor[%s] e vetor [%s]\n", matriz[flechaParcialI]->nome, matriz[flechaParcialJ]->nome);

      //atualizo o tempo
      tempoRestante -= tempoParcial;

      //atualizar as posicoes de todos os vetores
      for(i = 0; i < qntFlechas; i++)//velocidade
      {
        matriz[i]->posicao->x = (matriz[i]->posicao->x) + ((matriz[i]->velocid->x) * tempoParcial) + (gravidade->x * pow(tempoParcial, 2))/2;
        matriz[i]->posicao->y = (matriz[i]->posicao->y) + ((matriz[i]->velocid->y) * tempoParcial) + (gravidade->y * pow(tempoParcial, 2))/2;
        matriz[i]->posicao->z = (matriz[i]->posicao->z) + ((matriz[i]->velocid->z) * tempoParcial) + (gravidade->z * pow(tempoParcial, 2))/2;
      }
      //atualizar velocidades de todos os vetores
      for(i = 0; i < qntFlechas; i++)//velocidade
      {
        matriz[i]->velocid->x = (matriz[i]->velocid->x) + (gravidade->x * tempoParcial);
        matriz[i]->velocid->y = (matriz[i]->velocid->y) + (gravidade->y * tempoParcial);
        matriz[i]->velocid->z = (matriz[i]->velocid->z) + (gravidade->z * tempoParcial);
      }

      //troco as velocidades x
      Auxiliar = matriz[flechaParcialI]->velocid->x;
      matriz[flechaParcialI]->velocid->x = matriz[flechaParcialJ]->velocid->x;
      matriz[flechaParcialJ]->velocid->x = Auxiliar;
      //y
      Auxiliar = matriz[flechaParcialI]->velocid->y;
      matriz[flechaParcialI]->velocid->y = matriz[flechaParcialJ]->velocid->y;
      matriz[flechaParcialJ]->velocid->y = Auxiliar;
      //z
      Auxiliar = matriz[flechaParcialI]->velocid->z;
      matriz[flechaParcialI]->velocid->z = matriz[flechaParcialJ]->velocid->z;
      matriz[flechaParcialJ]->velocid->z = Auxiliar;

      printf("Partindo do novo referencial de tempo, A colisao ocorreu apos:\n");
      printStatus(matriz, gravidade, qntFlechas, tempoParcial);
    }
    else
    {
      printf("Nao houve colisoes no tempo estipulado!\n");
      if(tempoParcial > *qntTempo)
      {
        tempoRestante = *qntTempo;
      }
      else
      {
        tempoRestante -= tempoParcial; //atualizo o tempo atual
      }
      //atualizar as posicoes de todos os vetores
      for(i = 0; i < qntFlechas; i++)//velocidade
      {
        matriz[i]->posicao->x = (matriz[i]->posicao->x) + ((matriz[i]->velocid->x) * tempoParcial) + (gravidade->x * pow(tempoParcial, 2))/2;
        matriz[i]->posicao->y = (matriz[i]->posicao->y) + ((matriz[i]->velocid->y) * tempoParcial) + (gravidade->y * pow(tempoParcial, 2))/2;
        matriz[i]->posicao->z = (matriz[i]->posicao->z) + ((matriz[i]->velocid->z) * tempoParcial) + (gravidade->z * pow(tempoParcial, 2))/2;
      }
      //atualizar velocidades de todos os vetores
      for(i = 0; i < qntFlechas; i++)//velocidade
      {
        matriz[i]->velocid->x = (matriz[i]->velocid->x) + (gravidade->x * tempoParcial);
        matriz[i]->velocid->y = (matriz[i]->velocid->y) + (gravidade->y * tempoParcial);
        matriz[i]->velocid->z = (matriz[i]->velocid->z) + (gravidade->z * tempoParcial);
      }
    }

  }while(tempoRestante > 0 && tempoParcial < *qntTempo);
  return tempoParcial;
}
void programa()
{
  int qntFlechas = 0;
  Flecha** matriz = NULL;
  int opcao;//comeca o tempo com zero;
  float qntTempo = 0, tempoIncremental = 0;
  Vetor3d* gravidade = (Vetor3d*) malloc(sizeof(Vetor3d));
  if(gravidade !=NULL)
  {
    do
    {
      printf("Gravidade? <1>Sim <2>Nao: ");
      scanf("%d", &opcao);
      if(opcao == 1)//
      {
        printf("Vetor gravidade, entre virgulas, X,Y,Z : ");
        scanf("%f,%f,%f", &gravidade->x, &gravidade->y, &gravidade->z);
        printStatus(matriz, gravidade, qntFlechas, tempoIncremental);
      }
      else if(opcao == 2)//valores zero
      {
        gravidade->x = gravidade->y = gravidade->z = 0;
        printStatus(matriz, gravidade, qntFlechas, tempoIncremental);
      }
      else
      {
        printf("Erro: Valor invalido");
      }
    }while(!(opcao > 0 && opcao < 3));

    int opcao;
    do
    {
      printf("1-Adiciona Flecha\n2-Remove Flecha\n3-Percorrer Tempo\n4-Sair\n");
      scanf("%d", &opcao);
      system("cls");
      if(opcao == 1)
      {
        matriz = criaFlechaVazia(matriz, &qntFlechas);
        if(matriz != NULL)
        {
          if(preencheFlecha(matriz, qntFlechas))
          {
            printStatus(matriz, gravidade, qntFlechas, tempoIncremental);
            fflush(stdin);//Evitar buffer se digitar mais que 20 Char
          }
        }
      }
      else if(opcao == 2)
      {
        removeFlecha(matriz, &qntFlechas);
        printStatus(matriz, gravidade, qntFlechas, tempoIncremental);
      }
      else if(opcao == 3)
      {
        printf("Qnt tempo?:");
        scanf("%f", &qntTempo);
        tempoIncremental += qntTempo;
        colisoes(matriz, gravidade, qntFlechas, &qntTempo);
        printStatus(matriz, gravidade, qntFlechas, tempoIncremental);
      }
      else if(opcao == 4)
      {
        free(gravidade);
        while(qntFlechas)//percorrer para retirar todas as flechas
        {
          removeFlecha(matriz, &qntFlechas);
        }
      }
      else
      {
        printf("Erro:opcao invalida");
      }
    }while(opcao != 4);
  }
  else
  {
    printf("Erro: Alloc");
    exit(1);
  }
}
int main()
{
  programa();
  return 0;
}
