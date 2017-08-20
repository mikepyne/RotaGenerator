import pytest
from unittest.mock import Mock
from spiders.loew import LiturgyOffice


@pytest.fixture()
def lo():
    return LiturgyOffice()


class TestMass_init(object):
    def test_build_url(self, lo):
        assert lo._build_url(2017, 7) == 'http://www.liturgyoffice.org.uk/Calendar/2017/Jul.shtml'

    def test_build_url_bad_month(self, lo):
        with pytest.raises(ValueError):
            lo._build_url(2017, 13) == ''

    def test_build_summary(self, lo):
        assert lo._build_summary(2017, 7) == 'Liturgical Calendar for July 2017'

    def test_build_summary_bad_month(self, lo):
        with pytest.raises(ValueError):
            lo._build_summary(2017, 13)
