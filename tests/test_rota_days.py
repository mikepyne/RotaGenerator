import unittest
from rota.rota_days import RotaDays

class TestRotaDays(unittest.TestCase):
    def setUp(self):
        self.rd = RotaDays()

    def test_get_weekends_1(self):
        self.rd.get_weekends(2017, 1, 3)

if __name__ == '__main__':
    unittest.main()
