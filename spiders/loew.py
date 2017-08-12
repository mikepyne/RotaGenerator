import scrapy
from scrapy.crawler import CrawlerProcess
from scrapy.selector import Selector
from scrapy.http import HtmlResponse


class LoewSpider(scrapy.Spider):
    name = "liturgyoffice"

    def start_requests(self):
        urls = ['http://www.liturgyoffice.org.uk/Calendar/2017/Aug.shtml']

        for url in urls:
            yield scrapy.Request(url=url, callback=self.parse)

    def parse(self, response):
        html = HtmlResponse(
            url='http://www.liturgyoffice.org.uk/Calendar/2017/Aug.shtml',
            body=response.body)

        print('Selector: {0}'.format(Selector(response=html).xpath(
            '//html/body/div[@id="wrapper"]/div[@id="header"]/div[@id="main"]'
            '/div[@id="content"]/div[@id="Calendar"]'
        ).extract()))


process = CrawlerProcess({
    'USER_AGENT': 'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1)'
})

process.crawl(LoewSpider)
process.start()
