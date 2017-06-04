import json
import logging

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
        self.readings = {}
        self.readers = {}

    def read(self, conf_file):
        """Read config data from the file

        Parameters:
        conf_file -- a file-like object to read from

        conf_file is a file like object, rather than the path to a file to make
        testing easier.
        """
        loaded = json.load(conf_file)
        if len(loaded) is 0:
            raise ConfigError('No configuration details available')

        for index in loaded:
            self.validate(index, loaded[index])

    def validate(self, index, record):
        """Validate a record from the config"""
        self.logger.debug("Validating record '%s'", index)
        required_keys = ['spaces', 'startfrom']

        try:
            for key in required_keys:
                if not isinstance(record[key], int):
                    raise ConfigError("Key isn't an int", key, index)

        except KeyError as e:
            raise ConfigError('Missing key', e, index)

        try:
            for reader in record['readers']:
                if len(record['readers'][reader]) is not 0:
                    self.validate_reader(index, reader,
                                         record['readers'][reader])
                else:
                    raise ConfigError('Empty readers', 'readers', index)

        except KeyError as e:
            raise ConfigError('Missing readers', e, index)

    def validate_reader(self, index, reader_id, reader):
        self.logger.debug("Validating reader '%s' in record '%s'", reader_id,
                          index)

        if 'name' not in reader and 'names' not in reader:
            raise ConfigError('No name or names in reader', reader_id, index)

        if 'names' in reader and len(reader['names']) is 0:
            raise ConfigError('Names is empty', reader_id, index)

        if 'name' in reader and not reader['name']:
            raise ConfigError('Empty name', reader_id, index)

        # Does 'names' contain contain an empty string?
        if 'names' in reader and len(reader['names']) is not 0:
            for name in reader['names']:
                if not name:
                    raise ConfigError('Names has an empty name', reader_id,
                                      index)

