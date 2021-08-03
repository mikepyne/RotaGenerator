#ifndef MOCK_ROTA_H
#define MOCK_ROTA_H

#include <catch2/catch.hpp>
#include <trompeloeil.hpp>

#include <rota.h>

class MockRota : public rg::Rota
{
public:
    MockRota() : Rota() {};

    MockRota(int                     i,
             const std::string&      l,
             const std::string&      d,
             const std::vector<int>& e) :
        rg::Rota(i, l, d, e) {};

    static constexpr bool trompeloeil_movable_mock = true;

    MAKE_CONST_MOCK1(eq, bool(const Rota&), override);
    MAKE_CONST_MOCK0(get_id, int(), override);
};

#endif    // MOCK_ROTA_H
