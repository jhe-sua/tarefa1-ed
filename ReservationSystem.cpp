#include <iostream>
#include "ReservationRequest.hpp"

struct Reserva
{
    std::string course_name;
    std::string weekday;
    int start_hour;
    int end_hour;
    int student_count;
};

class Semana
{
    private: 
        bool semana[5][15];

    public:
        Semana()
        {
            for (int i = 0; i < 15; i ++)
            {
                for(int j = 0; j < 15; j++)
                {
                    this->semana[i][j] = false;
                };
            };
        };
        
};

struct Sala
{
    Reserva* reservas;
    int cap_max;
};

class ReservationSystem {

private:
    int room_count;
    int* room_capacities;

    // Estruturas internas escolhidas pelos alunos
    // para armazenar e gerenciar as reservas, os horários, ...

public:
    /**
     * @brief Construct a new Reservation System object
     * 
     * @param room_count numero total de salas disponiveis
     * @param room_capacities um array contendo a capacidade maxima de cada sala
     */
    ReservationSystem(int room_count, int* room_capacities);
    
    ~ReservationSystem();

    bool reserve(ReservationRequest request);
    bool cancel(std::string course_name);

    void printSchedule();

    // Outros métodos utilitários necessários
    // para auxiliar nas funções requisitadas
};