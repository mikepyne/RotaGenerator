import logging
import scrapy
from scrapy.crawler import CrawlerProcess
from scrapy.selector import Selector
from scrapy.http import HtmlResponse
from scrapy.utils.log import configure_logging


class LoewSpider(scrapy.Spider):
    """Spider for extracting data from the Liturgy Office calendar

    I've noticed that the calendar uses the 'Sunday' class for days other than
    sundays. For example, Tuesday 15th August 2017 has the class 'Sunday'
    """
    name = "liturgyoffice"

    def start_requests(self):
        urls = ['http://www.liturgyoffice.org.uk/Calendar/2017/Aug.shtml']

        for url in urls:
            yield scrapy.Request(url=url, callback=self.parse)

    def parse(self, response):
        html = HtmlResponse(
            url=response.url,
            body=response.body)

        rows = Selector(response=html).xpath(
            '//html/body/div[@id="wrapper"]/div[@id="header"]/div[@id="main"]'
            '/div[@id="content"]/div[@id="Calendar"]'
            '/table[@summary="Liturgical Calendar for August 2017"]/tbody/tr'
            '[td[@class="Sunday"]]'
        )

        for row in rows:
            print(row.extract())


configure_logging({'LOG_LEVEL': logging.ERROR})
process = CrawlerProcess({
    'USER_AGENT': 'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1)'
})

process.crawl(LoewSpider)
process.start()
