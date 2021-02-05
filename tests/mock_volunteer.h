#ifndef MOCKVOLUNTEER_H
#define MOCKVOLUNTEER_H

#include <catch2/catch.hpp>
#include <trompeloeil.hpp>

#include <volunteer.h>

class MockVolunteer : public Volunteer
{
public:
    MockVolunteer() : Volunteer() {};

    MockVolunteer(
        int id,
        const std::string& f,
        const std::string& l,
        const std::string& h,
        const std::string& m,
        const std::string& e
    ) : Volunteer(id, f, l, h, m, e) {};

    static constexpr bool trompeloeil_movable_mock = true;

    MAKE_CONST_MOCK1(eq, bool(const Volunteer&), override);
    MAKE_CONST_MOCK0(get_id, int(), override);
};

#endif // MOCKVOLUNTEER_H
