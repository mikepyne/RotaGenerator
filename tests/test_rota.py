import pytest
from unittest.mock import Mock
from rota.rota import Rota


@pytest.fixture()
def rota():
    return Rota()


@pytest.fixture()
def data():
    return {
            "needed": 2,
            "startfrom": 1,
            "readers": {
                1: {
                    "name": "Gabrielle Bedford",
                    "exclude": []
                },
                2: {
                    "name": "Ruth Burgess",
                    "exclude": []
                }
            }
        }


class TestRota_addMass(object):
    def test_addMass(self):
        m = Mock()
        r = Rota()
        r.add_mass(m)

        assert len(r.masses) == 1
        assert r.masses[0] == m
