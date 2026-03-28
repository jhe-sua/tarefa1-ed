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

string Reserva::getCourseName()
{
    return this->course_name;
}

string Reserva::getWeekday()
{
    return this->weekday;
}
int Reserva::getNumWeekDay()
{
    if (this->weekday == "segunda") return 0;
    if (this->weekday == "terca") return 1;
    if (this->weekday == "quarta") return 2;
    if (this->weekday == "quinta") return 3;
    if (this->weekday == "sexta") return 4;

    return -1;
}

int Reserva::getStartHour()
{
    return this->start_hour;
}

int Reserva::getEndHour()
{
    return this->end_hour;
}

int Reserva::getStudentCount()
{
    return this->student_count;
}



// Implementando ArrReservaDinamico ===========================================

//construtor
ArrReservaDinamico::ArrReservaDinamico(int capacidade)
{
    this->dados = new Reserva[capacidade];
    this->capacidade = capacidade;
    this->tamanho = 0;
}

//destrutor
ArrReservaDinamico::~ArrReservaDinamico()
{
    delete[] this->dados;
}

//construtor de copia
ArrReservaDinamico::ArrReservaDinamico(const ArrReservaDinamico& other)
{
    capacidade = other.capacidade;
    tamanho = other.tamanho;
    dados = new Reserva[capacidade];

    for (int i = 0; i < tamanho; i++) {
        dados[i] = other.dados[i];
    }
}

//operador de atribuicao
ArrReservaDinamico& ArrReservaDinamico::operator=(const ArrReservaDinamico& other) {
    if (this == &other) return *this;

    delete[] dados;

    capacidade = other.capacidade;
    tamanho = other.tamanho;
    dados = new Reserva[capacidade];

    for (int i = 0; i < tamanho; i++) {
        dados[i] = other.dados[i];
    }

    return *this;
}


void ArrReservaDinamico::resize(int nova_capacidade)
{
    Reserva* novos_dados = new Reserva[nova_capacidade];
    for (int i = 0; i < this->tamanho; i++)
    {
        novos_dados[i] = this->dados[i];
    }
    delete[] this->dados;
    this->dados = novos_dados;
    this->capacidade = nova_capacidade;
}

void ArrReservaDinamico::append(Reserva value)
{
    if(this->capacidade == this->tamanho){
    resize(2*this->capacidade);
    }

    this->dados[this->tamanho] = value;
    this->tamanho++;
}

void ArrReservaDinamico::remove(int index)
{
    for (int i = index; i < this->tamanho - 1; i ++)
    {
        this->dados[i] = this->dados[i+1];
    }
    this->dados[this->tamanho -1] = Reserva();
    this->tamanho--;
}

void ArrReservaDinamico::sort()
{
    int minHora = 0, maxhora = 23;
    int range = maxhora - minHora + 1;
    
    int count[range] = {0};
    Reserva output[this->tamanho];

    // Calculamos a frequencia
    for(int i = 0; i < this->tamanho; i++)
    {
        count[this->get(i).getStartHour() - minHora]++;
    }

    // Calcular distribuição acumulada
    for(int i = 1; i < this->tamanho; i++)
    {
        count[i] += count[i-1];
    }

    // Com a frequencia e a dristribuicao acumulada organizamos
    for(int i = this->tamanho-1; i>= 0; i--)
    {
        int hora = this->dados[i].getStartHour() - minHora;
        int pos = count[hora] - 1;
        output[pos] = this->dados[i];
        count[hora]--;
    }

    for(int i = 0; i < this->tamanho; i++)
    {
        this->dados[i] = output[i];
    }
}

Reserva ArrReservaDinamico::get(int index)
{
    return this->dados[index];
};

int ArrReservaDinamico::getTamanho()
{
    return this->tamanho;
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

void Semana::preencherHorario(int dia_semana, int hora_inicio, int hora_fim, bool value)
{
    for (int j = hora_inicio + 1; j <= hora_fim; j++)
    {
        this->setHour(dia_semana, j, value);
    }
}


// Implementando sala =========================================================
Sala::Sala() {}

Sala::Sala(int cap_max, int index)
: cap_max(cap_max), index(index), arr_reservas(14)
{}

Reserva Sala::getReserva(int index)
{   
    return this->arr_reservas.get(index);
} 

bool Sala::reservar(Reserva reserva, int dia_semana, int inicio, int fim)
{
    // verifica capacidade
    if (this->cap_max < reserva.getStudentCount()) {
        return false;
    }

    // verifica disponibilidade
    if (!this->semana.horarioDisponivel(dia_semana, inicio, fim)) {
        return false;
    }

    // faz a reserva
    this->semana.preencherHorario(dia_semana, inicio, fim, true);
    this->arr_reservas.append(reserva);

    return true;
}

bool Sala::remover(std::string course_name)
{
    int tamanho = this->arr_reservas.getTamanho();
    for(int i = 0; i < tamanho; i ++)
    {   
        Reserva reserva = this->arr_reservas.get(i);
        if (reserva.getCourseName() == course_name)
        {   
            int dia_semana = reserva.getNumWeekDay();
            int inico = reserva.getStartHour();
            int final = reserva.getEndHour();

            this->arr_reservas.remove(i);
            this->semana.preencherHorario(dia_semana, inico, final, false);

            return true;
        }
    }
    return false;
}

int Sala::getCap_max()
{
    return this->cap_max;
}

void Sala::setCap_max(int n)
{
    this->cap_max = n;
}

void Sala::print()
{   
    this->arr_reservas.sort();
    string dias_da_semana[] = {"segunda", "terca", "quarta", "quinta", "sexta", "sabado", "domingo"};
    bool dia_da_semana_printado[7] = {false};

    cout << "Room " << this->index << endl;
    for (int i = 0; i < this->arr_reservas.getTamanho(); i++)
    {   
        for (int j = 0; j < 7; j++)
        {
            if (this->arr_reservas.get(i).getWeekday() == dias_da_semana[j])
            {
                if (!dia_da_semana_printado[j])
                {
                    cout << dias_da_semana[j] << ":"
                }
            }
        }
        Reserva reserva =this->arr_reservas.get(i);
        cout << reserva.getWeekday() << ":" << endl;
        cout << reserva.getStartHour() << "h~" << reserva.getEndHour() << "h: "<< reserva.getCourseName() << endl;

    }
}

        
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
        this->salas[i] = Sala(room_capacities[i], i);
    };
};


ReservationSystem:: ~ReservationSystem()
{
    delete[] room_capacities;
    delete[] salas;
};

bool ReservationSystem::reserve(ReservationRequest request)
{   
    Reserva reserva = Reserva(request);

    int dia_semana = reserva.getNumWeekDay();
    int inicio = reserva.getStartHour();
    int fim = reserva.getEndHour();

    // en cada sala
    for(int i = 0; i < this->room_count; i++)
    {   
        // verifica a disponibilidade e faz a reserva
        if (this->salas[i].reservar(reserva, dia_semana, inicio, fim))
        {
            return true; // conseguiu reservar em alguma sala
        }
    }
    return false; // nenhuma sala conseguiu
}


bool ReservationSystem::cancel(std::string course_name)
{
    for(int i = 0; i < this->room_count; i ++)
    {
        bool sucesso = this->salas[i].remover(course_name);
        if (sucesso)
        {
            return true;
        }
    }
    return false;
}

void ReservationSystem::printSchedule()
{
    for(int i = 0; i < this->room_count; i++)
    {
        this->salas[i].print();
    }
};