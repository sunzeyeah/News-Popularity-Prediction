#This code is used to scrape data(news title, date, contents, # of reviews, # of participants and first 10 reviews)
#from www.sina.com.cn but can be easily adjusted for other websites.



# -*- coding:utf-8 -*-
import scrapy
#import time
import csv
from sina.items import SinaItem
#from scrapy.contrib.linkextractors.lxmlhtml import LxmlLinkExtractor
from scrapy.contrib.linkextractors import LinkExtractor
from scrapy.contrib.spiders import CrawlSpider
from scrapy.contrib.spiders import Rule
from scrapy.spider import Spider
from scrapy.http import Request
from selenium import webdriver
from selenium.webdriver.common.keys import Keys


class SinaNewsSpider(CrawlSpider): #Scrape the news title, date and contents
 name = 'news'
 allowed_domains = ['sina.com.cn']
 start_urls = [
  'http://news.sina.com.cn/'
  'http://finance.sina.com.cn/',
  'http://mil.news.sina.com.cn/',
  'http://news.sina.com.cn/society/',
  'http://tech.sina.com.cn/',
  'http://mobile.sina.com.cn/',
  'http://sports.sina.com.cn/',
  'http://ent.sina.com.cn/',
  'http://auto.sina.com.cn/',
  'http://book.sina.com.cn/',
  'http://edu.sina.com.cn/',		
  'http://health.sina.com.cn/',
  'http://eladies.sina.com.cn/',
  'http://collection.sina.com.cn/',
  'http://fashion.sina.com.cn/',
  'http://sky.news.sina.com.cn/',
  'http://edu.sina.com.cn/a/',
  'http://games.sina.com.cn/',
  'http://golf.sina.com.cn/',
  'http://fo.sina.com.cn/']
 rules = [
  Rule(LinkExtractor(allow=('news\.sina\.com\.cn/.*/?2015[-\d/]{1}',
   'finance\.sina\.com\.cn/.*/?2015[-\d/]{1}',
   'tech\.sina\.com\.cn/.*/?2015[-\d/]{1}',
   'sports\.sina\.com\.cn/.*/?2015[-\d/]{1}',
   'ent\.sina\.com\.cn/.*/?2015[-\d/]{1}',
   '//auto\.sina\.com\.cn/.*/?2015[-\d/]{1}',
   'book\.sina\.com\.cn/.*/?2015[-\d/]{1}',
   'edu\.sina\.com\.cn/.*/?2015[-\d/]{1}',
   'health\.sina\.com\.cn/.*/?2015[-\d/]{1}',
   'eladies\.sina\.com\.cn/.*/?2015[-\d/]{1}',
   'collection\.sina\.com\.cn/.*/?2015[-\d/]{1}',
   'fashion\.sina\.com\.cn/.*/?2015[-\d/]{1}',
   'games\.sina\.com\.cn/.*/?2015[-\d/]{1}',
   'fo\.sina\.com\.cn/.*/?2015[-\d/]{1}'),deny=('html.+','/l/')),callback = 'parse_item',follow = True)]
 def parse_item(self,response):
  url = str(response.url)
  
  #Title Extraction
  title = [n.encode('utf-8') for n in response.xpath('//h1[contains(@id,"artibodyTitle")]/text()').extract()]
  #title = response.xpath('//head/title/text()').extract()
  
  #Date Exctration
  Date = response.xpath('//span[contains(@id,"pub_date")]/text()').extract()  #html
  Date += response.xpath('//span[contains(@class,"time-source")]/text()').extract()   #shtml
  date = [n.encode('utf-8') for n in Date]
  
  #Contents Extraction
  contents = ''
  for body in response.xpath('//div[contains(@id,"artibody")]//p/text()'):
   for n in body.extract():
    contents += n.encode('utf-8')
    
  #Dynamic Contents Extraction:(1)Extract News ID and review channel
  newsID = ''
  channel = ''
  raw = str(response.xpath('//meta[contains(@content,"comment_channel")]/@content').extract())
  real=''
  i = 3
  while i <= len(raw)-3:
   real += raw[i]
   i = i + 1
   final=[]
   for s in real.split(':'):
    ss = s.split(';')
    for eachone in ss:
     final.append(eachone)
   i = 0
   while i < len(final):
    if 'comment_id' in final[i]:
     i = i + 1
     newsID = final[i]
    elif 'comment_channel' in final[i]:
     i = i + 1
     channel = final[i]
    i = i + 1
    
  #Dynamic Contents Extraction:(2)Generate the url of reviews
  comment_url = 'http://comment5.news.sina.com.cn/comment/skin/default.html?channel='+channel+'&newsid='+newsID
  if title and date and contents: #and newsID and channel:
   item = SinaItem()
   item['url'] = url.encode('utf-8')
   item['comment_url'] = comment_url.encode('utf-8')
   item['title'] = title
   item['date'] = date
   item['body'] = contents
   yield item


