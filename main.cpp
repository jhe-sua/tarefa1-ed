#include "ReservationSystem.hpp"
#include "ReservationRequest.hpp"

int main()
{   
    int capacities[3] = {30,50, 80};

    ReservationSystem system(3, capacities);
    ReservationRequest request("Calculo", "segunda", 7, 9, 29);
    ReservationRequest request2("Fundamentos", "segunda", 9, 10, 29);
    
    system.reserve(request2);
    system.reserve(request);
    system.printSchedule();
}