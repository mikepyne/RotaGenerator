import pytest
from io import StringIO
from rota.config import Config, ConfigError


class TestConfigError(object):
    def test_config_error(self):
        with pytest.raises(
            ConfigError,
            match='An error; Key: a key; Record: a record'
        ):
            raise ConfigError('An error', 'a key', 'a record')

    def test_config_error_key_none(self):
        with pytest.raises(
            ConfigError,
            match='An error; Key: None; Record: a record'
        ):
            raise ConfigError('An error', record='a record')

    def test_config_error_record_none(self):
        with pytest.raises(
            ConfigError,
            match='An error; Key: a key; Record: None'
        ):
            raise ConfigError('An error', 'a key')

    def test_config_error_key_record_none(self):
        with pytest.raises(
            ConfigError,
            match='An error; Key: None; Record: None'
        ):
            raise ConfigError('An error')


@pytest.fixture()
def config():
    return Config()


class TestConfig(object):
    def test_validate_reader_valid(self, config):
        data = {"name": "Gabrielle","exclude": []}
        config.validate_reader('saturday', '1', data)

    def test_validate_reader_names(self, config):
        data = {"names": ["Gabrielle", "Ruth"], "exclude": []}
        config.validate_reader('saturday', "1", data)

    def test_validate_reader_empty_name(self, config):
        data = {"name": "", "exclude": []}
        with pytest.raises(
            ConfigError,
            match='Empty name; Key: 1; Record: saturday'
        ):
            config.validate_reader('saturday', '1', data)

    def test_validate_reader_empty_names(self, config):
        data = {"names": [], "exclude": []}
        with pytest.raises(
            ConfigError,
            match='Names is empty; Key: 1; Record: saturday'
        ):
            config.validate_reader('saturday', '1', data)

    def test_validate_reader_empty_name_in_names(self, config):
        data = {"names": [""], "exclude": []}
        with pytest.raises(
            ConfigError,
            match='Names has an empty name; Key: 1; Record: saturday'
        ):
            config.validate_reader('saturday', '1', data)

    def test_config_empty(self, config):
        data = StringIO("{}")
        with pytest.raises(
            ConfigError,
            match='No configuration details available'
        ):
            config.read(data)

    def test_validate_missing_key_readers(self, config):
        data = {"spaces": 2, "startfrom": 1}
        with pytest.raises(
            ConfigError,
            match="Missing readers; Key: saturday; Record: None"
        ):
            config.validate('saturday', data)

    def test_validate_missing_key_spaces(self, config):
        data = {
            "startfrom": 1,
            "readers": {
                "1": {
                    "name": "Gabrielle Bedford",
                    "exclude": []
                }
            }
        }

        with pytest.raises(
            ConfigError,
            match="Missing key; Key: 'spaces'; Record: saturday"
        ):
            config.validate('saturday', data)

    def test_validate_missing_key_startfrom(self, config):
        data = {
            "spaces": 1,
            "readers": {
                "1": {
                    "name": "Gabrielle Bedford",
                    "exclude": []
                }
            }
        }

        with pytest.raises(
            ConfigError,
            match="Missing key; Key: 'startfrom'; Record: saturday"
        ):
            config.validate('saturday', data)

    def test_read_missing_key_name(self, config):
        data = StringIO("""{
                            "saturday": {
                                "spaces": 1,
                                "startfrom": 1,
                                "readers": {
                                    "1": {
                                        "exclude": []
                                    }
                                }
                            }
                        }""")

        with pytest.raises(
            ConfigError,
            match="No name or names in reader; Key: 1; Record: saturday"
        ):
            config.read(data)

    def test_read_missing_key_name_but_names(self, config):
        data = StringIO("""{
                            "saturday": {
                                "spaces": 1,
                                "startfrom": 1,
                                "readers": {
                                    "1": {
                                        "names": ["Mike", "Angharad"],
                                        "exclude": []
                                    }
                                }
                            }
                        }""")

        config.read(data)

    def test_read_empty_readers(self, config):
        data = StringIO("""{
                            "saturday": {
                                "spaces": 2,
                                "startfrom": 1,
                                "readers": {
                                }
                            }
                        }""")

        with pytest.raises(
            ConfigError,
            match="Empty readers; Key: saturday; Record: None"
        ):
            config.read(data)

    def test_read(self, config):
        expected_readings = {}
        expected_readers = {}
        data = StringIO("""{
                            "saturday": {
                                "spaces": 2,
                                "startfrom": 3,
                                "readers": {
                                    "1": {
                                        "name": "Gabrielle",
                                        "exclude": []
                                    }
                                }
                            },
                            "sunday": {
                                "spaces": 3,
                                "startfrom": 1,
                                "readers": {
                                    "1": {
                                        "name": "John",
                                        "exlude": []
                                    }
                                }
                            }
                        }""")

        config.read(data)

    def test_days(self, config):
        data = StringIO("""{
                            "saturday": {
                                "spaces": 2,
                                "startfrom": 3,
                                "readers": {
                                    "1": {
                                        "name": "Gabrielle",
                                        "exclude": []
                                    }
                                }
                            },
                            "sunday": {
                                "spaces": 3,
                                "startfrom": 1,
                                "readers": {
                                    "1": {
                                        "name": "John",
                                        "exlude": []
                                    }
                                }
                            }
                        }""")

        config.read(data);
        assert config.days() == ['saturday', 'sunday']

    def test_day(self, config):
        data = StringIO("""{
                            "saturday": {
                                "spaces": 2,
                                "startfrom": 3,
                                "readers": {
                                    "1": {
                                        "name": "Gabrielle",
                                        "exclude": []
                                    }
                                }
                            },
                            "sunday": {
                                "spaces": 3,
                                "startfrom": 1,
                                "readers": {
                                    "1": {
                                        "name": "John",
                                        "exclude": []
                                    }
                                }
                            }
                        }""")

        config.read(data);
        assert config.day('sunday') == {
            "spaces": 3,
            "startfrom": 1,
            "readers": {"1": {"name": "John", "exclude": []}}
        }

        assert config.day('saturday') == {
            "spaces": 2,
            "startfrom": 3,
            "readers": {
                "1": {
                    "name": "Gabrielle",
                    "exclude": []
                }
            }
        }
