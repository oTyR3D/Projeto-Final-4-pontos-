#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum
{
    ETANOL,
    GASOLEO,
    GASOLINA
} TipoCombustivel;

typedef struct Veiculo
{
    char proprietario[50];
    TipoCombustivel combustivel;
    char modelo[50];
    char cor[20];
    float numeroChassi;
    int anoFabricacao;
    char placa[7]; 
    struct Veiculo *proximo;
} Veiculo;

TipoCombustivel validarCombustivel(char combustivel)
{
    switch (combustivel)
    {
    case 'e':
        return ETANOL;
    case 'g':
        return GASOLEO;
    case 'p':
        return GASOLINA;
    default:
        printf("Tipo de combustível inválido! Tente novamente.\n");
        exit(EXIT_FAILURE);
    }
}

Veiculo *criarVeiculo(char dono[], TipoCombustivel combustivel, char tipoModelo[], char cor[], float nChassi, int ano, char placa[])
{
    Veiculo *novoCarro = (Veiculo *)malloc(sizeof(Veiculo));
    if (novoCarro == NULL)
    {
        perror("Erro ao alocar memória para o veículo");
        exit(EXIT_FAILURE);
    }

    strcpy(novoCarro->proprietario, dono);
    novoCarro->combustivel = combustivel;
    strcpy(novoCarro->modelo, tipoModelo);
    strcpy(novoCarro->cor, cor);
    novoCarro->numeroChassi = nChassi;
    novoCarro->anoFabricacao = ano;
    strcpy(novoCarro->placa, placa);
    novoCarro->proximo = NULL;

    return novoCarro;
}

int validarPlaca(char placa[])
{
    if (strlen(placa) != 7)
    {
        printf("A placa deve ter 7 caracteres.\n");
        return 1;
    }

    for (int i = 0; i < 2; ++i)
    {
        if (!((placa[i] >= 'A' && placa[i] <= 'Z') || (placa[i] >= 'a' && placa[i] <= 'z')))
        {
            printf("Os três primeiros caracteres devem ser alfabéticos.\n");
            return 1;
        }
    }

    for (int i = 3; i < 7; ++i)
    {
        if (!(placa[i] >= '0' && placa[i] <= '9'))
        {
            printf("Os quatro últimos caracteres devem ser numéricos.\n");
            return 1;
        }
    }
    printf("Placa válida!\n");
    return 0;
}

void cadastrarVeiculo(Veiculo **lista)
{
    char dono[50];
    TipoCombustivel combustivel;
    char tipoModelo[50];
    char cor[20];
    float nChassi;
    int ano;
    char placa[7];

    printf("Nome do proprietário: ");
    scanf("%s", dono);
    printf("Tipo de combustível (e - Etanol, g - Gasóleo, p - Gasolina): ");
    scanf(" %c", &combustivel);
    combustivel = validarCombustivel(combustivel);
    printf("Modelo do veículo: ");
    scanf("%s", tipoModelo);
    printf("Cor do veículo: ");
    scanf("%s", cor);
    printf("Número do Chassi: ");
    scanf("%f", &nChassi);
    printf("Ano de fabricação: ");
    scanf("%d", &ano);
    printf("Placa do veículo (apenas 7 caracteres): ");
    scanf("%s", placa);

    validarPlaca(placa);

    Veiculo *novoCarro = criarVeiculo(dono, combustivel, tipoModelo, cor, nChassi, ano, placa);

    novoCarro->proximo = *lista;
    *lista = novoCarro;
}

void imprimirLista(Veiculo *lista)
{
    Veiculo *atual = lista;
    while (atual != NULL)
    {
        printf("Proprietário: %s\n", atual->proprietario);
        printf("Combustível: ");
        switch (atual->combustivel)
        {
        case ETANOL:
            printf("Etanol\n");
            break;
        case GASOLEO:
            printf("Gasóleo\n");
            break;
        case GASOLINA:
            printf("Gasolina\n");
            break;
        }
        printf("Modelo: %s\n", atual->modelo);
        printf("Cor: %s\n", atual->cor);
        printf("Número do Chassi: %.2f\n", atual->numeroChassi);
        printf("Ano de Fabricação: %d\n", atual->anoFabricacao);
        printf("Placa: %s\n", atual->placa);
        printf("\n");

        atual = atual->proximo;
    }
}