class SinaCommentSpider(Spider): #Scrape the news reviews
 name = 'comment'
 allowed_domains = ['sina.com.cn']
 start_urls = ['http://comment5.news.sina.com.cn/comment/skin/default.html?channel=kj&newsid=2-1-9977035']
 def parse(self,response):
  url = str(response.url)
  if 'comment5' in url:
  item = SinaItem()
  
  #Dynamic Contents Extraction:(3)Open selenium explorer
  driver = webdriver.Firefox()
  driver.get(url)
  #extracing news title(adjustment for abnormal urls)
  try:
   title = driver.find_element_by_xpath('//h1[@id = "J_NewsTitle"]/a').text.encode('utf-8') #when channel is not 'kj'
   title = driver.find_element_by_xpath('//h1[@bbs-node-type = "title"]/a').text.encode('utf-8') #when channel is 'kj'
  except:
   title = ''
   item['title'] = title
   
  #Dynamic Contents Extraction:(4)Extracting # of reviews
  contents = driver.find_elements_by_xpath('//span[contains(@class,"f_red")]') #when channel is not 'kj'
# contents = driver.find_elements_by_xpath('//span[contains(@class,"count")]//em')  #when channel is 'kj'
  try:
   item['num_comment'] = contents[0].text.encode('utf-8')
  except:
   item['num_comment'] = 0
   
  #Dynamic Contents Extraction:(5)Extractng # of participants
  try:
   item['num_part'] = contents[1].text.encode('utf-8')
  except:
   item['num_part'] = 0
   
  #Dynamic Contents Extraction:(6)Extracting reviews
  comments = ''
  #when channel is not 'kj'
  for comment in driver.find_elements_by_xpath('//div[@id="J_Comment_List_Hot"]//div[@class="orig_content"]'):
   comments += comment.text.encode('utf-8')+'\n'+'\n'
  for comment in driver.find_elements_by_xpath('//div[@id="J_Comment_List_Hot"]//div[@class="t_txt"]'):
   comments += comment.text.encode('utf-8')+'\n'+'\n'
  for comment in driver.find_elements_by_xpath('//div[@class="comment_item_page_first"]//div[@class="orig_content"]'):
   comments += comment.text.encode('utf-8')+'\n'+'\n'
  for comment in driver.find_elements_by_xpath('//div[@class="comment_item_page_first"]//div[@class="t_txt"]'):
   comments += comment.text.encode('utf-8')+'\n'+'\n'
  #when channel is 'kj'
# for comment in driver.find_elements_by_xpath('//div[@class="sina-comment-page sina-comment-page-show"]//div[@comment-type="itemTxt"]'):
# comments += comment.text.encode('utf-8')+'\n'+'\n'
  item['comment'] = comments
  driver.close()
  yield item
  
  #Obtain the url of next piece of news
  reader = csv.reader(open('/media/sunzeyeah/Personal/SENIOR/Thesis/Data/Chinese/Sina/news_0317.csv','r'))
  for line in reader:
   if line[0] != 'comment_url':
    yield Request(line[0], callback=self.parse)
