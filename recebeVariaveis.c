#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TAM 20

int *leArquivo(int *count){
    /*
    Conta a qtd de variaveis dentro do arquivo, com esse valor
    é alocado um vetor e gravado essas variaveis.
    */
    int c = 0, i = 0;
    FILE *arquivo;
    char nome[TAM];

    printf("\nInforme o nome do arquivo: "); 
    scanf(" %[^\n]", nome);

    arquivo = fopen(nome, "r");

    if (!arquivo) {
        printf("\nArquivo nao encontrado\n");
    } else {
        while ((c = fgetc(arquivo)) != EOF) {
            if (c == ' ' || c == '\n')
            *count = *count + 1; 
        }
    }
    fclose(arquivo);
    //printf("\nContei %d variaveis\n", *count);
    int *novo = (int *) malloc((*count) * sizeof(int));

    arquivo = fopen(nome, "r");
        for (i = 0; i < *count; i++)
            fscanf(arquivo, "%d", (novo + i));
    fclose(arquivo);    
    return novo; 
}

void cabecalho(int variaveis[], int *count){
    int i, j, x = *count;
    printf("\n");
    //Cabecalho
    for (i = 0; i < x * 2; i++)
        printf("#");
    printf("\n\nVariaveis -->\t"); 
    j = 0; 
    while(x --> 0) 
        printf("%d ", variaveis[j++]); 
    printf("\n\n");
    
    //Rodape
    x = *count;
    for (i = 0; i < x * 2; i++) 
        printf("#");
}

int somatorio(int variaveis[], int *count){
    int somatorio = 0;
    for (int i = 0; i < *count; i++) somatorio += variaveis[i];
    return somatorio;
}

int quadradoSoma(int variaveis[], int *r_somatorio){
    int quadradoSoma = 0;
    quadradoSoma = pow(*r_somatorio, 2);
    return quadradoSoma;
}

int somaQuadrado(int variaveis[], int *count){
    int resultado = 0;
    for (int i = 0; i < *count; i++) resultado += pow(variaveis[i],2);
    return resultado;
}

float media(int *r_somatorio, int *count){
    float resultado = 0;
    resultado = (float) *r_somatorio / *count;
    return resultado;
}

void mediana(int vetor[], int *tam){
    int i, contador, aux, x = *tam;;
    float mediana = 0.0;
    //Algoritmo de ordenação Bubblesort:
    for (contador = 1; contador < *tam; contador++) {
        for (i = 0; i < *tam - 1; i++) {
            if (vetor[i] > vetor[i + 1]) {
            aux = vetor[i];
            vetor[i] = vetor[i + 1];
            vetor[i + 1] = aux;
            }
        }
    }
    printf(" --> Variaveis ordenadas:\n");
    i = 0; printf("\n\t"); while(x --> 0) printf("%d ", vetor[i++]); printf("\n");

    //Mediana
    if (*tam % 2 == 0) { // É par
        mediana = (float) (vetor[*tam / 2 - 1] + (vetor[(*tam + 2) / 2 - 1])) / 2;
        printf("\n --> Mediana é:\t\t\t%.2f\n", mediana);
    } else {            // É impar
        mediana = (float) vetor[(*tam + 1) / 2 - 1];
        printf("\n --> Mediana é:\t\t\t%.2f\n", mediana);
    }
}

float variancia(int variaveis[], int *somaQuad, int *quadSoma, int *count){
    float resultado = 0;
    resultado = (float) (*somaQuad - (*quadSoma / *count)) / (*count - 1);
    return resultado;
}

float desvioPadrao(float *variancia){
    float resultado = 0;
    resultado = sqrt(*variancia);
    return resultado;
}

int main(){
    int *novoVetor;
    //int variaveis[N] = {319,199,110,63,21,315,26,63};
    int r_somatorio, raiz, tamanho, quadSoma, somaQuad, count;
    r_somatorio = raiz = tamanho = quadSoma = somaQuad = count = 0;
    float desvio, r_variancia, r_media;
    desvio = r_variancia = r_media = 0;
    
    novoVetor = leArquivo(&count);

    // cabecalho(variaveis);
    cabecalho(novoVetor, &count);
    
    printf("\n\n------------------------------------------\n\n");
    printf("\t #### Resultados: #####\n");
    
    // r_somatorio = somatorio(variaveis);
    r_somatorio = somatorio(novoVetor, &count);
    printf("\n --> O somatorio é: \t\t%d\n", r_somatorio);

    quadSoma = quadradoSoma(novoVetor, &r_somatorio);
    printf(" --> O quadrado da soma é: \t%d\n", quadSoma);

    somaQuad = somaQuadrado(novoVetor, &count);
    printf(" --> Soma dos quadrados: \t%d\n",somaQuad);
    
    r_media = media(&r_somatorio, &count);
    printf(" --> A media é: \t\t%.2f\n", r_media);

    mediana(novoVetor, &count);

    r_variancia = variancia(novoVetor, &somaQuad, &quadSoma, &count);
    printf(" --> A variancia é: \t\t%.2f\n", r_variancia);

    desvio = desvioPadrao(&r_variancia);
    printf(" --> O desvio padrao é: \t%.1f\n", desvio);
    return 0;
}