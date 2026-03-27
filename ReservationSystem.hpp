#ifndef RESERVATION_SYSTEM_HPP
#define RESERVATION_SYSTEM_HPP

#include "ReservationRequest.hpp"
#include <string>

using namespace std;


class Reserva
{
    private:
        std::string course_name;
        std::string weekday;
        int start_hour;
        int end_hour;
        int student_count;
    
    public:
        Reserva();
        Reserva(ReservationRequest request);
};

class Semana
{
    private: 
        bool semana[5][24];

    public:
        Semana();

        bool getHour(int i, int j);

        void setHour(int i, int j, bool value);

        bool horarioDisponivel(int dia_semana, int hora_inicio, int hora_fim);

        void preencherHorario(int dia_semana, int hora_inicio, int hora_fim);
        
};

struct Sala
{   
    int cap_max;
    int n_reservas = 0;
    int nmax_reservas = 14;
    Reserva reservas[14];
    Semana semana;
};

class ReservationSystem {

private:
    int room_count;
    int* room_capacities;
    Sala* salas;

    int dia_para_index(string weekday);

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

#endif