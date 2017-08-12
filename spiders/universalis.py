import scrapy
from scrapy.crawler import CrawlerProcess


class UniversalisSpider(scrapy.Spider):
    name = "universalis"

    def start_requests(self):
        urls = ['http://universalis.com/calendar.htm?year=2017',
                'http://universalis.com/Europe.England.Portsmouth/calendar.htm?year=2018']

        # ToDo: Determine which URL should be the primary.

        for url in urls:
            yield scrapy.Request(url=url, callback=self.parse)

    def parse(self, response):
        print('{0}'.format(response.body))

process = CrawlerProcess({
    'USER_AGENT': 'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1)'
})

process.crawl(UniversalisSpider)
process.start()
