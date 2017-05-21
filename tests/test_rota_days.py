import unittest
from datetime import date
from rota.rota_days import RotaDays

class TestRotaDays(unittest.TestCase):
    def setUp(self):
        self.rd = RotaDays()

    def test_find_weekends_1(self):
        expected = ['Saturday 31st December/Sunday 1st January',
                    'Saturday 7th/Sunday 8th January',
                    'Saturday 14th/Sunday 15th January',
                    'Saturday 21st/Sunday 22nd January',
                    'Saturday 28th/Sunday 29th January']

        self.assertEqual(self.rd.find_weekends(2017, 1, 1), expected)

    def test_format_weekend(self):
        Saturday = date(2016, 12, 31)
        Sunday = date(2017, 1, 1)
        expected = 'Saturday 31st December/Sunday 1st January'

        self.assertEqual(self.rd.format_weekend(Saturday, Sunday), expected)

if __name__ == '__main__':
    unittest.main()
