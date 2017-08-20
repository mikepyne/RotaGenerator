from bs4 import BeautifulSoup

with open('../docs/Universalis: Calendar for 2017.htm') as doc:
    soup = BeautifulSoup(doc, 'lxml')
    print(soup.find('table', id='yearly-calendar'))
