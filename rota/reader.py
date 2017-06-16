import logging

class ReaderError(Exception):
    def __init__(self, error, id = None):
        self.error = error
        self.id = id

    def __str__(self):
        return "{0}; ID: {1}".format(self.error, self.id)

class Reader:
    def __init__(self, id, name='', names=None, exclude=None):
        self.id = id
        self.name = name
        self.names = names
        self.exclude = exclude

        if not self.name and not self.names:
            raise ReaderError('Reader must have a name and/or names', self.id)

        try:
            for n in self.names:
                if not n:
                    raise ReaderError('Bad name in names', self.id)
        except TypeError as e:
            raise ReaderError('Invalid names ({s})'.format(e), self.id)

    def __repr__(self):
        return("{0}({1:d}, '{2}', {3!r}, {4!r})".format(self.__class__.__name__,
                                                        self.id,
                                                        self.name,
                                                        self.names,
                                                        self.exclude))

    def __str__(self):
        string = '{0} - {1}'.format(self.id, self.name)
        if not self.name:
            string = '{0} - {1}'.format(self.id, str(self.names))

        return string
