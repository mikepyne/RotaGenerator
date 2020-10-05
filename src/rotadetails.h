#ifndef ROTADETAILS_H
#define ROTADETAILS_H


class RotaDetails
{
public:
    RotaDetails() = default;

    void addVolunteer(
        int id
    );

    void addEvent(
        int id
    );

private:
    int id {0};
    // Events events;
    // Volunteers volunteers;
};

#endif // ROTADETAILS_H
