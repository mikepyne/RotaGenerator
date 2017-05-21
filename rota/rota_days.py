from datetime import date

class RotaDays:
    # Weekday 0 is Monday; weekday 6 is Sunday
    # Test case: Sat 28th Feb/Sun 1st March 2015

    def get_weekends(self, year, start, end):
        d = date(year, start, 1)
        if d.weekday() == 5:
            # Saturday
            print "Saturday"
        elif d.weekday() == 6:
            # Sunday
            print "Sunday"
        else:
            # Move to weekend
            print "Weekday"
            d.day + 6 - d.weekday()
