# RotaGenerator

## Introduction

This is a tool to help me generate a rota for a group of readers.

Things that I want to do using this tool:

1. Generate a list of weekends in a given month (or months)
2. Identify the liturgical day for each weekend
3. Assign readers to a reading/mass
   1. Some readers are available for a specific mass
   2. Other readers are available for all masses
   3. Some readers may not be available for particular weekends
   4. Some masses may be special occasions and not require readers
4. Fill in some sort of template, using the above information

## Requirements

See requirements.txt for list of required packages.

Missing packages can be installed using PyPi.

## Testing

Unit tests are written using [PyTest](https://docs.pytest.org/en/latest/).

[Tox](https://tox.readthedocs.io/en/latest/) is used to manage the testing
environment and execute the unit tests.

To execute the tests:

    cd {project_dir}
    tox

## Links

The details for each Sunday in the rota period are retrieved from two places:

+ [Universalis](http://universalis.com/)
+ [Liturgy Office](www.liturgyoffice.org.uk/)

Both sites have calendars that detail the liturgical year for the UK:

+ [August 2017](http://www.liturgyoffice.org.uk/Calendar/2017/Aug.shtml)
+ [Current Year](http://universalis.com/calendar.htm)
  + A particular year can be selected by appending ``?year=yyyy`` to the URL, replacing ``yyyy`` with the desired year

