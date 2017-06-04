import pytest
import unittest
from io import StringIO
from rota.config import Config, ConfigError

@unittest.skip("Focus on testing config")
class TestConfigError(unittest.TestCase):
    def test_config_error(self):
        try:
            raise ConfigError("An error", "a key", "a record")
        except ConfigError as e:
            self.assertEqual("An error; Key: a key; Record: a record", str(e))


class TestConfig(unittest.TestCase):
    def setUp(self):
        self.conf = Config()


    def test_validate_reader_valid(self):
        data = {"name": "Gabrielle","exclude": []}
        try:
            self.conf.validate_reader('saturday', '1', data)
        except ConfigError as e:
            self.fail("Unexpected exception: '{0}'".format(e))

    def test_validate_reader_names(self):
        data = {"names": ["Gabrielle", "Ruth"], "exclude": []}
        try:
            self.conf.validate_reader('saturday', "1", data)
        except ConfigError as e:
            self.fail("Unexpected exception: '{0}'".format(e))

    def test_validate_reader_empty_name(self):
        data = {"name": "", "exclude": []}
        self.assertRaisesRegex(ConfigError,
                               'Empty name; Key: 1; Record: saturday',
                               self.conf.validate_reader,
                               'saturday',
                               '1',
                               data)

    def test_validate_reader_empty_names(self):
        data = {"names": [], "exclude": []}
        self.assertRaisesRegex(ConfigError,
                               'Names is empty; Key: 1; Record: saturday',
                               self.conf.validate_reader,
                               'saturday',
                               '1',
                               data)

    def test_validate_reader_empty_name_in_names(self):
        data = {"names": [""], "exclude": []}
        self.assertRaisesRegex(ConfigError,
                               'Names has an empty name; Key: 1; Record: saturday',
                               self.conf.validate_reader,
                               'saturday',
                               '1',
                               data)

    @unittest.skip("Focus on validate_reader")
    def test_config_empty(self):
        data = StringIO("{}")
        self.assertRaisesRegex(ConfigError,
                               'No configuration details available',
                               self.conf.read,
                               data)

    @unittest.skip("Focus on validate_reader")
    def test_config_missing_key_readers(self):
        data = StringIO("""{
                            "saturday": {
                                "spaces": 2,
                                "startfrom": 1
                           }
                        }""")

        self.assertRaisesRegex(
                ConfigError,
                "Missing readers; Key: 'readers'; Record: saturday",
                self.conf.read, data)

    @unittest.skip("Focus on validate_reader")
    def test_config_missing_key_spaces(self):
        data = StringIO("""{
                            "saturday": {
                                "startfrom": 1,
                                "readers": {
                                    "1": {
                                        "name": "Gabrielle Bedford",
                                        "exclude": []
                                    }
                                }
                            }
                        }""")

        self.assertRaisesRegex(ConfigError,
                               "Missing key; Key: 'spaces'; Record: saturday",
                               self.conf.read, data)

    @unittest.skip("Focus on validate_reader")
    def test_config_missing_key_startfrom(self):
        data = StringIO("""{
                            "saturday": {
                                "spaces": 1,
                                "readers": {
                                    "1": {
                                        "name": "Gabrielle Bedford",
                                        "exclude": []
                                    }
                                }
                            }
                        }""")

        self.assertRaisesRegex(ConfigError,
                               "Missing key; Key: 'startfrom'; Record: saturday",
                               self.conf.read, data)

    @unittest.skip("Focus on validate_reader")
    def test_config_missing_key_name(self):
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

        self.assertRaisesRegex(
                ConfigError,
                "No name or names in reader; Key: 1; Record: saturday",
                self.conf.read,
                data)

    @unittest.skip("Focus on validate_reader")
    def test_config_missing_key_name_but_names(self):
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

        try:
            self.conf.read(data)
        except ConfigError as e:
            self.fail("Unexpected exception: '{0}'".format(e))

    @unittest.skip("Focus on validate_reader")
    def test_config_empty_readers(self):
        data = StringIO("""{
                            "saturday": {
                                "spaces": 2,
                                "startfrom": 1,
                                "readers": {
                                }
                            }
                        }""")

        self.assertRaisesRegex(ConfigError, "No readers for 'saturday'",
                               self.conf.read, data)

    @unittest.skip("Focus on validate_reader")
    def test_config_config(self):
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

        self.conf.read(data)
        self.assertEqual(self.conf.readings, expected_readings)
        self.assertEqual(self.conf.readers, expected_readers)


#TODO: Add tests for validate and validate_reader, then for read?

if __name__ == '__main__':
    unittest.main()
