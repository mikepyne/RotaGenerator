import pytest
from datetime import date
import calendar
from rota.rota_days import RotaDays


@pytest.fixture(scope="module")
def rd():
    return RotaDays()


class TestRotaDays(object):
    def test_format_weekend(self, rd):
        Saturday = date(2016, 12, 31)
        Sunday = date(2017, 1, 1)
        expected = 'Saturday 31st December/Sunday 1st January'
        assert rd.format_weekend(Saturday, Sunday) == expected

    def test_find_weekends_1(self, rd):
        expected = ['Saturday 31st December/Sunday 1st January',
                    'Saturday 7th/Sunday 8th January',
                    'Saturday 14th/Sunday 15th January',
                    'Saturday 21st/Sunday 22nd January',
                    'Saturday 28th/Sunday 29th January']

        assert rd.find_weekends(2017, 1, 1) == expected

    def test_find_weekends_2(self, rd):
        expected = ['Saturday 28th February/Sunday 1st March',
                    'Saturday 7th/Sunday 8th March',
                    'Saturday 14th/Sunday 15th March',
                    'Saturday 21st/Sunday 22nd March',
                    'Saturday 28th/Sunday 29th March',
                    'Saturday 4th/Sunday 5th April',
                    'Saturday 11th/Sunday 12th April',
                    'Saturday 18th/Sunday 19th April',
                    'Saturday 25th/Sunday 26th April',
                    'Saturday 2nd/Sunday 3rd May',
                    'Saturday 9th/Sunday 10th May',
                    'Saturday 16th/Sunday 17th May',
                    'Saturday 23rd/Sunday 24th May',
                    'Saturday 30th/Sunday 31st May']

        assert rd.find_weekends(2015, 3, 5) == expected

    def test_find_weekends_dec_feb(self, rd):
        # Liturgical year starts in December, so first rota period is Dec - Feb
        expected = ['Saturday 5th/Sunday 6th December',
                    'Saturday 12th/Sunday 13th December',
                    'Saturday 19th/Sunday 20th December',
                    'Saturday 26th/Sunday 27th December',
                    'Saturday 2nd/Sunday 3rd January',
                    'Saturday 9th/Sunday 10th January',
                    'Saturday 16th/Sunday 17th January',
                    'Saturday 23rd/Sunday 24th January',
                    'Saturday 30th/Sunday 31st January',
                    'Saturday 6th/Sunday 7th February',
                    'Saturday 13th/Sunday 14th February',
                    'Saturday 20th/Sunday 21st February',
                    'Saturday 27th/Sunday 28th February']

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
