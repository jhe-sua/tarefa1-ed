#include <iostream>
#include "ReservationRequest.hpp"
#include "ReservationSystem.hpp"

// Implementando reserva ======================================================
Reserva::Reserva()
{
    this->course_name = "";
    this->weekday = "";
    this->end_hour = 0;
    this->start_hour = 0;
    this->student_count = 0;
}

Reserva::Reserva(ReservationRequest request)
{
    this->course_name = request.getCourseName();
    this->end_hour = request.getEndHour();
    this->start_hour = request.getStartHour();
    this->student_count = request.getStudentCount();
    this->weekday = request.getWeekday();
}


// Implementando semana =======================================================
Semana::Semana()
{
    for (int i = 0; i < 5; i ++)
    {
        for(int j = 0; j < 24; j++)
        {
            this->semana[i][j] = false;
        };
    };
};

bool Semana::getHour(int i, int j)
{   
    return this->semana[i][j];
}

void Semana::setHour(int i, int j, bool value)
{
    this->semana[i][j] = value;
}

bool Semana::horarioDisponivel(int dia_semana, int hora_inicio, int hora_fim)
{
    for (int j = hora_inicio + 1; j <= hora_fim; j++)
        {   
            bool disponivel;
            disponivel = this->getHour(dia_semana, j);

            if(disponivel)
            {
                return false;
            }
        }
    return true;
}

void Semana::preencherHorario(int dia_semana, int hora_inicio, int hora_fim)
{
    for (int j = hora_inicio + 1; j <= hora_fim; j++)
    {
        this->setHour(dia_semana, j, true);
    }
}


// Implementando sala =========================================================


        
// implementando ReservationSystem ============================================

/**
 * @brief Construct a new Reservation System object
 * 
 * @param room_count numero total de salas disponiveis
 * @param room_capacities um array contendo a capacidade maxima de cada sala
 */
ReservationSystem::ReservationSystem(int room_count, int* room_capacities)
{
    this->room_count = room_count;
    this->room_capacities = new int[room_count];
    this->salas = new Sala[room_count];

    for (int i = 0; i < room_count; i++)
    {
        this->room_capacities[i] = room_capacities[i];
        this->salas[i].cap_max = room_capacities[i];
    };
};


ReservationSystem:: ~ReservationSystem()
{
    delete[] room_capacities;
    delete[] salas;
};


int ReservationSystem:: dia_para_index(std::string weekday) {
    if (weekday == "segunda") return 0;
    if (weekday == "terca") return 1;
    if (weekday == "quarta") return 2;
    if (weekday == "quinta") return 3;
    if (weekday == "sexta") return 4;

    return -1;
}

bool ReservationSystem::reserve(ReservationRequest request)
{   
    // en cada sala
    for(int i = 0; i < this->room_count; i++)
    {   
        // olha se a capacidade da sala é suficiente, se não for pula pra proxima
        if (this->salas[i].cap_max < request.getStudentCount())
        {
            continue;
        } else
        // se for suficiente olha se tem horarios disponiveis
        {   
            int dia_semana = dia_para_index(request.getWeekday());
            int inicio = request.getStartHour();
            int fim = request.getEndHour();
            
            // passa por todos os horarios do dia da semana escolhido
            bool disponivel;
            disponivel = this->salas[i].semana.horarioDisponivel(dia_semana, inicio, fim);

            if (!disponivel)
            {
                return false;
            }

            // se sim estiver disponivel faz a reserva
            int index = this->salas[i].n_reservas;
            
            this->salas[i].semana.preencherHorario(dia_semana, inicio, fim);
            this->salas[i].reservas[index] = Reserva(request);
            
            this->salas[i].n_reservas++;
            
            
    }
    return false;
}
}

bool cancel(std::string course_name);

void printSchedule();