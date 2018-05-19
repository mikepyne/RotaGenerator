import pytest
from datetime import date, datetime
from rota.reader import Reader, ReaderError


class TestReader_init():
    """Test the init method of the Reader class"""

    init_data = [
        ({'name': 'Gabrielle'}),
        ({'name': 'Gabrielle', 'names': ['Burt', 'Ernie']}),
        ({'names': ['Burt', 'Ernie']}),
        ({'name': 'Alfred', 'exclude': []}),
        ({'name': 'Jill', 'exclude': ['02/03/2018']}),
        ({'name': 'Jill', 'exclude': ['02/03/2018', '03/04/2018']}),
    ]

    init_ids = [
        'name_only',
        'name_and_names',
        'names_only',
        'name_empty_exclude',
        'name_valid_exclude',
        'name_valid_multi_excludes',
    ]

    @pytest.mark.parametrize("data", init_data, ids=init_ids)
    def test_init(self, data):
        # Check no exceptions are thrown
        reader = Reader(1, data)  # noqa: F841

    def test_init_neither_name_or_names(self):
        data = {}
        with pytest.raises(
            ReaderError,
            match='Reader must have a name and/or names; ID: 1'
        ):
            reader = Reader(1, data)  # noqa: F841

    def test_init_names(self):
        data = {'names': ['Alf', '']}
        with pytest.raises(
            ReaderError,
            match='Empty name in names; ID: 1'
        ):
            reader = Reader(1, data)  # noqa: F841

    def test_bad_exclude(self):
        data = {
            'name': 'Jerome',
            'exclude': ['']
        }

        with pytest.raises(
            ReaderError,
            match='Bad value in excludes; ID: 1'
        ):
            reader = Reader(1, data)  # noqa: F841


class TestReader_str():
    """Test the str method of the Reader class"""

    test_data = [
        ({'name': 'Gabrielle'}, '1 - Gabrielle'),
        ({'names': ['Burt', 'Ernie']}, "1 - ['Burt', 'Ernie']"),
        ({'name': 'Gabrielle', 'names': ['Burt', 'Ernie']}, '1 - Gabrielle')
    ]

    test_ids = [
        'name_only',
        'names_only',
        'name_and_names'
    ]

    @pytest.mark.parametrize("data, expected", test_data, ids=test_ids)
    def test_str(self, data, expected):
        reader = Reader(1, data)
        assert str(reader) == expected


class TestReader_repr():
    """Test the repr method of the Reader class"""

    test_data = [
        (
            {
                'name': 'Gabrielle',
                'names': ['Burt', 'Ernie'],
                'exclude': ['01/01/2001']
            },
            "Reader(1, 'Gabrielle', ['Burt', 'Ernie'], ['01/01/2001'])"
        ),
        (
            {
                'name': 'Harry',
                'exclude': ['01/01/2001']
            },
            "Reader(1, 'Harry', [], ['01/01/2001'])"
        ),
        (
            {
                'names': ['Burt', 'Ernie'],
                'exclude': ['01/01/2001']
            },
            "Reader(1, '', ['Burt', 'Ernie'], ['01/01/2001'])"
        ),
        (
            {
                'name': 'Gabrielle',
                'names': ['Burt', 'Ernie']
            },
            "Reader(1, 'Gabrielle', ['Burt', 'Ernie'], [])"
        ),
        (
            {
                'name': 'Jennifer',
                'exclude': ['01/02/2018', '02/03/2018']
            },
            "Reader(1, 'Jennifer', [], ['01/02/2018', '02/03/2018'])"
        ),
    ]

    test_ids = [
        'all',
        'no_names',
        'names_only',
        'no_exclude',
        'multiple_excludes',
    ]

    @pytest.mark.parametrize("data, expected", test_data, ids=test_ids)
    def test_repr(self, data, expected):
        reader = Reader(1, data)
        assert repr(reader) == expected

    def test_repr_bad_id(self):
        data = {'name': 'Gabrielle'}
        reader = Reader('A', data)
        with pytest.raises(ValueError):
            repr(reader)


class TestReader_names():
    """Test the names method"""

    test_data = [
        (
            {
                'name': 'Gabrielle',
            },
            2,
            'Gabrielle'
        ),
        (
            {
                'name': 'Gabrielle',
                'names': ['Albert', 'Bill']
            },
            2,
            'Gabrielle'
        ),
        (
            {
                'name': 'Gabrielle',
                'names': ['Jane', 'Jill']
            },
            1,
            'Gabrielle'
        ),
        (
            {
                'name': 'Surname',
                'names': ['Albert', 'Bill']
            },
            3,
            'Albert, Bill'
        )
    ]

    test_ids = [
        'fewer_no_names',
        'same',
        'more',
        'fewer_names'
    ]

    @pytest.mark.parametrize("data, slots, expected", test_data, ids=test_ids)
    def test_names(self, data, slots, expected):
        reader = Reader(1, data)
        assert reader.get_name(slots) == expected


class TestReader_exclude():
    '''Test the exclude method'''

    test_data = [
        (
            {
                'name': 'Gabrielle'
            },
            False
        ),
        (
            {
                'name': 'Albert',
                'exclude': []
            },
            False
        ),
        (
            {
                'name': 'Bill',
                'exclude': ['01/01/2018']
            },
            True
        ),
        (
            {
                'name': 'Sophia',
                'exclude': ['01/02/2018']
            },
            False
        )
    ]

    test_ids = [
        'no_exclude',
        'empty_exclude',
        'excluded',
        'not_excluded'
    ]

    @pytest.mark.parametrize("data, expected", test_data, ids=test_ids)
    def test_exclude(self, data, expected):
        reader = Reader(1, data)
        assert reader.is_excluded(date(2018, 1, 1)) is expected

    def test_exclude_datetime(self):
        data = {
            'name': 'Joffrey',
            'exclude': ['01/02/2018']
        }
        reader = Reader(1, data)
        assert reader.is_excluded(datetime(2018, 2, 1, 0, 0, 0)) is False
