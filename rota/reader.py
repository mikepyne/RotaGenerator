import logging

class ReaderError(Exception):
    pass

class Reader:
    def __init__(self, id, name='', names=[], exclude=[]):
        if not name and not names:
            raise ReaderError('Reader must have a name and/or names')

        self.id = id
        self.name = name
        self.names = names
        self.exclude = exclude

    def __repr__(self):
        return("{0}({1}, '{2}', {3}, {4})".format(self.__class__.__name__,
                                                     self.id,
                                                     self.name,
                                                     str(self.names),
                                                     str(self.exclude)))

    def __str__(self):
        string = '{0} - {1}'.format(self.id, self.name)
        if not self.name:
            string = '{0} - {1}'.format(self.id, str(self.names))

        return string

    def __eq__(self, other):
        eq = False
        if isinstance(other, int):
            eq = self.id == other
        else:
            eq = self.id == other.id and self.name == other.name and \
                 self.names == other.names and self.exclude == self.exclude

        return eq
