import pytest
from io import StringIO
from rota.config import Config, ConfigError


@pytest.mark.skip(reason="Config object may be deprecated")
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


@pytest.mark.skip(reason="Config object may be deprecated")
class TestConfig(object):
    def test_config_empty(self, config):
        data = StringIO("{}")
        with pytest.raises(
            ConfigError,
            match='No configuration details available'
        ):
            config.read(data)

    def test_read_missing_key_name(self, config):
        data = StringIO("""{
                            "saturday": {
                                "needed": 1,
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
                                "needed": 1,
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
                                "needed": 2,
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
                                "needed": 2,
                                "startfrom": 3,
                                "readers": {
                                    "1": {
                                        "name": "Gabrielle",
                                        "exclude": []
                                    }
                                }
                            },
                            "sunday": {
                                "needed": 3,
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
