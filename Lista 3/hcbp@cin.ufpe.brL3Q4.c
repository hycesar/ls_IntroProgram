/* Logica: 7.0/7.0
 * Modularização: 0.5/2.0
 * Legibilidade: 1.0/1.0
 *
 * Nota: 8.5
 *
 * Observações: Confesso que não consegui ler o código todo de uma vez, pelo tamanho extenso do mesmo
 *              Mas está tudo correto. O problema foi exatamente a falta de modularização.
 */

#include <stdio.h>
#include <stdlib.h>

#define LINHAS 20
#define COLUNAS 30
#define CORREDOR 0
#define PAREDE 1
#define MAX_PASSOS 400

//L3q4
void imprime_matriz(int matriz[LINHAS][COLUNAS])
{
  int i, j;
  system("cls");//limpando tela.
  printf("\n");
  for(i = 0; i < LINHAS; i++)
  {
    for(j = 0; j < COLUNAS; j++)
    {
      if(matriz[i][j] == 3)
      {
        printf("S");//S de saida!
      }
      if(matriz[i][j] == 2)//Futura implementação simulando os monitores andando pela matriz (simbolizando migalhas de pão)
        printf("*");
      else if(matriz[i][j] == 1)//TEMP: Adaptação para melhor visualizar o labirinto: paredes
        printf("|");
      else//corredor
        printf(" ");
    }
    printf("\n");
  }
//  system("pause");//TEMP: atraso na execução para debug substituir por timout
}

void imprime_coordenada(unsigned char coordenadas[MAX_PASSOS][2])
{
  int i, j;
  for(i = 0, j = 0; coordenadas[i][j] != '\0'; i++)
  {
    printf(" %d[%c]/", coordenadas[i][j], coordenadas[i][j+1]);
    if(i % 11 == 0 && i != 0)
    {
      printf("\n");
    }
  }
}

