#include "ReservationSystem.hpp"
#include "ReservationRequest.hpp"
#include <iostream>

using namespace std;

int main()
{   
    int capacities[3] = {30,50, 80};

    // criação do sistema
    ReservationSystem system(3, capacities);

    // Criação dos requests
    ReservationRequest request0("Estrutura de dados", "segunda", 9, 11, 79);
    ReservationRequest request1("Calculo em uma Variavel", "segunda", 7, 9, 29);
    ReservationRequest request2("Fundamentos", "segunda", 7, 9, 29);
    ReservationRequest request3("GA", "segunda", 7, 9, 29);
    ReservationRequest request4("MD", "segunda", 7, 9, 29);
    ReservationRequest request5("ALN", "quarta", 11, 13, 90);
    ReservationRequest request6("Oficina de Teatro", "quarta", 6, 7, 12);
    
    // reservas bem-sucedidas
    bool r0 = system.reserve(request0);
    bool r1 = system.reserve(request1);
    bool r2 = system.reserve(request2);
    bool r3 = system.reserve(request3);

    cout << r0 << ", "  << r1 << ", " << r2 << ", " << r3 << endl;

    // reservas malsucedidas
    bool r4 = system.reserve(request4); //Conflito de horários
    bool r5 = system.reserve(request5); //Além da capacidade
    bool r6 = system.reserve(request6); // Fora do horário de funcionamento

    cout << r4 << "," << r5 << ","<< r6 << endl;

    // cancelamentos
    bool c1 = system.cancel("Fundamentos"); //com sucesso
    bool c2 = system.cancel("Calculo em Varias Variaveis"); //sem sucesso

    cout << c1 << ", " << c2 << endl;

    // exibição de grade
    system.printSchedule();
}