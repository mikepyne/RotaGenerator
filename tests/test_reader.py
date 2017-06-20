import pytest
from rota.reader import Reader, ReaderError


class TestReader_init():
    """Test the init method of the Reader class"""

    init_data = [
        ({'name': 'Gabrielle'}),
        ({'name': 'Gabrielle', 'names': ['Burt', 'Ernie']}),
        ({'names': ['Burt', 'Ernie']})
    ]

    init_ids = [
        'name_only',
        'name_and_names',
        'names_only'
    ]

    @pytest.mark.parametrize("data", init_data, ids=init_ids)
    def test_init(self, data):
        reader = Reader(1, data)

    def test_init_neither_name_or_names(self):
        data = {}
        with pytest.raises(
            ReaderError,
            match='Reader must have a name and/or names; ID: 1'
        ):
            reader = Reader(1, data)


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
        )
    ]

    test_ids = [
        'all',
        'names_only',
        'no_exlude'
    ]

    @pytest.mark.parametrize("data, expected", test_data, ids=test_ids)
    def test_repr(sel, data, expected):
        reader = Reader(1, data)
        assert repr(reader) == expected

    def test_repr_bad_id(self):
        data = {'name': 'Gabrielle'}
        reader = Reader('A', data)
        with pytest.raises(ValueError):
            repr(reader)
