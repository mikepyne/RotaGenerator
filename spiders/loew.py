from bs4 import BeautifulSoup


class LiturgyOffice:
    root_url = 'http://www.liturgyoffice.org.uk/Calendar/'

    def get_sundays_in(self, year, month):
        url = '{0}{1}/{2}.shtml'.format(LiturgyOffice.root_url, year, month)
        sunday_rows = []
        with open('../docs/Liturgical Calendar | August 2017.shtml',
                  encoding='windows-1252') as doc:
            soup = BeautifulSoup(doc, 'lxml')
            table = soup.find('table', summary='Liturgical Calendar for August 2017')
            all_rows = table.find('tr')
            sunday_rows = table.find_all(self._row_is_sunday)

        if sunday_rows:
            self._parse_sundays(sunday_rows)

    def _parse_sundays(self, rows):
        pass

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
    lo.get_sundays_in('2017', 'Aug')
