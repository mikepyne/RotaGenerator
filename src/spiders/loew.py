from bs4 import BeautifulSoup
from datetime import date
import urllib.request


class LiturgyOffice:
    """Get details of Sundays from the Liturgy Office"""
    root_url = 'https://www.liturgyoffice.org.uk/Calendar/'

    def get_sundays_in(self, year, month):
        sunday_rows = []
        with urllib.request.urlopen(self._build_url(year, month)) as response:
            soup = BeautifulSoup(response.read(), 'lxml')
            table = soup.find('table', summary=self._build_summary(year, month))
            all_rows = table.find('tr')
            sunday_rows = table.find_all(self._row_is_sunday)

        if sunday_rows:
            return self._parse_sundays(sunday_rows, year, month)

        return []

    def _build_url(self, year, month):
        d = date(year, month, 1)
        url = '{0}{1}/{2}.shtml'.format(LiturgyOffice.root_url,
                                        d.strftime('%Y'),
                                        d.strftime('%b'))

        return url

    def _build_summary(self, year, month):
        d = date(year, month, 1)
        summary = 'Liturgical Calendar for {0} {1}'.format(d.strftime('%B'),
                                                           d.strftime('%Y'))

        return summary

    def _parse_sundays(self, rows, year, month):
        d = date(year, month, 1)
        sundays = []
        for row in rows:
            date_cell = row.find('td', class_='date')
            sol = row.find('td', class_='sol')

            parsed = '{0} {1}, {2}'.format(d.strftime('%b'),
                                           date_cell.string,
                                           sol.string)

            sundays.append(parsed)

        return sundays

    def _row_is_sunday(self, tag):
        is_sunday = False
        if tag.name == 'tr':
            child = tag.find('td', class_="Sunday")
            if child is not None:
                # The class attribute is returned as a list of strings (or none)
                if 'Sunday' in child['class'] and child.string == 'Sunday':
                   is_sunday = True

        return is_sunday

if __name__ == '__main__':
    lo = LiturgyOffice()
    print(lo.get_sundays_in(2017, 9))
    print(lo.get_sundays_in(2017, 10))
    print(lo.get_sundays_in(2017, 11))
