import inflect
import logging
from datetime import date, timedelta
import calendar

class RotaDays:
    def __init__(self):
        self.logger = logging.getLogger('rotaGenerator.rota_days')
        self.ie = inflect.engine()

    # Weekday 0 is Monday; weekday 6 is Sunday
    # Test case: Sat 28th Feb/Sun 1st March 2015
    # Another test case: December - February

    def find_weekends(self, start_year, start, end, end_year=None):
        """Find each Saturday and Sunday in a particular rota period.

        Parameters:
        start_year -- the year the starting month is in
        start -- the starting month
        end -- the ending month
        end_year -- the year the ending month is in, if different to start year
        """
        self.logger.debug('start_year=%s, start=%s, end=%s, end_year=%s',
                          start_year, start, end, end_year)

        if end_year is None:
            end_year = start_year
            self.logger.debug('end_year=%s', end_year)

        weekends = []
        current = date(start_year, start, 1)
        e = calendar.monthrange(end_year, end)[1] # monthrange returns two values
        last = date(end_year, end, e)
        self.logger.debug('current=%s, last=%s', current, last)

        while(current <= last):
            if current.weekday() < 6:
                current = current + timedelta(days=(6 - current.weekday()))

            saturday = current - timedelta(days=1)
            weekends.append(self.format_weekend(saturday, current))
            current = current + timedelta(days=7)

        return weekends

    def format_weekend(self, saturday, sunday):
        """Format the string for a weekend

        Parameters:
        saturday -- the date of the saturday
        sunday -- the date of the sunday

        Currently uses a fixed format for the weekend. For example:
            - Saturday 31st December/Sunday 1st January
            - Saturday 11th/Sunday 12th February
        """
        self.logger.debug('saturday=%s, sunday=%s, ', saturday,
                          sunday)

        sun = self.ie.ordinal(sunday.day)
        sat = self.ie.ordinal(saturday.day)

        if saturday.month == sunday.month:
            weekend = '{a:%A} {b}/{c:%A} {d} {c:%B}'.format(a=saturday,
                b=sat, c=sunday, d=sun)

        else:
            weekend = '{a:%A} {b} {a:%B}/{c:%A} {d} {c:%B}'.format(a=saturday,
                b=sat, c=sunday, d=sun)

        self.logger.debug('returning: %s', weekend)
        return weekend
