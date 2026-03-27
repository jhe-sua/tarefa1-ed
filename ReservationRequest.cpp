#include <iostream>

class ReservationRequest {

private:
    std::string course_name;
    std::string weekday;
    int start_hour;
    int end_hour;
    int student_count;

public:
    //construtor
    ReservationRequest(
        std::string course_name,
        std::string weekday,
        int start_hour,
        int end_hour,
        int student_count
    );
    //destrutor
    ~ReservationRequest();

    int getStartHour()
    {
	return 0;
    }
    int getEndHour();
    std::string getCourseName();
    std::string getWeekday();
    int getStudentCount();
};
