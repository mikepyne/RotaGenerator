import logging
from .reader import Reader, ReaderError


class MassError(Exception):
    pass


class Mass:
    """Represents a mass readers are needed for"""

    def __init__(self, label, needed, startfrom, readers={}):
        """Create the Mass object

        Arguments:
        label -- [string] a label for the mass (e.g. Saturday)
        needed -- [int] how many readers are needed for a Mass
        startfrom -- [int] which reader to startfrom
        readers -- [dict] the readers for the Mass
        """
        self.label = label
        self.needed = needed
        self.startfrom = startfrom
        self.readers = readers

    def __str__(self):
        return self.label

    def __repr__(self):
        return("{0}('{1}', {2:d}, {3:d}, {4!r})".format(self.__class__.__name__,
                                                        self.label,
                                                        self.needed,
                                                        self.startfrom,
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
