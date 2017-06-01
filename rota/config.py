import json

class ConfigException(Exception):
    pass


class Config:
    def __init__(self):
        self.readings = {}
        self.readers = {}

    def read(self, conf_file):
        o = json.load(conf_file)
        if len(o) is 0:
            raise ConfigException("No configuration details available")

        try:
            self.readings = o['readings']
            self.readers = o['readers']
        except KeyError as e:
            raise ConfigException("Missing key: {0}".format(e))

        for r in self.readings:
            if r not in self.readers:
                raise ConfigException("No readers for '{0}'".format(r))
