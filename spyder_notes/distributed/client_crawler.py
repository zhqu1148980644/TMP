import argparse
import collections
import json
#import multiprocessing
#from multiprocessing import  Queue    error: can't pickle _thread.lock objects
import socket
import sys
import threading
import time

import requests
from lxml import etree

from mongo_redis_mgr import MongoRedisUrlManager
from collections import deque
import os

sys.path.append(
    r"C:\Users\Zhongquan\Documents\Visual Studio 2015\Projects\spider-course-3\distributed")

parser = argparse.ArgumentParser(
    prog='CrawlerClient', description='Start a crawler client,first client must choose a website for server to control')
parser.add_argument('-S', '--host-all', type=str, nargs=1,
                    help='Host server for all services')
parser.add_argument('-H', '--host', type=str,default='localhost',
                    help='Crawler host server address, default is localhost')
parser.add_argument('-HP', '--hostport', type=int, default=25013,
                    help='Crawler host server port number, default is 25013')
parser.add_argument('-M', '--mongo', type=str,  default='localhost',
                    help='Mongo Server address, default is localhost')
parser.add_argument('-MP', '--mongoport', type=int,
                    default=27017, help='Mongo port number, default is 27017')
parser.add_argument('-R', '--redis', type=str, default='localhost9',
                    help='Redis server address, default is localhost')
parser.add_argument('-RP', '--redisport', type=int, 
                    default=6379, help='Redis port number, default is 6379')
parser.add_argument('-W', '--web',  type=str,default='http://www.mafengwo.cn',help='Choose the website you want to crawl, first time must choose a website')

args = parser.parse_args()

if args.host_all is not None:
    args.host = args.mongo = args.redis = args.host_all
host = args.host
hostport = args.hostport
mongo = args.mongo
mongoport = args.mongoport
redis = args.redis
redisport = args.redisport
web = args.web
print("website is {}".format(web))

class SocketClient:
    def __init__(self, server_ip, server_port):
        self.server_ip = server_ip
        self.server_port = server_port
        self.server=(self.server_ip,self.server_port)
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.setblocking(True)
        self.socket.connect(self.server)


    def send(self, request):
        try:
            # Create a TCP/IP socket
            self.socket.sendall(request.encode("utf-8"))
            print("send data\r\n{}".format(request))

            data = self.socket.recv(2048).decode("utf-8")

            return json.loads(data.encode("utf-8"))
        except socket.error as msg:
            print('Bind failed. Error information : {}'.format(msg))


