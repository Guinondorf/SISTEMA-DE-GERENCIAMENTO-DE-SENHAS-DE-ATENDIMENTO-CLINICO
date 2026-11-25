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

## Compilação e Execução
```bash
gcc main.c -o clinica
./clinica
