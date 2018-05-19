# import logging
from rota.reader import Reader


class MassError(Exception):
    def __init__(self, error, label=None):
        self.error = error
        self.label = label

    def __str__(self):
        return "{0}; Label: {1}".format(self.error, self.label)


class Mass:
    """Represents a mass readers are needed for

    Instance Variables:
    label -- label for the mass (e.g. 'Saturday', or 'Sat 6:15pm')
    start_from -- ID of reader (in readers) to assign first
    needed -- how many readers are needed for each occasion
    exclude -- list of occasions to be excluded
    readers -- dictionary of readers available for the mass
    """

    def __init__(self, label, data):
        """Create the Mass object

        Arguments:
        label -- [string] a label for the mass (e.g. Saturday)
        data -- dict with the attributes for the mass

        To Do:
            * Check 'exclude'
            * Check 'readers'
        """
        self.label = label
        self.readers = {}
        if not self.label:
            raise (MassError('Bad label'))

        try:
            self.needed = data['needed']
            self.start_from = data['startfrom']
        except KeyError as e:
            raise MassError("Required key is missing ({0})".format(e),
                            self.label)

        try:
            self.exclude = data['exclude']
        except KeyError:
            self.exclude = []

        try:
            for r in data['readers']:
                reader = Reader(r, data['readers'][r])
                self.readers[r] = reader

        except KeyError:
            self.readers = {}

        try:
            int(self.needed)
        except ValueError:
            raise MassError("'needed' is invalid ({0})".format(self.needed),
                            self.label)

        try:
            int(self.start_from)
        except ValueError:
            raise MassError(
                "'start_from' is invalid ({0})".format(self.start_from),
                self.label
            )

        self.current_reader_id = self.start_from

    def __str__(self):
        return self.label

    def __repr__(self):
        return("{0}('{1}', {2:d}, {3:d}, {4!r}, {5!r})".format(
                self.__class__.__name__,
                self.label,
                self.needed,
                self.start_from,
                self.exclude,
                self.readers))

    def add_reader(self, reader):
        """Add a reader to the mass

        Arguments:
        reader -- [Reader] the reader to add
        """
        self.readers[reader.id] = reader

    def add_exclude(self, exclude):
        """Add a list of masses that don't need readers

        Arguments:
        excludes -- [list] Masses that don't need readers
        """
        if exclude is None:
            self.exclude = []
        else:
            self.exclude = exclude

    def get_reader(self, id=None):
        """Get a reader object

        Gets the reader object indicated by the given ID. If no ID is given,
        gets the current reader object and increments the index

        Arguments:
        id -- the id of the reader to retrieve

        Returns:
        The desired reader object
        """
        if id is None:
            id = self.current_reader_id
            self.current_reader_id += 1
        else:
            self.current_reader_id = id

        if id in self.readers:
            return self.readers[id]
        else:
            raise MassError('No reader for ID: {0:d}'.format(id))