class crawler:
    def __init__(self, host, hostport, mongo, mongoport, redis, redisport, web):
        self.status = "RUNNING"
        self.client_id = None
        self.enqued_num=0
        self.start=False    
        self.get=False
        self.socket = SocketClient(host, hostport)
        self.deque = deque()
        self.dbmanager = MongoRedisUrlManager(mongo, mongoport)
        self.dbmanager.enqueuUrl(web, 'new', 0)
        self.dir_name = 'web/'
        self.max_num_thread=5
        self.CRAWL_DELAY=5
        self.last_heartbeat_time=time.time()
        self.web=web
        self.client_id=None
        self.request_headers = {
            'host': "www.mafengwo.cn",
            'connection': "keep-alive",
            'cache-control': "no-cache",
            'upgrade-insecure-requests': "1",
            'user-agent': "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.95 Safari/537.36",
            'accept': "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
            'accept-language': "zh-CN,en-US;q=0.8,en;q=0.6"
        }       
        #start a thread for heartbeat which is  continual
        if not os.path.exists(self.dir_name):
            os.mkdir(self.dir_name)
        try:
            t = threading.Thread(target=self.heartbeat, args=())
            t.setDaemon(True)
            t.start()
        except Exception as err:
            print("failed to start thread HEARTBEAT ,error is "+str(err))
        time.sleep(30)
        if self.get==True:
            self.thread()
        #start multi_process num is equal to cpu_max
        
    #facing error not solved
    # def multi_process(self,cpu_max):
    #     print("started multi_process")
    #     process=[]

    #     for i in range(cpu_max):
    #         p=multiprocessing.Process(target=self.thread, name=None,daemon=True)
    #         process.append(p)

    #     for p in process:
    #         p.start()
    #         p.join()

    def thread(self):
        print("starting thread")
        threads=[]
        while True:
            if self.status=="RUNNING":
                                # first remove all finished running threads
                for t in threads:
                    if not t.is_alive():
                        threads.remove(t)
                if len(threads) >= self.max_num_thread:
                    time.sleep(self.CRAWL_DELAY)
                    continue
                try:
                    try:
                        curtask=self.deque.pop()
                        self.deque.append(curtask)
                    except:
                        curtask=None
                    if self.status=="RUNNING" and curtask is not None:
                        curtask=self.deque.pop()
                        t = threading.Thread(target=self.get_page_content, name=None, args=(curtask[0], curtask[1]))
                        threads.append(t)
                        t.setDaemon(True)
                        t.start()
                        continue                
                    else:
                        continue
            # set daemon so main thread can exit when receives ctrl-c

                except Exception as err:
                    print("Error: unable to start thread"+str(err))
            else:
                continue
    

    def get_page_content(self,cur_url, depth):
        print("downloading %s at level %d" % (cur_url, depth))
        links = []
        try:
            req = requests.request('GET', cur_url, headers=self.request_headers)
            req.encoding = req.apparent_encoding
            html_page = req.text
            filename = cur_url[7:].replace('/', '_')

        # Write page to local files system
            fo = open("%s%s.html" % (self.dir_name, filename), 'wb+')
            fo.write(html_page.encode("utf-8"))
            fo.close()

            self.dbmanager.finishUrl(cur_url)
        except Exception as err:
            print(err)
            return

        html = etree.HTML(html_page.lower())
        hrefs = html.xpath(u"//a")

        for href in hrefs:
            try:
                if 'href' in href.attrib:
                    val = href.attrib['href']
                    if val.find('javascript:') != -1:
                        continue
                    if val.startswith('http://') is False:
                        if val.startswith('/'):
                            val = self.web + val
                        else:
                            continue
                    if val[-1] == '/':
                        val = val[0:-1]
                    links.append(val)
                    while not (self.status=="RUNNING"):
                        time.sleep(5)
                    self.dbmanager.enqueuUrl(val, 'new', depth+1)
                    self.enqued_num+=1
            except ValueError:
                continue

        self.dbmanager.set_url_links(cur_url, links)

    def on_massage(self,server_response):
        request = server_response
        try:
            massage=request["MASSAGE"]
            if massage == "PAUSE" and self.status == "RUNNING":
                self.status = "PAUSED"
                print("receiving data {} from server".format(request))
            elif massage == "RESUME" and self.status == "PAUSED":
                self.status = "RUNNING"
                print("receiving data {} from server".format(request))
            elif massage == "WAIT" and self.status == "PAUSED":
                self.status = "PAUSED"
            elif massage == "REGISTERED" and self.client_id is None:
                self.client_id = request["CLIENT_ID"]
                print("receiving data {} from server".format(request))
            else:
                print("MASSAGE_TYPE is invalid")
        except:
            fetch_num=len(request["URLS"])
            if fetch_num>0:
                for i in request["URLS"]:
                    self.deque.append(i)
                    self.get=True
                print("receiving data {} from server".format(request))
            elif request == {}:
                print("normal HEARTBEAT response received")
            else:
                print("invalid request from server")
                return None

    def heartbeat(self):
        request = {}
        #register client in server

        if self.client_id is None:
            request["MASSAGE_TYPE"] = "REGISTER"
            request["CLIENT_STATUS"] = self.status
            server_response = self.socket.send(json.dumps(request))
            self.on_massage(server_response)
            self.last_heartbeat_time = time.time()
        #use while infinite loop to send massages like heartbeat and fetch_url
        while True:
            #if deque is empty ,URL_REQUEST is prior to HEARTBEAT ,and as a substitution
            if self.enqued_num>30:
                self.start=False

            if self.start==True:
                continue
            
            try:
                a1 = self.deque.pop()
                self.deque.append(a1)
            except:
                a1 = None
            time1 = time.time()
            if a1 is None and time1 - self.last_heartbeat_time >= 40:
                request["MASSAGE_TYPE"] = "URL_REQUEST"
                request["CLIENT_STATUS"] = self.status
                request["CLIENT_ID"]=self.client_id
                server_response = self.socket.send(json.dumps(request))
                self.on_massage(server_response)
                self.last_heartbeat_time = time.time()
            elif a1 is not None and time1 - self.last_heartbeat_time >= 40:
                request["MASSAGE_TYPE"] = "HEARTBEAT"
                request["CLIENT_STATUS"] = self.status
                request["CLIENT_ID"]=self.client_id               
                server_response = self.socket.send(json.dumps(request))
                self.on_massage(server_response)
                self.last_heartbeat_time = time.time()
            elif a1 is None:
                request["MASSAGE_TYPE"] = "URL_REQUEST"
                request["CLIENT_STATUS"] = self.status
                request["CLIENT_ID"]=self.client_id
                server_response = self.socket.send(json.dumps(request))
                self.on_massage(server_response)
                self.last_heartbeat_time = time.time()
                self.start=True
            else:
                continue

if __name__=='__main__':
    crawler=crawler(host, hostport, mongo, mongoport, redis, redisport, web)