void constroiu_coordenadas(int mapa[LINHAS][COLUNAS], int i, int j)//ler matriz em sequencia e otimiza o movimento
{
  int resultado = mapa[i][j];
  unsigned char coordenadas[MAX_PASSOS][2] = {{0}};//Evitar algum lixo de memória nas comparações abaixo
  int l, m;
  //o carinha nao chegou ao fim? continua procurando!
  for(l = -1, m = 0; mapa[i][j] != 3; )//TEMP L = -1
  {
    mapa[i][j] = 0; //removo uma migalha de pão
    imprime_matriz(mapa);
    if(i == 0)
    {
      resultado = mapa[(i + 1)][j];//sul
      if(j == 0 && (resultado != 2 && resultado != 3))
      {
        //leste
        if(coordenadas[l][m + 1] == 'L')
        {
          coordenadas[l][m] += 1;
        }
        else
        {
          l++; // Apenas quando a próxima cordenada eh diferente avançamos no vetor
          coordenadas[l][m] = 1;
          coordenadas[l][m + 1] = 'L';
        }
        j++;//andei no mapa
      }
      else if(j == COLUNAS - 1 && (resultado != 2 && resultado != 3))
      {
        //oeste
        if(coordenadas[l][m + 1] == 'O')
        {
          coordenadas[l][m] += 1;
        }
        else
        {
          l++; // Apenas quando a próxima cordenada eh diferente avançamos no vetor
          coordenadas[l][m] = 1;
          coordenadas[l][m + 1] = 'O';
        }
        j--;//andei no mapa para oeste
      }
      else if(resultado != 2 && resultado != 3)
      {
        resultado = mapa[i][(j + 1)];//leste
        if(resultado != 2 && resultado != 3)
        {
          //oeste
          if(coordenadas[l][m + 1] == 'O')
          {
            coordenadas[l][m] += 1;
          }
          else
          {
            l++; // Apenas quando a próxima cordenada eh diferente avançamos no vetor
            coordenadas[l][m] = 1;
            coordenadas[l][m + 1] = 'O';
          }
          j--;//andei no mapa para oeste
        }
        else
        {
          //leste
          if(coordenadas[l][m + 1] == 'L')
          {
            coordenadas[l][m] += 1;
          }
          else
          {
            l++; // Apenas quando a próxima cordenada eh diferente avançamos no vetor
            coordenadas[l][m] = 1;
            coordenadas[l][m + 1] = 'L';
          }
          j++;//andei no mapa
        }
      }
      else
      {
        //sul
        if(coordenadas[l][m + 1] == 'S')
        {
          coordenadas[l][m] += 1;
        }
        else
        {
          l++; // Apenas quando a próxima cordenada eh diferente avançamos no vetor
          coordenadas[l][m] = 1;
          coordenadas[l][m + 1] = 'S';
        }
        i++;//andei no mapa sul
      }
    }
    else if(i == LINHAS - 1 && (resultado != 2 && resultado != 3))
    {
      resultado = mapa[(i - 1)][j];//norte
      if(j == 0 && (resultado != 2 && resultado != 3))
      {
        //leste
        if(coordenadas[l][m + 1] == 'L')
        {
          coordenadas[l][m] += 1;
        }
        else
        {
          l++; // Apenas quando a próxima cordenada eh diferente avançamos no vetor
          coordenadas[l][m] = 1;
          coordenadas[l][m + 1] = 'L';
        }
        j++;//andei no mapa
      }
      else if(j == COLUNAS - 1 && (resultado != 2 && resultado != 3))
      {
        //oeste
        if(coordenadas[l][m + 1] == 'O')
        {
          coordenadas[l][m] += 1;
        }
        else
        {
          l++; // Apenas quando a próxima cordenada eh diferente avançamos no vetor
          coordenadas[l][m] = 1;
          coordenadas[l][m + 1] = 'O';
        }
        j--;//andei no mapa para oeste
      }
      else if(resultado != 2 && resultado != 3)
      {
        resultado = mapa[i][(j + 1)];//leste
        if(resultado != 2 && resultado != 3)
        {
          //oeste
          if(coordenadas[l][m + 1] == 'O')
          {
            coordenadas[l][m] += 1;
          }
          else
          {
            l++; // Apenas quando a próxima cordenada eh diferente avançamos no vetor
            coordenadas[l][m] = 1;
            coordenadas[l][m + 1] = 'O';
          }
          j--;//andei no mapa para oeste
        }
        else
        {
          //leste
          if(coordenadas[l][m + 1] == 'L')
          {
            coordenadas[l][m] += 1;
          }
          else
          {
            l++; // Apenas quando a próxima cordenada eh diferente avançamos no vetor
            coordenadas[l][m] = 1;
            coordenadas[l][m + 1] = 'L';
          }
          j++;//andei no mapa
        }
      }
      else
      {
        //norte
        if(coordenadas[l][m + 1] == 'N')
        {
          coordenadas[l][m] += 1;
        }
        else
        {
          l++; // Apenas quando a próxima cordenada eh diferente avançamos no vetor
          coordenadas[l][m] = 1;
          coordenadas[l][m + 1] = 'N';
        }
        i--;//andei no mapa norte
      }
    }
    else//qualquer result estranho
    {
      resultado = mapa[(i + 1)][j];//sul
      if(resultado != 2 && resultado != 3)
      {
        resultado = mapa[(i - 1)][j];//norte
        if(j == 0 && (resultado != 2 && resultado != 3))
        {
          //leste
          if(coordenadas[l][m + 1] == 'L')
          {
            coordenadas[l][m] += 1;
          }
          else
          {
            l++; // Apenas quando a próxima cordenada eh diferente avançamos no vetor
            coordenadas[l][m] = 1;
            coordenadas[l][m + 1] = 'L';
          }
          j++;//andei no mapa
        }
        else if(j == COLUNAS - 1 && (resultado != 2 && resultado != 3))
        {
          //oeste
          if(coordenadas[l][m + 1] == 'O')
          {
            coordenadas[l][m] += 1;
          }
          else
          {
            l++; // Apenas quando a próxima cordenada eh diferente avançamos no vetor
            coordenadas[l][m] = 1;
            coordenadas[l][m + 1] = 'O';
          }
          j--;//andei no mapa para oeste
        }
        else if(resultado != 2 && resultado != 3)//qq jota estranho
        {
          resultado = mapa[i][(j + 1)];//leste
          if(resultado != 2 && resultado != 3)
          {
            //oeste
            if(coordenadas[l][m + 1] == 'O')
            {
              coordenadas[l][m] += 1;
            }
            else
            {
              l++; // Apenas quando a próxima cordenada eh diferente avançamos no vetor
              coordenadas[l][m] = 1;
              coordenadas[l][m + 1] = 'O';
            }
            j--;//andei no mapa para oeste
          }
          else
          {
            //leste
            if(coordenadas[l][m + 1] == 'L')
            {
              coordenadas[l][m] += 1;
            }
            else
            {
              l++; // Apenas quando a próxima cordenada eh diferente avançamos no vetor
              coordenadas[l][m] = 1;
              coordenadas[l][m + 1] = 'L';
            }
            j++;//andei no mapa
          }
        }
        else
        {
          //norte
          if(coordenadas[l][m + 1] == 'N')
          {
            coordenadas[l][m] += 1;
          }
          else
          {
            l++; // Apenas quando a próxima cordenada eh diferente avançamos no vetor
            coordenadas[l][m] = 1;
            coordenadas[l][m + 1] = 'N';
          }
          i--;//andei no mapa norte
        }
      }
      else
      {
        //sul
        if(coordenadas[l][m + 1] == 'S')
        {
          coordenadas[l][m] += 1;
        }
        else
        {
          l++; // Apenas quando a próxima cordenada eh diferente avançamos no vetor
          coordenadas[l][m] = 1;
          coordenadas[l][m + 1] = 'S';
        }
        i++;//andei no mapa sul
      }
    }
  }
  l++;//Ultimo lance para finalizar o vetor;
  coordenadas[l][m] = '\0';//Finalizei o vetor
  imprime_coordenada(coordenadas);
}

