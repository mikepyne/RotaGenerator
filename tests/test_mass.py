import pytest
from unittest.mock import Mock
from rota.mass import Mass, MassError


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
            m = Mass(label, data)

    @pytest.mark.parametrize("label, data", init_data, ids=init_ids)
    def test_init(self, label, data):
        m = Mass(label, data)


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
                'exclude': ['A'],
                'readers':{
                    1: {
                        "name": "Gabrielle Bedford",
                        "exclude": []
                    }
                }
            },
            # Long string split over two lines
            "Mass('saturday', 2, 1, ['A'], "
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
        tr = Mock()
        tr.id = 1
        tr.name = 'A Reader'
        mass.add_reader(tr)
        assert mass.readers[1] == tr

    def test_add_exclude(self, mass):
        mass.add_exclude(None)
        assert mass.exclude == []
