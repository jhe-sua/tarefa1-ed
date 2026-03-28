#include "ReservationSystem.hpp"
#include "ReservationRequest.hpp"
#include <iostream>

using namespace std;

int main()
{   
    int capacities[3] = {30,50, 80};

    ReservationSystem system(3, capacities);
    ReservationRequest request("Calculo", "segunda", 9, 10, 29);
    ReservationRequest request2("Fundamentos", "segunda", 9, 10, 29);
    ReservationRequest request3("GA", "segunda", 9, 10, 29);
    ReservationRequest request4("MD", "segunda", 10, 11, 29);
    ReservationRequest request5("PEPE", "segunda", 9, 10, 29);
    ReservationRequest request6("PEPE", "terca", 9, 10, 29);
    
    system.reserve(request);
    system.reserve(request3);
    system.reserve(request2);
    system.reserve(request4);
    system.reserve(request5);
    system.reserve(request6);
    system.printSchedule();
}