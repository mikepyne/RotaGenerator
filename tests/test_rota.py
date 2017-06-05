import pytest
from rota.rota import Rota

@pytest.fixture()
def rota():
    return Rota()


class TestRota(object):
    def test_assign_readers(self, rota):
        rota.assign_readers(1, {})
