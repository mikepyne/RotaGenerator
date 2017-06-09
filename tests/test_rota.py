import pytest
from rota.rota import Rota

@pytest.fixture()
def rota():
    return Rota()


class TestRota(object):
    @pytest.mark.skip(reason="Not reader yet")
    def test_assign_readers(self, rota):
        data = {
            "needed": 2,
            "startfrom": 1,
            "readers": {
                "1": {
                    "name": "Gabrielle Bedford",
                    "exclude": []
                },
                "2": {
                    "name": "Ruth Burgess",
                    "exclude": []
                }
            }
        }
        rota.assign_readers(1, data)
