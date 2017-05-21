import inflect
from datetime import date, timedelta
import calendar

class RotaDays:
    def __init__(self):
        self.ie = inflect.engine()

    # Weekday 0 is Monday; weekday 6 is Sunday
    # Test case: Sat 28th Feb/Sun 1st March 2015

    def find_weekends(self, year, start, end):
        weekends = []
        current = date(year, start, 1)
        e = calendar.monthrange(year, end)[1] # monthrange returns two values
        last = date(year, end, e)

        while(current <= last):
            if current.weekday() < 6:
                current = current + timedelta(days=(6 - current.weekday()))

            saturday = current - timedelta(days=1)
            weekends.append(self.format_weekend(saturday, current))
            current = current + timedelta(days=7)

        return weekends

    def format_weekend(self, saturday, sunday):
        sun = self.ie.ordinal(sunday.day)
        sat = self.ie.ordinal(saturday.day)

        if saturday.month == sunday.month:
            weekend = '{a:%A} {b}/{c:%A} {d} {c:%B}'.format(a=saturday,
                b=sat, c=sunday, d=sun)

        else:
            weekend = '{a:%A} {b} {a:%B}/{c:%A} {d} {c:%B}'.format(a=saturday,
                b=sat, c=sunday, d=sun)

        return weekend
