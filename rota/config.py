import json
import logging

class ConfigException(Exception):
    pass


class Config:
    def __init__(self):
        self.logger = logging.getLogger('rotaGenerator.config')
        self.readings = {}
        self.readers = {}

    def read(self, conf_file):
        """Read config data from the file

        Parameters:
        conf_file -- a file-like object to read from

        conf_file is a file like object, rather than the path to a file to make
        testing easier.
        """
        o = json.load(conf_file)
        if len(o) is 0:
            self.logger.error('No configuration details available')
            raise ConfigException('No configuration details available')

        try:
            self.readings = o['readings']
            self.readers = o['readers']
        except KeyError as e:
            self.logger.error('Missing key: {0}'.format(e))
            raise ConfigException('Missing key: {0}'.format(e))

        for r in self.readings:
            if r not in self.readers or len(self.readers[r]) is 0:
                self.logger.error("No readers for '{0}'".format(r))
                raise ConfigException("No readers for '{0}'".format(r))
