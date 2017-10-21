import pytest
from datetime import date
import calendar
from rota.rota_days import RotaDays


@pytest.fixture(scope="module")
def rd():
    return RotaDays()


class TestRotaDays(object):
    def test_format_weekend(self, rd):
        Sunday = date(2017, 1, 1)
        expected = 'Saturday 31st December/Sunday 1st January'
        assert rd.format_weekend(Sunday) == expected

    def test_format_weekend(self, rd):
        weekends = [date(2017, 1, 1),
                    date(2017, 1, 8),
                    date(2017, 1, 15),
                    date(2017, 1, 22),
                    date(2017, 1, 29)]

        expected = ['Saturday 31st December/Sunday 1st January',
                    'Saturday 7th/Sunday 8th January',
                    'Saturday 14th/Sunday 15th January',
                    'Saturday 21st/Sunday 22nd January',
                    'Saturday 28th/Sunday 29th January']

        assert rd.format_weekends(weekends) == expected

    def test_find_weekends_1(self, rd):
        expected = [date(2017, 1, 1),
                    date(2017, 1, 8),
                    date(2017, 1, 15),
                    date(2017, 1, 22),
                    date(2017, 1, 29)]

        assert rd.find_weekends(2017, 1, 1) == expected

    def test_find_weekends_2(self, rd):
        expected = [date(2015, 3, 1),
                    date(2015, 3, 8),
                    date(2015, 3, 15),
                    date(2015, 3, 22),
                    date(2015, 3, 29),
                    date(2015, 4, 5),
                    date(2015, 4, 12),
                    date(2015, 4, 19),
                    date(2015, 4, 26),
                    date(2015, 5, 3),
                    date(2015, 5, 10),
                    date(2015, 5, 17),
                    date(2015, 5, 24),
                    date(2015, 5, 31)]

        assert rd.find_weekends(2015, 3, 5) == expected

    def test_find_weekends_dec_feb(self, rd):
        # Liturgical year starts in December, so first rota period is Dec - Feb
        expected = [date(2015, 12, 6),
                    date(2015, 12, 13),
                    date(2015, 12, 20),
                    date(2015, 12, 27),
                    date(2016, 1, 3),
                    date(2016, 1, 10),
                    date(2016, 1, 17),
                    date(2016, 1, 24),
                    date(2016, 1, 31),
                    date(2016, 2, 7),
                    date(2016, 2, 14),
                    date(2016, 2, 21),
                    date(2016, 2, 28)]

        assert rd.find_weekends(2015, 12, 2, 2016) == expected

    def test_find_weekends_bad_params(self, rd):
        expected = []
        assert rd.find_weekends(2015, 5, 3) == expected

    def test_find_weekends_bad_end_month(self, rd):
        expected = []
        with pytest.raises(calendar.IllegalMonthError):
            rd.find_weekends(2015, 5, 2017)


if __name__ == '__main__':
    unittest.main()
