import logging
from rota.exclude import ExcludeMixin


class ReaderError(Exception):
    def __init__(self, error, id=None):
        self.error = error
        self.id = id

    def __str__(self):
        return "{0}; ID: {1}".format(self.error, self.id)


class Reader(ExcludeMixin):
    """ A reader available for a mass

    Instance variables:
    id -- the numeric ID of the reader
    name -- The name of the reader (either full name, or surname)
    names -- The names for the reader
    date_format -- The date format used to parse exclusions
    exclude -- A list of dates the reader cannot make

    A 'reader' may be a single person (in which case, only 'name' is required)
    or may be multiple people (e.g. a family). In this case, the surname should
    be specified for 'name', with individual names in 'names'.

    The 'exclude' variable is a list of dates that the reader is unavailable
    for. The dates are passed in as strings and are parsed into date objects.
    The dates should be in either the default format of 'DD/MM/YYYY', or the
    desired format should be specified in the date_format parameter on
    construction an object. The date_format parameter follows the rules for
    strftime and strptime in the python documentation.
    """

    def __init__(self, id, data, date_format='%d/%m/%Y'):
        """Initialise a reader object

        Arguments:
        id -- the reader ID
        data -- A dictonary containing the reader data (name, exclude, etc)
        date_format -- Format of dates in the exclude list
        """
        self.logger = logging.getLogger('rotaGenerator.Reader')
        self.id = id
        try:
            ExcludeMixin.__init__(self, data['exclude'], date_format)
        except KeyError:
            ExcludeMixin.__init__(self, [], date_format)

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
                    raise ReaderError('Empty name in names', self.id)
        except TypeError as e:
            raise ReaderError('Invalid names ({0})'.format(e), self.id)

    def __repr__(self):
        return("{0}({1:d}, '{2}', {3!r}, {4!r})".format(
            self.__class__.__name__,
            self.id,
            self.name,
            self.names,
            self.excludes_as_string()))

    def __str__(self):
        string = '{0} - {1}'.format(self.id, self.name)
        if not self.name:
            string = '{0} - {1}'.format(self.id, str(self.names))

        return string

    def get_name(self, slots):
        """Get the name of this reader

        When a reader with multiple names has fewer names than slots, the list
        of individual names is returned as a combined string. When the reader
        has enough or more names, only the 'name' is returned.

        Arguments:
        slots -- the number of slots to be filled

        Returns:
        A string containing the name(s) of the reader
        """
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
