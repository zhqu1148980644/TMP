import json
import sys
import threading
import time

import requests

from feeds_crawler import FeedsCrawler
from mysql_db_manager import CrawlDatabaseManager

sys.path.append(
    r"C:/Users/Zhongquan/Documents/Visual Studio 2015/Projects/spider-learning/weibo_mysql_mongo/")


start_uid = '1730077315'

CRAWL_DELAY = 2


class UsersCrawler:
    url_format = 'https://m.weibo.cn/api/container/getIndex?containerid=231051_-_followers_-_%s&page=%d'

#    querystring = {"version":"v4"}

#    payload = "------WebKitFormBoundary7MA4YWxkTrZu0gW\r\nContent-Disposition: form-data; name=\"version\"\r\n\r\nv4\r\n------WebKitFormBoundary7MA4YWxkTrZu0gW--"
    headers = {
        'host': "m.weibo.cn",
        'connection': "keep-alive",
        'cache-control': "no-cache",
        'upgrade-insecure-requests': "1",
        'user-agent': "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36",
        'accept': "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
        'accept-encoding': "gzip, deflate, sdch, br",
        'accept-language': "zh-CN,en-US;q=0.8,en;q=0.6",
        'cookie': "_T_WM=0c8015962736d2199e208ca8adb7d301; SCF=AgS4nly86VG3e5zq2Usv2iN_bQIUj-rGsjZvQJLMLobUOXiNKaU1wEUxFjfWYNVchEv1_4Mfh08RgGthig-4Qcg.; SUB=_2A253p1ZcDeRhGeNG71YS9S7Jwj-IHXVVaHoUrDV6PUJbkdANLXbgkW1NS0f7LHe4BMxiV6LodCnt1vITwWSST2DI; SUHB=0xnCvYrYJqVQyb; SSOLoginState=1520641555; M_WEIBOCN_PARAMS=uicode%3D20000174"
    }

    # response = requests.request("GET", url, data=payload, headers=headers, params=querystring)

    db_manager = None

    threads = []

    run = False

    kickstart = True

    user_count = 0

    max_threads = 10

    def __init__(self):
        self.db_manager = CrawlDatabaseManager()
        self.crawl_feeds = FeedsCrawler()

    def get_users(self, uid, page):
        url = (self.url_format) % (uid, page)
        response = requests.request("GET", url, headers=self.headers)
        response.encoding = response.apparent_encoding
        return response.text

    def get_uid(self):
        return self.db_manager.dequeue_user()

    def start(self):
        self.run = True
        t = threading.Thread(target=self.crawl_feeds.crawl_feeds(), name=None)
        self.threads.append(t)
        # set daemon so main thread can exit when receives ctrl-c
        t.setDaemon(True)
        t.start()

    def crawl_users(self):
        self.outrange = False
        self.run = True
        self.page = 1
        if self.kickstart:
            self.kickstart = False
            uid = start_uid
        else:
            uid = self.get_uid()[1]
        while self.run:
            print(self.page)
            count = 0
            user_str = self.get_users(uid, self.page)
            users = json.loads(user_str)
            if self.page == 1:
                index = 1
            else:
                index = 0
            try:
                page_count = len(users['data']['cards'][index]['card_group'])
            except:
                print("page %d has none follow information,break!" % self.page)
                break
            for i in range(page_count):
                user = users['data']['cards'][index]['card_group'][i]
                try:
                    name = user['user']['screen_name']
                    if name.startswith("#"):
                        continue
                    user_id = user['user']['id']
                    followers_count = user['user']['followers_count']
                    follow_count = user['user']['follow_count']
                    description = user['user']['description']
                    print(name)
                except:
                    continue
                if followers_count > 15*follow_count:
                    self.db_manager.enqueue_user(user_id=user_id,
                                                 name=name,
                                                 follow_count=follow_count,
                                                 followers_count=followers_count,
                                                 description=description)
                    self.user_count += 1
                    count += 1
                else:
                    continue
            self.page += 1
            time.sleep(CRAWL_DELAY)
        print(self.page)
        print("%d users were qnququed this time ,%d users have been enququed from the start" % (
            count, self.user_count))


user_crawler = UsersCrawler()
for i in range(100):
    user_crawler.crawl_users()
while True:
    for t in user_crawler.threads:
        t.join()
    for t in user_crawler.threads:
        if not t.is_alive():
            user_crawler.threads.remove(t)
    if len(user_crawler.threads) < user_crawler.max_threads:
        try:
            user_crawler.start()
            time.sleep(CRAWL_DELAY)
        except Exception as err:
            print(err)
    else:
        time.sleep(CRAWL_DELAY)
        continue
