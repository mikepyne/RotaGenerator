from bs4 import BeautifulSoup
from datetime import date, timedelta
from urllib import request


class Universalis:
    root_url = ('https://universalis.com/Europe.England.Portsmouth.Berkshire/'
                'calendar.htm?year=')

    def get_sundays_in(self, year, month):
        start = date(year, month, 1)
        stop = date(year, month + 1, 1)
        # TODO: Needs to handle December properly
        start_str = start.strftime('%B')
        stop_str = stop.strftime('%B')
        sunday_rows = []
        with request.urlopen(self._build_url(year)) as response:
            soup = BeautifulSoup(response.read(), "lxml")
            table = soup.find('table', id='yearly-calendar')
            in_month = False
            for row in table.find_all('tr'):
                if row.string == start_str:
                    # Set a flag, start looking for Sundays in the target month
                    in_month = True
                    continue

                if in_month:
                    print(row.contents[0].string)

                if row.string == stop_str:
                    # Got to the next month, so exit the loop
                    break

        # if sunday_rows:
        #     return self._parse_sundays(sunday_rows, year, month)

        # return []

    def _build_url(self, year):
        url = self.root_url + str(year)
        return url

if __name__ == "__main__":
    u = Universalis()
    print(u.get_sundays_in(2017, 7))
