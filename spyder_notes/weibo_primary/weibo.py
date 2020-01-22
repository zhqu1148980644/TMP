# -*- coding: utf-8 -*-
import hashlib
import re
import threading
import time
from collections import deque

from lxml import etree
from pybloom_live import BloomFilter

from selenium import webdriver
from selenium.webdriver.common.desired_capabilities import DesiredCapabilities

user_agent = (
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_8_4) " +
    "AppleWebKit/537.36 (KHTML, like Gecko) Chrome/29.0.1547.57 Safari/537.36"
)
dcap = dict(DesiredCapabilities.PHANTOMJS)
dcap["phantomjs.page.settings.userAgent"] = user_agent
Phantomjs_path="C:/Program Files (x86)/Python36-32/phantomjs-2.1.1-windows/bin/phantomjs.exe"

feeds_crawler = webdriver.PhantomJS(desired_capabilities=dcap,executable_path=Phantomjs_path)
feeds_crawler.set_window_size(1920, 1200)  # optional
user_crawler = webdriver.PhantomJS(desired_capabilities=dcap,executable_path=Phantomjs_path)
user_crawler.set_window_size(1920, 1200)  # optional

domain = "weibo.com"
url_home = "http://" + domain

download_bf = BloomFilter(1024*1024*16, 0.01)
cur_queue = deque()

# feeds_crawler.find_element_by_class_name('WB_detail')
# time = feeds_crawler.find_elements_by_xpath('//div[@class="WB_detail"]/div[@class="WB_from S_txt2"]/a[0]').text

seed_user = 'http://weibo.com/yaochen'

min_mblogs_allowed = 100
max_follow_fans_ratio_allowed = 3

def extract_user(users):
    print('extract user')
    for i in range(0,20):
        user_crawler.save_screenshot("test.png")
        for user_element in user_crawler.find_elements_by_xpath('//li[@class="follow_item S_line2"]'):
            print("提取该用户信息")
            tried = 0
            while tried < 3:
                try:
                    user = {}
                    user['follows'] = re.findall(r'(\d+)', user_element.find_element_by_xpath('.//div[@class="info_connect"]/span').text)[0]
                    user['follows_link'] = user_element.find_element_by_xpath('.//div[@class="info_connect"]/span//a').get_attribute('href')
                    user['fans'] = re.findall(r'(\d+)', user_element.find_elements_by_xpath('.//div[@class="info_connect"]/span')[1].text)[0]
                    user['fans_link'] = user_element.find_elements_by_xpath('.//div[@class="info_connect"]/span//a')[1].get_attribute('href')
                    user['mblogs'] = re.findall(r'(\d+)', user_element.find_elements_by_xpath('.//div[@class="info_connect"]/span')[2].text)[0]
                    user_link = user_element.find_element_by_xpath('.//div[contains(@class,"info_name")]/a')
                    user['link'] = re.findall(r'(.+)\?', user_link.get_attribute('href'))[0]
                    if user['link'][:4] != 'http':
                        user['link'] = domain + user['link']
                    user['name'] = user_link.text
                    user['icon'] = re.findall(r'/([^/]+)$', user_element.find_element_by_xpath('.//dt[@class="mod_pic"]/a/img').get_attribute('src'))[0]
                    # name = user_element.find_element_by_xpath('.//a[@class="S_txt1"]')

                    print('--------------------')
                    print(user['name'] + ' follows: ' + user['follows'] + ' blogs:' + user['mblogs'])
                    print(user['link'])

                    # 如果微博数量少于阈值或者关注数量与粉丝数量比值超过阈值，则跳过
                    if int(user['mblogs']) < min_mblogs_allowed or int(user['follows'])/int(user['fans']) > max_follow_fans_ratio_allowed:
                        break

                    enqueueUrl(user['link'])
                    users.append(user)
                    break
                except Exception as e:
                    print(e)
                    time.sleep(1)
                    tried += 1
        if go_next_page(user_crawler) is False:
            return users

    return users

def extract_feed(feeds):
    for i in range(0,5):      #翻5页
        scroll_to_bottom()
        for element in feeds_crawler.find_elements_by_class_name('WB_detail'):
            tried = 0
            while tried < 3:
                try:
                    feed = {}
                    feed['time'] = element.find_element_by_xpath('.//div[@class="WB_from S_txt2"]').text
                    feed['content'] = element.find_element_by_xpath('.//div[@class="WB_text W_f14"]').text
                    feed['image_names'] = []
                    for image in element.find_elements_by_xpath('.//li[contains(@class,"WB_pic")]/img'):
                        feed['image_names'].append(re.findall('/([^/]+)$', image.get_attribute('src')))
                    feeds.append(feed)
                    print('--------------------')
                    print(feed['time'])
                    print(feed['content'])
                    break
                except Exception:
                    tried += 1
                    time.sleep(1)
        if go_next_page(feeds_crawler) is False:
            return feeds

