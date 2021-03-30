# -*- coding: utf-8 -*-
import string
import requests
import threading
from mysql_db_manager import CrawlDatabaseManager
from mongo_db_manager import FeedsMongoManager
from time import strftime,strptime,mktime
import re
import json
import time

CRAWL_DELAY = 2

MAX_PAGE = 10

class FeedsCrawler():

    url_format = "https://m.weibo.cn/api/container/getIndex?uid=%s&type=uid&value=%s&containerid=107603%s&page=%d"

    # querystring = {"version":"v4"}

    # payload = "------WebKitFormBoundary7MA4YWxkTrZu0gW\r\nContent-Disposition: form-data; name=\"version\"\r\n\r\nv4\r\n------WebKitFormBoundary7MA4YWxkTrZu0gW--"
    headers = {
        'content-type': "multipart/form-data; boundary=----WebKitFormBoundary7MA4YWxkTrZu0gW",
        'host': "m.weibo.cn",
        'connection': "keep-alive",
        'cache-control': "no-cache",
        'upgrade-insecure-requests': "1",
        'user-agent': "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36",
        'accept': "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
        'accept-encoding': "gzip, deflate, sdch, br",
        'accept-language': "zh-CN,en-US;q=0.8,en;q=0.6",
        'cookie': "_T_WM=0c8015962736d2199e208ca8adb7d301; SCF=AgS4nly86VG3e5zq2Usv2iN_bQIUj-rGsjZvQJLMLobUOXiNKaU1wEUxFjfWYNVchEv1_4Mfh08RgGthig-4Qcg.; SUB=_2A253p1ZcDeRhGeNG71YS9S7Jwj-IHXVVaHoUrDV6PUJbkdANLXbgkW1NS0f7LHe4BMxiV6LodCnt1vITwWSST2DI; SUHB=0xnCvYrYJqVQyb; SSOLoginState=1520641555; M_WEIBOCN_PARAMS=uicode%3D20000174",
        'postman-token': "0b85ea3b-073b-a799-4593-61095e4ed01a"
    }

    db_manager = CrawlDatabaseManager()

    feeds_db_manager = FeedsMongoManager()

    threads = []

    run = False

    def __init__(self):
        pass
    # 5s前 5分钟前 5小时前 05:05 05-05 2017-05-05
    def get_time(self, created_time):
        print(created_time)
        if u's' in created_time:
            time_sec=re.findall(u'(\d*)s',created_time)[0]
            time=mktime(strptime(strftime("%Y-%m-%d-%H-%M-")+time_sec,"%Y-%m-%d-%H-%M-%S"))
            return time
        elif u'分钟' in created_time:
            time_min=str(60-int(re.findall(u'(\d*)分',created_time)[0]))
            time=mktime(strptime(strftime("%Y-%m-%d-%H-%S-")+time_min,"%Y-%m-%d-%H-%S-%M"))
            return time
        elif u'小时' in created_time:
            time_hour=str(24-int(re.findall(u'(\d*)小',created_time)[0]))
            time=mktime(strptime(strftime("%Y-%m-%d-%M-%S-")+time_hour,"%Y-%m-%d-%M-%S-%H"))
            return time
        elif u':' in created_time:
            time_hour_min=created_time
            time=mktime(strptime(strftime("%Y-%m-%d-%S-")+time_hour_min,"%Y-%m-%d-%S-%H:%M"))
            return time
        elif len(created_time)==5:
            time_mon_day=created_time
            time=mktime(strptime(strftime("%Y-%H-%M-%S-")+time_mon_day,"%Y-%H-%M-%S-%m-%d"))
            return time
        elif len(created_time)==10:
            time_year_mon_day=created_time
            time=mktime(strptime(strftime("%H-%M-%S-")+time_year_mon_day,"%H-%M-%S-%Y-%m-%d"))
            return time
        else:
            return None
        

    def get_feeds(self, uid, page):
        url = (self.url_format)%(uid, uid, uid, page)
        req=requests.request("GET", url, headers=self.headers)
        req.encoding=req.apparent_encoding
        return req.text

    def get_uid(self):
        uid = self.db_manager.dequeue_user()
        if uid is None:
            return None
        return uid[1]

# '''     def start(self):
#         self.run = True
#         t = threading.Thread(target=self.crawl_feeds, name=None)
#         self.threads.append(t)
#         # set daemon so main thread can exit when receives ctrl-c
#         t.setDaemon(True)
#         t.start() '''


    def crawl_feeds(self):
        self.run = True

        while self.run:
            uid = self.get_uid()
            print("start new user crawling")
            if uid is None:
                self.run = False
                break
            for page in range(1, MAX_PAGE):
                feeds_str = self.get_feeds(uid, page)
                feeds = json.loads(feeds_str)
                for feed in feeds['data']['cards']:
                    if feed['card_type'] != 9:
                        continue
                    try:                      
                        if 'mblog' in feed.keys():
                            self.feeds_db_manager.insert_feed(feed, self.get_time(feed['mblog']['created_at']))
                            print('--------\n' + feed['mblog']['user']['screen_name'] + '\n--------\n' + re.sub(r'<.*?>','',feed['mblog']['text']))
                        else: continue
                    except Exception as err:
                        print(err)
                        continue
                    # item_id = feed['itemid']
                    # scheme = feed['scheme']
                    # uid = feed['mblog']['user']['id']
                    # name = feed['mblog']['user']['screen_name']1
                    # profile_image_url = feed['mblog']['user']['profile_image_url']
                    # created_at = feed['mblog']['created_at']
                    # text = feed['mblog']['text']
                    # feed_id = feed['mblog']['id']
                    # reposts_count = feed['mblog']['reposts_count']
                    # comments_count = feed['mblog']['comments_count']
                    # attitudes_count = feed['mblog']['attitudes_count']
                    # page_info = feed['mblog']['page_info']
                    # pics = feed['mblog']['pics']

            time.sleep(CRAWL_DELAY)


if __name__ == '__main__':
    feeds_crawler = FeedsCrawler()
    feeds_crawler.crawl_feeds()