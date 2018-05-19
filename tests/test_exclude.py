import pytest
from datetime import date, datetime
from rota.exclude import ExcludeMixin, ExcludeError


class TestExclude_init():
    def test_init(self):
        em = ExcludeMixin([])
        assert em.exclude == []
        assert em.date_format == '%d/%m/%Y'

    good_exclude_data = [
        (['01/01/2018'], [date(2018, 1, 1)]),
        (['01/01/2018', '01/02/2018'], [date(2018, 1, 1), date(2018, 2, 1)])
    ]

    good_ids = [
        'single_date',
        'two_dates'
    ]

    @pytest.mark.parametrize("excludes, expected",
                             good_exclude_data,
                             ids=good_ids)
    def test_init_date(self, excludes, expected):
        em = ExcludeMixin(excludes)
        assert em.exclude == expected

    bad_exclude_data = [
        ['a'],
        ['40/01/2018'],
        ['01/13/2018'],
        ['']
    ]

    bad_exclude_ids = [
        'string',
        'invalid_day',
        'invalid_month',
        'empty_string'
    ]

    @pytest.mark.parametrize("data", bad_exclude_data, ids=bad_exclude_ids)
    def test_init_bad_exclude(self, data):
        with pytest.raises(
            ExcludeError,
            match='Bad value in excludes'
        ):
            em = ExcludeMixin(data)  # noqa: F841


class TestExclude_is_excluded():
    """Test the is_excluded method"""

    test_data = [
        ([], False),
        (['01/01/2018'], True),
        (['01/02/2018'], False)
    ]

    test_ids = [
        'no_exclude',
        'excluded',
        'not_excluded'
    ]

    @pytest.mark.parametrize("data, expected", test_data, ids=test_ids)
    def test_exclude(self, data, expected):
        em = ExcludeMixin(data)
        assert em.is_excluded(date(2018, 1, 1)) is expected

    def test_exclude_datetime(self):
        data = ['01/02/2018']
        em = ExcludeMixin(data)
        assert em.is_excluded(datetime(2018, 2, 1, 0, 0, 0)) is False


class TestExclude_as_strings():
    test_data = [
        (['01/01/2018', '02/02/2018'], ['01/01/2018', '02/02/2018']),
        ([], []),
        (['01/01/2018'], ['01/01/2018'])
    ]

    test_ids = [
        'multiple',
        'empty',
        'single',
    ]

    @pytest.mark.parametrize("data, expected", test_data, ids=test_ids)
    def test_exclude_strings(self, data, expected):
        em = ExcludeMixin(data)
        assert em.excludes_as_string() == expected


class TestExclude_add():
    def test_exclude_add(self):
        expected = [date(2018, 3, 3)]
        em = ExcludeMixin([])
        em.add_exclude('03/03/2018')
        assert em.exclude == expected
