import pytest
from rota.reader import Reader, ReaderError


class TestReader(object):
    def test_init_name(self):
        reader = Reader(1, 'Gabrielle', [], [])

    def test_init_name_and_names(self):
        reader = Reader(1, 'Gabrielle', ['Burt', 'Ernie'])

    def test_init_names(self):
        reader = Reader(1, names=['Burt', 'Ernie'], exclude=[])

    def test_init_neither_name_or_names(self):
        with pytest.raises(ReaderError):
            Reader(1)

    def test_str_name(self):
        reader = Reader(1, 'Gabrielle', [], [])
        assert str(reader) == '1 - Gabrielle'

    def test_str_names(self):
        reader = Reader(1, names=['Burt', 'Ernie'])
        assert str(reader) == "1 - ['Burt', 'Ernie']"

    def test_str_name_and_names(self):
        reader = Reader(1, 'Gabrielle', ['Burt', 'Ernie'])
        assert str(reader) == '1 - Gabrielle'

    def test_repr(self):
        expected = "Reader(1, 'Gabrielle', ['Burt', 'Ernie'], ['01/01/2001'])"
        reader = Reader(1, 'Gabrielle', ['Burt', 'Ernie'], ['01/01/2001'])
        assert repr(reader) == expected

    def test_repr_bad_id(self):
        reader = Reader('A', 'Gabrielle', [], [])
        with pytest.raises(ValueError):
            repr(reader)
