import json
import logging
from collections import OrderedDict
from .mass import Mass
from .reader import Reader


class ConfigError(Exception):
    def __init__(self, error, key = None, record = None):
        self.error = error
        self.key = key
        self.record = record

    def __str__(self):
        return "{0}; Key: {1}; Record: {2}".format(self.error, self.key,
                                                   self.record)


class Config:
    def __init__(self):
        self.logger = logging.getLogger('rotaGenerator.config')
        self.loaded_data = OrderedDict()

    def read(self, conf_file):
        """Read config data from the file

        Parameters:
        conf_file -- a file-like object to read from

        conf_file is a file like object, rather than the path to a file to make
        testing easier.
        """
        self.loaded_data = json.load(conf_file, object_pairs_hook=OrderedDict)
        if len(self.loaded_data) is 0:
            raise ConfigError('No configuration details available')

        for index in self.loaded_data:
            m = Mass(index, self.loaded_data[index])
