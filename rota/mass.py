import logging
from .reader import Reader, ReaderError


class MassError(Exception):
    def __init__(self, error, label = None):
        self.error = error
        self.label = label

    def __str__(self):
        return "{0}; Label: {1}".format(self.error, self.label)


class Mass:
    """Represents a mass readers are needed for"""

    def __init__(self, label, needed, startfrom, exclude=None, readers=None):
        """Create the Mass object

        Arguments:
        label -- [string] a label for the mass (e.g. Saturday)
        needed -- [int] how many readers are needed for a Mass
        startfrom -- [int] which reader to startfrom
        exclude -- [list] masses which do not need readers
        readers -- [dict] the readers for the Mass

        To Do:
            * Check 'exclude'
            * Check 'readers'
        """
        self.label = label
        self.needed = needed
        self.startfrom = startfrom
        if exclude is None:
            self.exclude = []
        else:
            self.exclude = exclude
        if readers is None:
            self.readers = {}
        else:
            self.readers = readers

        if not self.label:
            raise (MassError('Bad label'))

        try:
            int(self.needed)
        except ValueError:
            raise MassError("'needed' is invalid ({0})".format(self.needed),
                            self.label)

        try:
            int(self.startfrom)
        except ValueError:
            raise MassError(
                "'startfrom' is invalid ({0})".format(self.startfrom),
                self.label
            )

    def __str__(self):
        return self.label

    def __repr__(self):
        return("{0}('{1}', {2:d}, {3:d}, {4!r}, {5!r})".format(
                self.__class__.__name__,
                self.label,
                self.needed,
                self.startfrom,
                self.exclude,
                self.readers))

    def add_reader(self, reader):
        """Add a reader to the mass

        Arguments:
        reader -- [Reader] the reader to add
        """
        self.readers[reader.id] = reader

    def get_reader(self, id):
        """Get a reader object

        Arguments:
        id -- the id of the reader to retrieve
        """
        if id in self.readers:
            return self.readers[id]
        else:
            raise MassError('No reader for ID: {0:d}'.format(id))