def scroll_to_bottom():
    # 最多尝试 20 次滚屏
    print('scroll down')
    for i in range(0,50):
        # print 'scrolling for the %d time' % (i)
        feeds_crawler.execute_script('window.scrollTo(0, document.body.scrollHeight)')
        html = feeds_crawler.page_source
        tr = etree.HTML(html)
        next_page_url = tr.xpath('//a[contains(@class,"page next")]')
        if len(next_page_url) > 0:
            return next_page_url[0].get('href')
        if len(re.findall('点击重新载入', html)) > 0:
            print('scrolling failed, reload it')
            feeds_crawler.find_element_by_link_text('点击重新载入').click()
        time.sleep(1)

def go_next_page(cur_driver):
    try:
        next_page = cur_driver.find_element_by_xpath('//a[@class="page next S_txt1 S_line1"]').get_attribute('href')
        print('next page is ' + next_page)
        cur_driver.get(next_page)
        time.sleep(3)
        return True
    except Exception:
        print('next page is not found')
        return False

def fetch_user(user_link):
    print('downloading ' + user_link)
    feeds_crawler.get(user_link)
    time.sleep(5)

    # 提取用户姓名
    account_name = feeds_crawler.find_element_by_xpath('//h1[1]').text

    #photo = get_element_by_xpath(feeds_crawler, '//p[@class="photo_wrap"]/img')[0].get('src')
    photo = feeds_crawler.find_element_by_xpath('//p[@class="photo_wrap"]/img[1]').get_attribute('src')
    account_photo = re.findall('/([^/]+)$', photo)    

    # 提取他的关注主页
    follows_link = get_element_by_xpath(feeds_crawler, '//a[@class="t_link S_txt1"]')[0].get('href')

    print('account: ' + account_name)
    print('photo url is'+str(account_photo))
    print('follows link is ' + follows_link)

    user_crawler.get( "http://"+follows_link )
    time.sleep(5)
    
    feeds = []
    users = []
    t_users = threading.Thread(target=extract_user, name=None, args=(users,))
    t_feeds = threading.Thread(target=extract_feed, name=None, args=(feeds,))
    
    t_users.setDaemon(True)
    t_feeds.setDaemon(True)
    
    t_users.start()
    t_feeds.start()
    
    t_users.join()
    t_feeds.join()
    t_users.join()

def get_element_by_xpath(cur_driver, path):
    tried = 0
    while tried < 6:
        html = cur_driver.page_source
        tr = etree.HTML(html)
        elements = tr.xpath(path)
        if len(elements) == 0:
            time.sleep(1)
            continue
        return elements

def login(username, password):
    print('Login')
    feeds_crawler.get(url_home)
    user_crawler.get(url_home)
    time.sleep(8)
    print('find click button to login')

    feeds_crawler.find_element_by_id('loginname').send_keys(username)
    feeds_crawler.find_element_by_name('password').send_keys(password)
    # 执行 click()
    feeds_crawler.find_element_by_xpath('//div[contains(@class,"login_btn")][1]/a').click()
    time.sleep(10)
    feeds_crawler.save_screenshot("screenshot1.png")
    time.sleep(10)
    verifycode1=input("please enter verifycode")
    try:
        feeds_crawler.find_elements_by_xpath('//*[@id="pl_login_form"]/div/div[3]/div[3]/div/input')[0].send_keys(verifycode1)
    except Exception as e:
        print(e)
        pass
    feeds_crawler.save_screenshot("3.png")
    feeds_crawler.find_element_by_xpath('//div[contains(@class,"login_btn")][1]/a').click()
    print("success!")
    # 也可以使用 execute_script 来执行一段 javascript
    # feeds_crawler.execute_script('document.getElementsByClassName("W_btn_a btn_32px")[0].click()')   
    user_crawler.find_element_by_id('loginname').send_keys(username)
    user_crawler.find_element_by_name('password').send_keys(password)
    # # 执行 click()
    user_crawler.find_element_by_xpath('//div[contains(@class,"login_btn")][1]/a').click()
    time.sleep(10)
    user_crawler.save_screenshot("screenshot2.png")
    time.sleep(10)
    verifycode2=input("please enter verifycode")
    user_crawler.find_elements_by_xpath('//*[@id="pl_login_form"]/div/div[3]/div[3]/div/input')[0].send_keys(verifycode2)
    user_crawler.save_screenshot("4.png")
    user_crawler.find_element_by_xpath('//div[contains(@class,"login_btn")][1]/a').click()
    #for cookie in feeds_crawler.get_cookies():
    #user_crawler.add_cookie(cookie)

def enqueueUrl(url):
    try:
        md5v = hashlib.md5(url.encode("utf-8")).hexdigest()
        if md5v not in download_bf:
            print(url + ' is added to queue')
            cur_queue.append(url)
            download_bf.add(md5v)
        # else:
            # print 'Skip %s' % (url)
    except ValueError:
        pass

def dequeuUrl():
    return cur_queue.popleft()

def crawl():
    while True:
        url = dequeuUrl()
        fetch_user(url)

if __name__ == '__main__':
    enqueueUrl(seed_user)
    login('13125928026', 'cxyLOVE19970507')
    crawl()
    feeds_crawler.close()
    user_crawler.close()
