import inflect
import logging
from datetime import date, timedelta
import calendar


class RotaDays:

    """Generate a list of Sundays in a rota period.

    Weekday 0 is Monday; weekday 6 is Sunday
    """

    def __init__(self):
        self.logger = logging.getLogger('rotaGenerator.rota_days')
        self.ie = inflect.engine()

    def find_weekends(self, start_year, start, end, end_year=None):
        """Find each Sunday in a particular rota period.

        Parameters:
        start_year -- the year the starting month is in
        start -- the starting month
        end -- the ending month
        end_year -- the year the ending month is in, if different to start year

        Returns a list of date for each Sunday in the target period
        """
        self.logger.debug('start_year=%s, start=%s, end=%s, end_year=%s',
                          start_year, start, end, end_year)

        if end_year is None:
            end_year = start_year
            self.logger.debug('end_year=%s', end_year)

        sundays = []
        current = date(start_year, start, 1)
        e = calendar.monthrange(end_year, end)[1]
        last = date(end_year, end, e)
        self.logger.debug('current=%s, last=%s', current, last)

        while(current <= last):
            if current.weekday() < 6:
                current = current + timedelta(days=(6 - current.weekday()))

            sundays.append(current)
            current = current + timedelta(days=7)

        return sundays

    def format_weekends(self, sundays):
        """Format all weekends into strings

        Parameters:
        sundays -- dates of Sundays to format

        Returns a list of strings of 'Saturday nth/Sunday mth Month'
        """
        formatted = []
        for sunday in sundays:
            formatted.append(self.format_weekend(sunday))

        return formatted

    def format_weekend(self, sunday):
        """Format the string for a single weekend

        Parameters:
        sunday -- date of a sunday

        Currently uses a fixed format for the weekend. For example:
            - Saturday 31st December/Sunday 1st January
            - Saturday 11th/Sunday 12th February

        Returns the weekend as a formatted string
        """
        self.logger.debug('sunday=%s', sunday)

        saturday = sunday - timedelta(days=1)
        sun = self.ie.ordinal(sunday.day)
        sat = self.ie.ordinal(saturday.day)

        if saturday.month == sunday.month:
            formatted = '{a:%A} {b}/{c:%A} {d} {c:%B}'.format(
                    a=saturday,
                    b=sat,
                    c=sunday,
                    d=sun)

        else:
            formatted = '{a:%A} {b} {a:%B}/{c:%A} {d} {c:%B}'.format(
                a=saturday,
                b=sat,
                c=sunday,
                d=sun)

        self.logger.debug('returning: %s', formatted)
        return formatted
