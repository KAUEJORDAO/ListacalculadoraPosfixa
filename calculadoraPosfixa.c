#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "calculadoraPosfixa.h"
#define M_PI 3.14159265358979323846
//botei a definição de PI aqui pq meu pc não estava reconhecendo a biblioteca math.h


void inicializar(Pilha *pilha)
{
    pilha->topo = NULL;
}

void empilhar(Pilha *pilha, double valor)
{
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL)
    {
        printf("Erro: Falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    novoNo->dado = valor;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

double desempilhar(Pilha *pilha)
{
    if (pilha->topo != NULL)
    {
        No *temp = pilha->topo;
        double valor = temp->dado;
        pilha->topo = temp->proximo;
        free(temp);
        return valor;
    }
    else
    {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}


double avaliarExpressaoPosfixada(const char *expressao)
{


    Pilha pilha;
    inicializar(&pilha);

    for (int i = 0; expressao[i] != '\0'; ++i)
    {
     

        if (isdigit(expressao[i]) || expressao[i] == '.')
        {
            double numero = strtod(expressao + i, NULL);
            empilhar(&pilha, numero);

            while (isdigit(expressao[i]) || expressao[i] == '.')
            {
                ++i;
            }
            --i;
        }
        else if (expressao[i] == ' ' || expressao[i] == '\t')
        {
     
            continue;
        }
        else
        {
    
            switch (expressao[i])
            {
            case '+':
                empilhar(&pilha, desempilhar(&pilha) + desempilhar(&pilha));
                break;
            case '-':
            {
                double operando2 = desempilhar(&pilha);
                empilhar(&pilha, desempilhar(&pilha) - operando2);
            }
            break;
            case '*':
                empilhar(&pilha, desempilhar(&pilha) * desempilhar(&pilha));
                break;
            case '/':
            {
                double operando2 = desempilhar(&pilha);
                if (operando2 != 0.0)
                {
                    empilhar(&pilha, desempilhar(&pilha) / operando2);
                }
                else
                {
                    printf("Erro: Divisão por zero\n");
                    exit(EXIT_FAILURE);
                }
            }
            break;
            case 'l':
                if (expressao[i + 1] == 'o' && expressao[i + 2] == 'g')
                {
                    i += 2;
                    double operando1 = desempilhar(&pilha);

                    if (operando1 <= 0.0)
                    {
                        printf("Erro: Argumento do logaritmo deve ser maior que zero\n");
                        exit(EXIT_FAILURE);
                    }

                    empilhar(&pilha, log10(operando1));
                }
                break;
            case '^':
            {
                double base = desempilhar(&pilha);
                double expoente = desempilhar(&pilha);
                empilhar(&pilha, pow(base, expoente));
            }
            break;
            case 's':
                if (expressao[i + 1] == 'e' && expressao[i + 2] == 'n')
                {
                    i += 2;
                    double valor = desempilhar(&pilha);
                    empilhar(&pilha, sin(valor * M_PI / 180.0)); 
                }
                break;
            case 'c':
                if (expressao[i + 1] == 'o' && expressao[i + 2] == 's')
                {
                    i += 2;
                    double valor = desempilhar(&pilha);
                    empilhar(&pilha, cos(valor * M_PI / 180.0)); 
                }
                break;
            case 't':
                if (expressao[i + 1] == 'a' && expressao[i + 2] == 'n')
                {
                    i += 2;
                    double valor = desempilhar(&pilha);
                    empilhar(&pilha, tan(valor)); 
                }
                break;
            case 'r':
                if (expressao[i + 1] == 't')
                {
                    i += 1;
                    double valor = desempilhar(&pilha);
                    if (valor >= 0.0)
                    {
                        empilhar(&pilha, sqrt(valor));
                    }
                    else
                    {
                        printf("Erro: Raiz quadrada de número negativo\n");
                        exit(EXIT_FAILURE);
                    }
                }
                break;
            default:
                printf("Erro: Operador ou função inválida (%c)\n", expressao[i]);
                exit(EXIT_FAILURE);
            }
        }
        

    }

    
    return desempilhar(&pilha);
}