int movimento(int labirinto[LINHAS][COLUNAS], int i, int j, int linha_fim, int coluna_fim)//condicoes de movimentação recursao
{
  int resultado = labirinto[i][j];//0 1 (ou 2 para migalha de pão)
  if(resultado == 0)//Eh um corredor?
  {
    labirinto[i][j] = 2; //Coloco uma migalha de pão
    imprime_matriz(labirinto);
  }
  if(linha_fim == i && coluna_fim == j && resultado == 0)//Cheguei ao fim do labirinto
  {
    resultado = 3;
    labirinto[i][j] = 3;
  }
  else//o carinha nao chegou ao fim? continua procurando!
  {
    if(resultado == 0)//TEMP:reduçao para !labirinto é ilegível?
    {
      if(i == 0)
      {
        resultado = movimento(labirinto, (i + 1), j, linha_fim, coluna_fim);//sul
        if(j == 0 && resultado < 3)// && resultado != 0 ele para a busca e retorna 0 (Cheguei ao fim)
        {
          resultado = movimento(labirinto, i, (j + 1), linha_fim, coluna_fim);//leste
          if (labirinto[i][j] == 2 && resultado < 3)//Ou seja, se as proximas casas nao são validas
          {
          labirinto[i][j] = 0;//retornarei resultado mas recolho a migalha de pão
          }
        }
        else if(j == COLUNAS - 1 && resultado < 3)
        {
          resultado = movimento(labirinto, i, (j - 1), linha_fim, coluna_fim);//oeste
          if (labirinto[i][j] == 2 && resultado < 3)//Ou seja, se as proximas casas nao são validas
          {
            labirinto[i][j] = 0;//retornarei resultado mas recolho a migalha de pão
          }
        }
        else if(resultado < 3)
        {
          resultado = movimento(labirinto, i, (j + 1), linha_fim, coluna_fim);//leste
          if(resultado < 3)
          {
            resultado = movimento(labirinto, i, (j - 1), linha_fim, coluna_fim);//oeste
            if (labirinto[i][j] == 2 && resultado < 3)//Ou seja, se as proximas casas nao são validas
            {
              labirinto[i][j] = 0;//retornarei resultado mas recolho a migalha de pão
            }
          }
        }
      }
      else if(i == LINHAS - 1 && resultado < 3)//TEMP:Nessa questão 19
      {
        resultado = movimento(labirinto, (i - 1), j, linha_fim, coluna_fim);//norte
        if(j == 0 && resultado < 3)
        {
          resultado = movimento(labirinto, i, (j + 1), linha_fim, coluna_fim);//leste
          if (labirinto[i][j] == 2 && resultado < 3)//Ou seja, se as proximas casas nao são validas
          {
            labirinto[i][j] = 0;//retornarei resultado mas recolho a migalha de pão
          }
        }
        else if(j == COLUNAS - 1 && resultado < 3)
        {
          resultado = movimento(labirinto, i, (j - 1), linha_fim, coluna_fim);//oeste
          if (labirinto[i][j] == 2 && resultado < 3)//Ou seja, se as proximas casas nao são validas
          {
            labirinto[i][j] = 0;//retornarei resultado mas recolho a migalha de pão
          }
        }
        else if(resultado < 3)
        {
          resultado = movimento(labirinto, i, (j + 1), linha_fim, coluna_fim);//leste
          if(resultado < 3)
          {
            resultado = movimento(labirinto, i, (j - 1), linha_fim, coluna_fim);//oeste
            if (labirinto[i][j] == 2 && resultado < 3)//Ou seja, se as proximas casas nao são validas
            {
              labirinto[i][j] = 0;//retornarei resultado mas recolho a migalha de pão
            }
          }
        }
      }
      else if(resultado < 3)//qualquer i estranho
      {
        resultado = movimento(labirinto, (i + 1), j, linha_fim, coluna_fim);//sul
        if(resultado < 3)
        {
          resultado = movimento(labirinto, (i - 1), j, linha_fim, coluna_fim);//norte
          if(j == 0 && resultado < 3)
          {
            resultado = movimento(labirinto, i, (j + 1), linha_fim, coluna_fim);//leste
            if (labirinto[i][j] == 2 && resultado < 3)//Ou seja, se as proximas casas nao são validas
            {
              labirinto[i][j] = 0;//retornarei resultado mas recolho a migalha de pão
            }
          }
          else if(j == COLUNAS - 1 && resultado < 3)//Nesse caso 29
          {
            resultado = movimento(labirinto, i, (j - 1), linha_fim, coluna_fim);//oeste
            if (labirinto[i][j] == 2 && resultado < 3)//Ou seja, se as proximas casas nao são validas
            {
              labirinto[i][j] = 0;//retornarei resultado mas recolho a migalha de pão
            }
          }
          else if(resultado < 3)//qq jota estranho
          {
            resultado = movimento(labirinto, i, (j + 1), linha_fim, coluna_fim);//leste
            if(resultado < 3)
            {
              resultado = movimento(labirinto, i, (j - 1), linha_fim, coluna_fim);//oeste
              if (labirinto[i][j] == 2 && resultado < 3)//Ou seja, se as proximas casas nao são validas
              {
                labirinto[i][j] = 0;//retornarei resultado mas recolho a migalha de pão
              }
            }
          }
        }
      }
    }
  }
  return resultado;
}

