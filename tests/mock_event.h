#ifndef MOCKEVENT_H
#define MOCKEVENT_H

#include <catch2/catch.hpp>
#include <trompeloeil.hpp>

#include <event.h>

class MockEvent : public rg::Event
{
public:
    MockEvent() : Event() {};

    MockEvent(
        int id,
        const std::string& l,
        const std::string& d,
        int v,
        std::vector<int> vols
    ) : rg::Event(id, l, d, v, vols) {};

    static constexpr bool trompeloeil_movable_mock = true;

    MAKE_CONST_MOCK1(eq, bool(const Event&), override);
    MAKE_CONST_MOCK0(get_id, int(), override);
};

#endif // MOCKEVENT_H
