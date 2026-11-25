#include <stdio.h>

#define MAX 100

typedef struct {
    char senha[12];
    int cat;    /* 1: Urgente, 2: Preferencial, 3: Normal */
    int status; /* 0: Esperando, 1: Em atendimento, 2: Finalizado */
    char genero;
    int idade;
} Paciente;

Paciente fila[MAX];
int total = 0, cU = 0, cP = 0, cN = 0;

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int lerInt(const char *msg, int min, int max) {
    int v;
    while (1) {
        printf("%s", msg);
        if (scanf("%d", &v) == 1 && v >= min && v <= max) {
            limparBuffer();
            return v;
        }
        limparBuffer();
        printf("Valor invalido (%d a %d).\n", min, max);
    }
}

char lerChar(const char *msg, const char *validos) {
    char c;
    while (1) {
        printf("%s", msg);
        if (scanf(" %c", &c) == 1) {
            limparBuffer();
            if (c >= 'a' && c <= 'z') c -= 32;
            for (int i = 0; validos[i] != '\0'; i++) {
                if (validos[i] == c) return c;
            }
        } else {
            limparBuffer();
        }
        printf("Opcao invalida (%s).\n", validos);
    }
}

const char *nomeCat(int cat) {
    return (cat == 1) ? "Urgente" : (cat == 2) ? "Preferencial" : "Normal";
}

int classificar(char gen, int idade, int gest, int lact, int pcd, int obeso) {
    if (idade > 80) return 1;
    if (gest || lact || pcd || obeso ||
        (gen == 'F' && idade >= 60) || (gen == 'M' && idade >= 65)) return 2;
    return 3;
}

void gerarSenha(Paciente *p) {
    if (p->cat == 1) sprintf(p->senha, "U%03d", ++cU);
    else if (p->cat == 2) sprintf(p->senha, "P%03d", ++cP);
    else sprintf(p->senha, "N%03d", ++cN);
}

void cadastrar(void) {
    if (total >= MAX) { printf("Limite de pacientes atingido.\n"); return; }

    Paciente p = {0};
    p.genero = lerChar("Genero [M/F/O]: ", "MFO");
    p.idade = lerInt("Idade: ", 0, 130);
    int gest = (p.genero == 'F') ? (lerChar("Gestante [S/N]? ", "SN") == 'S') : 0;
    int lact = (p.genero != 'M') ? (lerChar("Lactante [S/N]? ", "SN") == 'S') : 0;
    int pcd = (lerChar("Necessidade especial [S/N]? ", "SN") == 'S');
    int obeso = (lerChar("Obesidade [S/N]? ", "SN") == 'S');

    p.cat = classificar(p.genero, p.idade, gest, lact, pcd, obeso);
    gerarSenha(&p);
    fila[total++] = p;
    printf(">> Senha emitida: %s (%s)\n", p.senha, nomeCat(p.cat));
}

int buscarProximo(void) {
    for (int cat = 1; cat <= 3; cat++)
        for (int i = 0; i < total; i++)
            if (fila[i].status == 0 && fila[i].cat == cat) return i;
    return -1;
}

int buscarAtual(void) {
    for (int i = 0; i < total; i++)
        if (fila[i].status == 1) return i;
    return -1;
}

void chamarPaciente(void) {
    if (buscarAtual() != -1) {
        printf("Finalize o atendimento atual antes de chamar outro.\n");
        return;
    }
    int idx = buscarProximo();
    if (idx == -1) { printf("Fila vazia.\n"); return; }
    fila[idx].status = 1;
    printf(">> Chamando: %s (%s)\n", fila[idx].senha, nomeCat(fila[idx].cat));
}

void finalizarAtendimento(void) {
    int idx = buscarAtual();
    if (idx == -1) { printf("Nenhum atendimento em andamento.\n"); return; }
    fila[idx].status = 2;
    printf(">> Senha %s finalizada.\n", fila[idx].senha);
}

void exibirPainel(void) {
    int atual = buscarAtual();
    int qtd[4] = {0};

    printf("\n================ PAINEL DE CHAMADA ================\n");
    if (atual != -1)
        printf("Em atendimento: %s (%s)\n", fila[atual].senha, nomeCat(fila[atual].cat));
    else
        printf("Em atendimento: Nenhum\n");

    printf("Proximas: ");
    int temEspera = 0;
    for (int cat = 1; cat <= 3; cat++) {
        for (int i = 0; i < total; i++) {
            if (fila[i].status == 0 && fila[i].cat == cat) {
                printf("%s ", fila[i].senha);
                qtd[cat]++;
                temEspera = 1;
            }
        }
    }
    if (!temEspera) printf("Nenhuma");
    printf("\nEspera -> Urgente: %d | Preferencial: %d | Normal: %d\n", qtd[1], qtd[2], qtd[3]);
    printf("===================================================\n");
}

int main(void) {
    int op;
    do {
        exibirPainel();
        printf("1-Cadastrar | 2-Proxima senha | 3-Chamar | 4-Em atendimento | 5-Finalizar | 0-Sair\n");
        op = lerInt("Opcao: ", 0, 5);

        if (op == 1) cadastrar();
        else if (op == 2) {
            int p = buscarProximo();
            if (p != -1) printf(">> Proxima: %s (%s)\n", fila[p].senha, nomeCat(fila[p].cat));
            else printf("Fila vazia.\n");
        }
        else if (op == 3) chamarPaciente();
        else if (op == 4) {
            int a = buscarAtual();
            if (a != -1) printf(">> Atual: %s (%s) | %c, %d anos\n", fila[a].senha, nomeCat(fila[a].cat), fila[a].genero, fila[a].idade);
            else printf("Nenhum paciente em atendimento.\n");
        }
        else if (op == 5) finalizarAtendimento();
    } while (op != 0);

    return 0;
}
