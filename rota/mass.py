import logging
from .reader import Reader, ReaderError


class MassError(Exception):
    pass


class Mass:
    """Represents a mass readers are needed for"""

    def __init__(self, label, needed, startfrom):
        """Create the Mass object

        Arguments:
        label -- [string] a label for the mass (e.g. Saturday)
        needed -- [int] how many readers are needed for a Mass
        startfrom -- [int] which reader to startfrom
        """
        self.label = label
        self.needed = needed
        self.startfrom = startfrom
        self.readers = []

    def add_reader(self, reader):
        """Add a reader to the mass

        Arguments:
        reader -- [Reader] the reader to add
        """
        if not isinstance(reader, Reader):
            raise MassError('Not a reader')

        self.readers.append(reader)

    def get_reader(self, id):
        """Get a reader object

        Arguments:
        id -- the id of the reader to retrieve
        """
        for r in self.readers:
            if r == id:
                return r