void funcaoA(Veiculo *lista)
{
    Veiculo *atual = lista;
    printf("Proprietários cujos carros são do ano de 2010 ou mais e que usam gasóleo\n");

    while (atual != NULL)
    {
        if (atual->anoFabricacao >= 2010 && atual->combustivel == GASOLEO)
        {
            printf("Proprietário: %s\n", atual->proprietario);
            printf("Combustível: Gasóleo\n");
            printf("Modelo: %s\n", atual->modelo);
            printf("Cor: %s\n", atual->cor);
            printf("Número do Chassi: %.2f\n", atual->numeroChassi);
            printf("Ano de Fabricação: %d\n", atual->anoFabricacao);
            printf("Placa: %s\n", atual->placa);
            printf("\n");
        }

        atual = atual->proximo;
    }
}

void funcaoB(Veiculo *lista)
{
    Veiculo *atual = lista;
    printf("Placas que começam com j e terminam com 0, 2, 4 ou 7\n");

    while (atual != NULL)
    {
        if (atual->placa[0] == 'j' && (atual->placa[6] == '0' || atual->placa[6] == '2' || atual->placa[6] == '4' || atual->placa[6] == '7'))
        {
            printf("Placa: %s\n", atual->placa);
            printf("Proprietário: %s\n", atual->proprietario);
            printf("\n");
        }

        atual = atual->proximo;
    }
}

void funcaoC(Veiculo *lista)
{
    Veiculo *atual = lista;
    printf("Modelo e cor dos veículos com placas que têm vogal no segundo caractere e a soma dos valores numéricos é um número par\n");

    while (atual != NULL)
    {
        int somaNumeros = 0;
        for (int i = 3; i < 7; i++)
        {
            somaNumeros += atual->placa[i] - '0';
        }

        if ((atual->placa[1] == 'a' || atual->placa[1] == 'e' || atual->placa[1] == 'i' || atual->placa[1] == 'o' || atual->placa[1] == 'u') && somaNumeros % 2 == 0)
        {
            printf("Modelo: %s\n", atual->modelo);
            printf("Cor: %s\n", atual->cor);
            printf("\n");
        }

        atual = atual->proximo;
    }
}

void funcaoD(Veiculo *lista, float nChassi)
{
    Veiculo *atual = lista;
    printf("Troca de proprietário com o fornecimento do número do chassi apenas para carros com placas que não possuem nenhum dígito igual a zero\n");

    while (atual != NULL)
    {
        int temZero = 0;
        for (int i = 0; i < 7; i++)
        {
            if (atual->placa[i] == '0')
            {
                temZero = 1; 
                break;
            }
        }
        if (temZero == 0 && atual->numeroChassi == nChassi)
        {
            printf("Número do Chassi: %.2f\n", atual->numeroChassi);
            printf("Placa: %s\n", atual->placa);
            printf("Digite o novo proprietário: ");
            scanf("%s", atual->proprietario);
            printf("Troca de proprietário realizada com sucesso!\n");
            return;
        }
        else
        {
            printf("Veículo com o número do chassi fornecido não encontrado ou placa possui dígito igual a zero.\n");
        }
        atual = atual->proximo;
    }
}

int main()
{
    Veiculo *listaCarros = NULL;
    int escolha;

    do
    {
        printf("Escolha uma opção\n");
        printf("1: Cadastrar veículo\n");
        printf("2: Imprimir lista\n");
        printf("3: Função A\n");
        printf("4: Função B\n");
        printf("5: Função C\n");
        printf("6: Função D\n");
        printf("0: Sair\n");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            cadastrarVeiculo(&listaCarros);
            break;
        case 2:
            imprimirLista(listaCarros);
            break;
        case 3:
            funcaoA(listaCarros);
            break;
        case 4:
            funcaoB(listaCarros);
            break;
        case 5:
            funcaoC(listaCarros);
            break;
        case 6:
            printf("Digite o número do Chassi para a troca de proprietário: ");
            float nChassi;
            scanf("%f", &nChassi);
            funcaoD(listaCarros, nChassi);
            break;
        default:
            break;
        }
    } while (escolha != 0);

    while (listaCarros != NULL)
    {
        Veiculo *temp = listaCarros;
        listaCarros = listaCarros->proximo;
        free(temp);
    }

    return 0;
}
