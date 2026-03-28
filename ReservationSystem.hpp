#ifndef RESERVATION_SYSTEM_HPP
#define RESERVATION_SYSTEM_HPP

#include "ReservationRequest.hpp"
#include <string>

using namespace std;

// Reserva ====================================================================
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
        
        //getters
        string getCourseName();
        string getWeekday();
        int getNumWeekDay();
        int getStartHour();
        int getEndHour();
        int getStudentCount();
};


// ArrReservaDinamico =========================================================
class ArrReservaDinamico
{
private:
    int capacidade;
    int tamanho;
    Reserva* dados;

public:
    ArrReservaDinamico(int capacidade);
    ArrReservaDinamico(const ArrReservaDinamico& other);
    ArrReservaDinamico& operator=(const ArrReservaDinamico& other);
    ~ArrReservaDinamico();
    void resize(int nova_capacidade);
    void append(Reserva value);
    void remove(int index);
    void sort();
    Reserva get(int index);
    int getTamanho();
};


// Semana =====================================================================
class Semana
{
    private: 
        bool semana[5][24];

    public:
        Semana();

        bool getHour(int i, int j);

        void setHour(int i, int j, bool value);

        bool horarioDisponivel(int dia_semana, int hora_inicio, int hora_fim);

        void preencherHorario(int dia_semana, int hora_inicio, int hora_fim, bool value);

        
};

// Sala========================================================================
class Sala
{   
    private:
        int cap_max;
        int index;
        ArrReservaDinamico arr_reservas = ArrReservaDinamico(14);
        Semana semana;

    public:
        Sala();
        Sala(int cap_max, int index);

        Reserva getReserva(int index); 
        bool reservar(Reserva reserva, int dia_semana, int inicio, int fim);
        bool remover(std::string course_name);

        int getCap_max(); 
        void setCap_max(int n); 

        void print();

         
};

// ReservationSystem ==========================================================
class ReservationSystem {

private:
    int room_count;
    int* room_capacities;
    Sala* salas;

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