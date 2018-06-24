import pytest
from unittest.mock import MagicMock, patch
from rota.mass import Mass, MassError
from rota.reader import Reader
# from rota.exclude import ExcludeError


@pytest.fixture()
def mass():
    return Mass(
        'saturday',
        {
            'needed': 2,
            'startfrom': 1,
            'exclude': [],
            'readers': {}
        }
    )


class TestMass_init(object):
    init_error_data = [
        (
            '',
            {
                'needed': 2,
                'startfrom': 1,
                'exclude': [],
                'readers': {}
            },
            'Bad label'
        ),
        (
            'saturday',
            {
                'needed': 2,
                'exclude': [],
                'readers': {}
            },
            "Required key is missing ('startfrom'); Label: saturday"
        ),
        (
            'saturday',
            {
                'startfrom': 1,
                'exclude': [],
                'readers': {}
            },
            "Required key is missing ('needed'); Label: saturday"
        ),
        (
            'saturday',
            {
                'needed': 'B',
                'startfrom': 1,
                'exclude': [],
                'readers': {}
            },
            "'needed' is invalid (B); Label: saturday"
        ),
        (
            'saturday',
            {
                'needed': 2,
                'startfrom': 'A',
                'exclude': [],
                'readers': {}
            },
            "'startfrom' is invalid (A); Label: saturday"
        ),
    ]

    init_error_ids = [
        'no_label',
        'no_startfrom',
        'no_needed',
        'bad_needed',
        'bad_startfrom'
    ]

    init_data = [
        (
            'saturday',
            {
                'needed': 2,
                'startfrom': 1,
                'exclude': [],
                'readers': {}
            }
        ),
        (
            'saturday',
            {
                'needed': 2,
                'startfrom': 1,
                'readers': {}
            }
        )
    ]

    init_ids = [
        'basic',
        'no_exclude'
    ]

    @pytest.mark.parametrize("label, data, expected", init_error_data,
                             ids=init_error_ids)
    def test_init_errors(self, label, data, expected):
        with pytest.raises(MassError, message=expected):
            m = Mass(label, data)   # noqa: F841

    @pytest.mark.parametrize("label, data", init_data, ids=init_ids)
    def test_init(self, label, data):
        m = Mass(label, data)   # noqa: F841


class TestMass_repr:
    repr_data = [
        # Test data for the __repr__ method
        # Each set contains the label, data, and expected output
        (
            'saturday',
            {
                'needed': 2,
                'startfrom': 1,
                'exclude': [],
                'readers': {}
            },
            "Mass('saturday', 2, 1, [], {})"
        ),
        (
            'saturday',
            {
                'needed': 2,
                'startfrom': 1,
                'exclude': ['01/01/2018'],
                'readers':{
                    1: {
                        "name": "Gabrielle Bedford",
                        "exclude": []
                    }
                }
            },
            # Long string split over two lines
            "Mass('saturday', 2, 1, ['01/01/2018'], "
            "{1: Reader(1, 'Gabrielle Bedford', [], [])})"
        )
    ]

    repr_ids = [
        'basic',
        'all'
    ]

    @pytest.mark.parametrize("label, data, expected", repr_data, ids=repr_ids)
    def test_repr(self, label, data, expected):
        m = Mass(label, data)
        assert repr(m) == expected


class TestMass:
    def test_str(self, mass):
        assert str(mass) == 'saturday'

    def test_get_reader(self, mass):
        with pytest.raises(
            MassError,
            match='No reader for ID: 1'
        ):
            mass.get_reader(1)

    def test_get_reader_one_reader(self, mass):
        mass.readers[1] = 'Reader'
        assert mass.get_reader(1) == 'Reader'

    def test_add_reader(self, mass):
        tr = MagicMock()
        tr.id = 1
        tr.name = 'A Reader'
        mass.add_reader(tr)
        assert mass.readers[1] == tr

    def test_get_readers(self, mass):
        r1 = MagicMock()
        r1.id = 1
        r1.name = 'Reader 1'
        r2 = MagicMock()
        r2.id = 2
        r2.name = 'Reader 2'

        mass.add_reader(r1)
        mass.add_reader(r2)

        assert mass.get_reader() == r1
        assert mass.get_reader(2) == r2
        assert mass.get_reader(1) == r1


class TestMass_allocate:
    def test_allocate_2_slots_2_readers(self, mass):
        a = MagicMock()
        a.id = 1
        a.get_name.return_value = ('Reader 1', 1)
        b = MagicMock()
        b.id = 2
        b.get_name.return_value = ('Reader 2', 0)

        mass.add_reader(a)
        mass.add_reader(b)

        expected = ['Reader 1', 'Reader 2']

        assert mass.allocate(1) == expected

    def test_allocate_3_slots_3_readers(self):
        mass = Mass(
            'saturday',
            {
                'needed': 3,
                'startfrom': 1,
                'exclude': [],
                'readers': {}
            }
        )

        a = MagicMock()
        a.id = 1
        a.get_name.return_value = ("One", 2)
        b = MagicMock()
        b.id = 2
        b.get_name.return_value = ("Two A, Two B", 0)

        mass.add_reader(a)
        mass.add_reader(b)

        expected = ['One', 'Two A, Two B']

        assert mass.allocate(1) == expected

    def test_allocate_2_slots_3_readers(self, mass):
        a = MagicMock()
        a.id = 1
        a.get_name.return_value = ("One", 2)
        b = MagicMock()
        b.id = 2
        b.get_name.return_value = ("Two", 0)

        mass.add_reader(a)
        mass.add_reader(b)

        expected = ['One', 'Two']

        assert mass.allocate(1) == expected

    def test_allocate_3_slots_2_readers(self):
        mass = Mass(
            'saturday',
            {
                'needed': 3,
                'startfrom': 1,
                'exclude': [],
                'readers': {}
            }
        )

        a = MagicMock()
        a.id = 1
        a.get_name.return_value = ("One", 2)
        b = MagicMock()
        b.id = 2
        b.get_name.return_value = ("Two", 1)

        mass.add_reader(a)
        mass.add_reader(b)

        expected = 'Not enough readers for a single mass'

        # with pytest.raises(Exception, message=expected):
        mass.allocate(1)
