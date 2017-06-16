import pytest
from unittest.mock import Mock
from rota.mass import Mass, MassError


@pytest.fixture()
def mass():
    return Mass('saturday', 2, 1)


class TestMass(object):
    def test_str(self, mass):
        assert str(mass) == 'saturday'

    def test_repr(self, mass):
        assert repr(mass) == "Mass('saturday', 2, 1, None, None)"

    def test_repr(self):
        mass = Mass('saturday', 2, 1, 'A', 'B')
        assert repr(mass) == "Mass('saturday', 2, 1, 'A', 'B')"

    def test_get_reader_empty(self, mass):
        with pytest.raises(
            MassError,
            match='No reader for ID: 1'
        ):
            mass.get_reader(1)

    def test_get_reader_one_reader(self, mass):
        mass.readers[1] = 'Reader'
        assert mass.get_reader(1) == 'Reader'

    def test_add_reader(self, mass):
        tr = mocker().Mock()
        tr.id = 1
        tr.name = 'A Reader'
        mass.add_reader(tr)
        assert mass.readers[1] == tr
