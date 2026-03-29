# Room Reservation System

Sistema de gerenciamento de reserva de salas com controle de capacidades e horários.


## Descrição do Sistema

O projeto implementa um sistema de reserva de salas que permite ao usuário visualizar os horários ocupados, solicitar uma reserva e cancelar uma reserva feita anteriormente.

As reservas são organizadas pelo dia da semana, horário de início e de término de cada reunião. O sistema verifica a disponibilidade analisando quantas pessoas as salas comportam e seus horários não ocupados, e realiza a reserva na primeira sala que atender aos parâmetros do usuário; caso contrário, informa a indisponibilidade.

O sistema foi projetado para:
1. Permitir consulta rápida no histórico de reservas;
2. Reservar ou desmarcar um horário;
3. Evitar conflitos de horários;
4. Ser de simples compilação e uso;
5. Gerenciar corretamente o uso de memória alocada;

### Dinâmica do Sistema
Ao solicitar uma reserva (`ReservationSystemn`), o usuário preenche suas exigências (dia da semana, horário de início e fim, quantidade de alunos e o nome da disciplina), e o sistema percorre cada sala disponível até encontrar alguma que satisfaça precisamente os parâmetros passados. Caso isso ocorra, é acrescentada ao histórico da sala uma reserva (objeto da classe `Reserva`), correspondente à solicitação realizada, e os horários reservados passam a ser classificados como indisponíveis para futuras tentativas. Caso contrário, o usuário é informado de que não foi possível concluir a operação.

Ao cancelar uma reserva, o sistema acessa diretamente os horários da sala correspondente e os torna disponíveis para futuras tentativas, além de remover a reserva desejada de seu histórico.

A última operação disponível ao usuário é a de obter as reservas realizadas (`printSchedule`). Nela, o sistema acessa cada sala existente e organiza seu histórico de reservas a fim de exibir (printar) cada horário ocupado de forma ordenada, por dia e por horário.

## Organização Interna
O código está dividido em 5 arquivos principais, cujas funções serão esclarecidas posteriormente:

1. `ReservationRequest.hpp`
2. `ReservationRequest.cpp`
3. `ReservationSystemn.hpp`
4. `ReservationSystemn.cpp`
5. `main.cpp`

Eles podem ser divididos em três grupos.

### __1. Reservation Request__
Composto pelos arquivos `ReservationRequest.hpp` e `ReservationRequest.cpp`, contendo suas declarações e implementações, respectivamente.

Nestes módulos, foi implementada a classe `ReservationRequest`, que, ao ser criada, carrega consigo as exigências da solicitação de reserva impostas pelo usuário. É capaz de retornar o valor de cada um de seus parâmetros por meio de seus métodos getters.

### __2. Reservation Systemn__
Composto pelos arquivos `ReservationSystemn.hpp` e `ReservationSystemn.cpp`, contendo suas declarações e implementações, respectivamente.

Aqui, 5 classes são implementadas: `Reserva`, `ArrReservaDinamico`, `Semana`, `Sala` e `ReservationSystemn`.

- **Reserva**: Guarda os dados de uma solicitação bem-sucedida e tem a capacidade de fornecer os valores de seus parâmetros.

- **ArrReservaDinamico**: Guarda o histórico de reservas de uma sala. Possui a capacidade de se reestruturar, facilitando o acréscimo (em caso de solicitações bem-sucedidas) e a remoção (em caso de desmarcação) de reservas, além de evitar que o limite seja atingido ao duplicar seu tamanho quando a capacidade máxima é alcançada. Isso otimiza o uso de memória do sistema, que aloca mais espaço apenas quando necessário. Além disso, consegue se ordenar, a fim de facilitar operações como a exibição dos horários ocupados ao usuário.

- **Semana**: Gerencia os horários de uma sala em cada dia da semana. Preenche, desmarca e informa horários, tornando possível o controle de reservas sem conflitos de dias ou horários.

- **Sala**: É o coração do sistema. Gerencia localmente (ou seja, na própria sala) as reservas e chama internamente métodos das outras classes citadas anteriormente. Por meio dela são feitas as reservas, desmarcações, consultas e exibição do histórico de reservas.

- **ReservationSystemn**: Classe central do sistema. Ao ser inicializada, gera as salas com suas respectivas capacidades e fornece a interface para que o usuário solicite, cancele e visualize reservas.

### __3. Main__
Composto pelo arquivo `main.cpp`. Reúne exemplos de uso que demonstram o funcionamento e as respostas do sistema.

## Instruções de Compilação
Para compilar o projeto, siga os passos abaixo:
No terminal use:
```
g++ main.cpp ReservationSystem.cpp ReservationRequest.cpp -o reservation_system
```
O executável `reservation_system` será gerado. O programa inicia a partir da função `main()`, definida em `main.cpp`.

## Instruções de uso
Para executar o programa, utilize:  
```
./reservation_system
```
É necessário estar na pasta correta


### Exemplos de uso
Segue uma explicação dos exemplos que demonstram o funcionamento do sistema contidos em `main.cpp`.

__Observação__  
- O  sistema utiliza valores booleanos para indicar sucesso ou falha nas operações (`1` para sucesso ou `0` para fracasso)

#### 1. Criação do sistema
O sistema é inicializado com 3 salas, com diferentes capacidades:
- Sala 1: 30 alunos  
- Sala 2: 50 alunos  
- Sala 3: 80 alunos 

#### 2. Criação de Requests
São criadas várias requests de reserva, cada uma contendo:
- Nome da disciplina  
- Dia da semana  
- Horário de início e fim  
- Quantidade de alunos  

Exemplo: `ReservationRequest request3("GA", "segunda", 7, 9, 29);`

#### 3. Reservas bem-sucedidas
As primeiras reservas são realizadas com sucesso e assim devem ser exibidos os valores 1, 1, 1, 1 indicando que cada request se consolidou como um reserva.


#### 4. Reservas malsucedidas
As tentativas seguintes falham por diferentes motivos:

- Conflito de horário  
- Número de alunos acima da capacidade das salas  
- Horário fora do período permitido 

E por isso a sequência a ser exibida é de 0, 0, 0.

#### 5. Cancelamentos
São realizados testes de cancelamento. O primeiro efetivamente cancela a reserva, enquanto o segundo demonstra o único caso possível de falha no cancelamento: a não existência da disciplina especificada.

#### 6. Exibição da grade de horários
Ao final da execução, o sistema imprime a grade de ocupação das salas, mostrando todas as reservas válidas realizadas.