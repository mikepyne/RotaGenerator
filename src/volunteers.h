#ifndef VOLUNTEERS_H
#define VOLUNTEERS_H

#include "rotadata.h"

#include "volunteer.h"


static std::string_view volunteers_fname {"volunteers.txt"};

/// \class Volunteers
/// \brief Collection of Volunteer objects
class Volunteers : public RotaData<Volunteer>
{
public:
    Volunteers() = default;
};

#endif // VOLUNTEERS_H
