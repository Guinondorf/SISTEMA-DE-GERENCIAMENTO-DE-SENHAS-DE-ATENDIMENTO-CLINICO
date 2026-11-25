# Sistema de Gerenciamento de Senhas Clínicas

## Objetivo
Gerenciar a triagem, emissão de senhas e fila de atendimento de uma clínica médica em linguagem C, respeitando prioridades (**Urgente > Preferencial > Normal**) e ordem de chegada (**FIFO**).

## Funcionalidades
* **Cadastro e Classificação:** Lê dados do paciente e gera senha sequencial por categoria:
  * `U001...` (**Urgente**): idade maior que 80 anos.
  * `P001...` (**Preferencial**): gestante, lactante, necessidade especial, obesidade, mulher com 60+ anos ou homem com 65+ anos.
  * `N001...` (**Normal**): demais pacientes.
* **Atendimento:** Consulta a próxima senha, chama o próximo paciente, exibe quem está em atendimento e finaliza o atendimento (sem retorno à fila).
* **Painel:** Mostra a senha em atendimento, a categoria, a fila de espera ordenada e a quantidade por categoria.

## Validação e Testes

### Validações Implementadas
* **Entradas numéricas e textuais:** As funções `lerInt()` e `lerChar()` validam tipos, faixas de valores (idade entre 0 e 130; opções do menu entre 0 e 5) e limpam o buffer de entrada (`limparBuffer()`) para evitar falhas de leitura.
* **Integridade da fila:** O sistema impede chamadas simultâneas antes da finalização do atendimento atual, bloqueia finalizações sem paciente ativo e garante que senhas já atendidas (`status = 2`) não retornem à fila.

### Testes Realizados
* **Classificação de Prioridades:** Validada a emissão independente (`U001`, `P001`, `N001`), incluindo casos de fronteira etária (mulher com 60 anos e homem com 65 anos como Preferencial; paciente com 81 anos como Urgente).
* **Precedência e FIFO:** Validada a ordem de chamada (`Urgente > Preferencial > Normal`) e a manutenção da ordem de chegada dentro da mesma categoria (`P001` chamado antes de `P002`).
* **Tratamento de Erros:** Testadas entradas inválidas (letras em campos numéricos e caracteres fora do padrão `M/F/O` e `S/N`), com rejeição e nova solicitação ao usuário.

## Compilação e Execução
```bash
gcc main.c -o clinica
./clinica
