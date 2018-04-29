import logging


class ReaderError(Exception):
    def __init__(self, error, id=None):
        self.error = error
        self.id = id

    def __str__(self):
        return "{0}; ID: {1}".format(self.error, self.id)


class Reader:
    def __init__(self, id, data):
        self.logger = logging.getLogger('rotaGenerator.Reader')
        self.id = id

        if 'name' not in data and 'names' not in data:
            raise ReaderError('Reader must have a name and/or names', self.id)

        try:
            self.name = data['name']
        except KeyError:
            self.name = ''

        try:
            self.names = data['names']
        except KeyError:
            self.names = []

        try:
            for n in self.names:
                if not n:
                    raise ReaderError('Bad name in names', self.id)
        except TypeError as e:
            raise ReaderError('Invalid names ({0})'.format(e), self.id)

        try:
            self.exclude = data['exclude']
        except KeyError:
            self.exclude = []

    def __repr__(self):
        return("{0}({1:d}, '{2}', {3!r}, {4!r})".format(
            self.__class__.__name__,
            self.id,
            self.name,
            self.names,
            self.exclude))

    def __str__(self):
        string = '{0} - {1}'.format(self.id, self.name)
        if not self.name:
            string = '{0} - {1}'.format(self.id, str(self.names))

        return string

    def get_name(self, slots):
        if self.names:
            num_names = len(self.names)
            if num_names < slots:
                return ', '.join(self.names)
            elif num_names == slots:
                return self.name
            else:
                self.logger.warn("More names than slots")
                return self.name
        else:
            return self.name