void labirinto()
{
  int linha_inicio, coluna_inicio, linha_fim, coluna_fim, i, j;
  int labirinto[LINHAS][COLUNAS];
  int resultado;
  printf("Labirinto IP L3q4\n=================\n");
  do
  {
    printf("\nDigite os indices entre 0 e %d para linha e 0 e %d para coluna correspondente a\nposicao do prof. adriano e seus monitores, por ex: 0 0\n\nDigite a posicao inicial:", COLUNAS - 1, LINHAS - 1);
    scanf(" %d %d", &coluna_inicio, &linha_inicio);//Perceba a inversão de linhas colunas
    printf("==========================================\nDigite a posicao da saida: ");
    scanf(" %d %d", &coluna_fim, &linha_fim);
    system("cls");//limpa tela
  }
  while(!(linha_inicio >= 0 && linha_inicio < LINHAS && linha_fim >= 0 && linha_fim < LINHAS && coluna_inicio >= 0 && coluna_inicio < COLUNAS && coluna_fim >= 0 && coluna_fim < COLUNAS));
  printf("\nRecebendo dados:\n");
  for(i = 0; i < LINHAS; i++)//Perceba a inversão de linhas colunas
  {
    for(j = 0; j < COLUNAS; j++)
    {
      scanf(" %1d", &labirinto[i][j]);
    }
  }
  fflush(stdin);//TEMP: O uso de formatação %1 exige limpeza do cache se tiver um scanf futuro
  printf("Enviando dados...");
  imprime_matriz(labirinto);
  resultado = movimento(labirinto, linha_inicio, coluna_inicio, linha_fim, coluna_fim);
  if(resultado == 3)
  {
    printf("\nExiste solucao\n");//chamar funcao que irá limpar as migalhas colocar num vetor de define 400 posicoes e construir um mapa otimizado.
    constroiu_coordenadas(labirinto, linha_inicio, coluna_inicio);
  }
  else
  {
    printf("\nNao ha solucao para o labirinto.\nVerifique as coordenadas de saida ou o mapa e tente novamente\n");
  }
}

int main()
{
  labirinto();
  return 0;
}



//      labirinto_auxiliar[i][j] = labirinto[i][j];//TEMP:O labirinto auxiliar irá receber valor 2(simbolizando migalhas de pão) para cada passagem, evitando loops no labirinto
//Estou usando o auxiliar para não modificar o original, se fizer função retornando (antes do return para restarar
//  movimento_possivel();
//      labirinto[i][j] = 2; //Coloco uma migalha de pão
//    if(labirinto[i][j] == 2)//migalha na saida!
//    {
//      labirinto[i][j] = 0;//Reconstroi a matriz original(0), retirando a migalha de pão(2) de tras para frente.
//      resultado = 2;//significa não posso continuar, já passei por ali.
//    }
