from datetime import datetime


class ExcludeError(Exception):
    def __init__(self, error):
        self.error = error

    def __str__(self):
        return "{0}".format(self.error)


class ExcludeMixin():
    """Common functionality to handle exclusion dates

    Instance Variables:
    exclude -- a list of Date objects
    date_format -- the format to use with strptime and strftime
    """

    def __init__(self, excludes, date_format='%d/%m/%Y'):
        self.date_format = date_format
        if excludes:
            self.exclude = []
            try:
                for d in excludes:
                    self.exclude.append(
                        datetime.strptime(d, self.date_format).date())

            except (TypeError, ValueError):
                raise ExcludeError('Bad value in excludes')
        else:
            self.exclude = []

    def is_excluded(self, check_date):
        """Should date be excluded?

        Arguments:
        check_date -- date to check

        Returns:
        true if check_date is in the list of excludes; false otherwise
        """
        try:
            return check_date in self.exclude
        except AttributeError:
            return False

    def excludes_as_string(self):
        excludes = []
        for d in self.exclude:
            excludes.append(datetime.strftime(d, self.date_format))

        return excludes

    def add_exclude(self, exclude):
        """Add exclusions

        Arguments:
        exclude -- Date to exclude
        """
        try:
            self.exclude.append(
                datetime.strptime(exclude, self.date_format).date())
        except (TypeError, ValueError):
            raise ExcludeError('Bad value adding exclusion')
