import unittest
from io import StringIO
from rota.config import Config, ConfigException


class TestConfig(unittest.TestCase):
    def setUp(self):
        self.conf = Config()

    def test_config_empty(self):
        data = StringIO("{}")
        self.assertRaisesRegex(ConfigException,
                               'No configuration details available',
                               self.conf.read,
                               data)

    def test_config_missing_key_readers(self):
        data = StringIO("""{
                            "readings": {
                                "saturday": 2
                           }
                        }""")

        self.assertRaisesRegex(ConfigException, "Missing key: 'readers'",
                               self.conf.read, data)

    def test_config_missing_key_readings(self):
        data = StringIO("""{
                            "readers": {
                                "saturday": [
                                    "One"
                                ]
                            }
                        }""")

        self.assertRaisesRegex(ConfigException, "Missing key: 'readings'",
                               self.conf.read, data)

    def test_config_mismatch(self):
        data = StringIO("""{
                            "readings": {
                                "saturday": 2
                            },
                            "readers": {
                                "sunday": [
                                    "One"
                                ]
                            }
                        }""")

        self.assertRaisesRegex(ConfigException, "No readers for 'saturday'",
                               self.conf.read, data)

    def test_config_config(self):
        expected_readings = {"saturday": 2, "sunday": 3}
        expected_readers = {"saturday": ["Reader One"], "sunday": ["Reader Two"]}
        data = StringIO("""{
                            "readings": {
                                "saturday": 2,
                                "sunday": 3
                            },
                            "readers": {
                                "saturday": [
                                    "Reader One"
                                ],
                                "sunday": [
                                    "Reader Two"
                                ]
                            }
                        }""")

        self.conf.read(data)
        self.assertEqual(self.conf.readings, expected_readings)
        self.assertEqual(self.conf.readers, expected_readers)


if __name__ == '__main__':
    unittest.main()
