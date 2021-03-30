import argparse
import hashlib
import json
import select
import socket
import sys
import threading
import time

import networkx as nx
import redis
from pymongo import MongoClient

parser = argparse.ArgumentParser(
    prog="SPIDER_MASTER", description="Create socket server and  automatically  distribute orders")
parser.add_argument('-H', '--host', default='localhost', type=str,
                    nargs=1, help="server host,default is \'localhost\'")
parser.add_argument('-P', '--port', default=25013, nargs=1, type=int,
                    help="choose a port for server to listen connection from lient,default is 25013")
parser.add_argument('-M', '--mongo', default='127.0.0.1', type=str,
                    nargs=1, help="choose your mongodb host,default host is 127.0.0.1")
parser.add_argument('-MP', '--mongoport', default=27017,
                    type=int, nargs=1, help="mongodb port default is 27017")
parser.add_argument('-R', '--redishost', default='127.0.0.1', type=str,
                    nargs=1, help="choose your redis host,default host is 127.0.0.1")
parser.add_argument('-RP', '--redisport', default=6379,
                    type=int, nargs=1, help="redis port default is 6379")

args = parser.parse_args()

host = args.host
port = args.port
mongohost = args.mongo
mongoport = args.mongoport
redishost = args.redishost
redisport = args.redisport


class CrawlMaster:


    def __init__(self, host, port, mongohost, mongoport, redishost, redisport):
        mongo_client = MongoClient(mongohost, mongoport)
        self.mongodb = mongo_client.spider
        self.redis_pool = redis.ConnectionPool(host=redishost, port=redisport)
        self.redis_client = redis.StrictRedis(
            connection_pool=self.redis_pool, decode_responses=True)
        self.clients = {}
        self.is_checking=False
        self.check_start=False
        self.last_index=0
        self.server = ServerSocket(self.on_message, host, port)
        t=threading.Thread(target=self.timeout_check)
        t.setDaemon(True)
        t.start()
        t.join()

    def timeout_check(self):
        while True:
            for key,value in self.clients.items():
                time1 =time.time()
                if time1 - value["LAST_HEARTBEAT_TIME"] > 50:
                    del self.clients[key]

    def on_message(self,s,data):
        request = data
        response = {}
        if self.check_start:
            try:
                tp=threading.Thread(target=self.compute_pagerank,args=())
                tp.start()
            finally:
                self.check_start=False
        #when server is not compputing pagerange 
        if request["CLIENT_STATUS"] == "RUNNING" and not self.is_checking:
            try:
                # register client in master
                if request["MASSAGE_TYPE"] == "REGISTER":
                    try:
                        client_id=request["CLIENT_ID"]
                    except:
                        client_id=None
                    if client_id is None:
                        response["CLIENT_ID"] = self.get_free_id()
                        client = {}
                        client["CLIENT_ID"] = response["CLIENT_ID"]
                        client["CLIENT_STATUS"] = request["CLIENT_STATUS"]
                        self.clients[response["CLIENT_ID"]] = client
                        response["MASSAGE"] = "REGISTERED"
                        time2 = time.time()
                        try:
                            a=self.clients[response["CLIENT_ID"]]["LAST_REORDER_TIME"]
                        except:
                            a=None
                        try:
                            self.clients[response["CLIENT_ID"]]["LAST_HEARTBEAT_TIME"]
                        except:
                            b=None
                        if a is None:
                            self.clients[response["CLIENT_ID"]
                                         ]["LAST_REORDER_TIME"] = time2

                        if b is None:
                            self.clients[response["CLIENT_ID"]
                                         ]["LAST_HEARTBEAT_TIME"] = time2
                    else:
                        response["MASSAGE"] = "CLIENT_ID_ALREADY_EXISTS"
                    return json.dumps(response)
                # handling heartbeat signal,check connection lost and reorder time
                elif request["MASSAGE_TYPE"] == "HEARTBEAT":
                    time3 = time.time()
                    self.clients[request["CLIENT_ID"]
                                 ]["LAST_HEARTBEAT_TIME"] = time3

                    if (time3 - self.clients[request["CLIENT_ID"]]["LAST_REORDER_TIME"]) > 600:
                        response["MASSAGE"] = "PAUSE"
                        self.is_checking = True
                        self.check_start=True
                    response["MASSAGE"]="HEARTBEAT"
                    return json.dumps(response)
                # handling fetch_url request and return urls
                elif request["MASSAGE_TYPE"] == "URL_REQUEST":
                    time4 = time.time()

                    self.clients[request["CLIENT_ID"]]["LAST_HEARTBEAT_TIME"] = time4

                    if (time4 - self.clients[request["CLIENT_ID"]]["LAST_REORDER_TIME"]) > 600:
                        response["MASSAGE"] = "PAUSE"
                        self.is_checking = True
                        self.check_start=True
                    elif (time4 - self.clients[request["CLIENT_ID"]]["LAST_REORDER_TIME"]) < 600:
                        response["URLS"] = self.get_url()
                    else: 
                        pass
                    return json.dumps(response)
                else:
                    print("not a valid massage type")
            except Exception as err:
                print(err)
        #when client has paused by server and pagerank computing has completed,restart clinet crawl
        elif request["CLIENT_STATUS"]=="PAUSED" and not self.is_checking:
            response["MASSAGE"] = "RESUME"
            return json.dumps(response)
        #pagerank computing has not yet complete ,tell client to wait
        else:
            response["MASSAGE"] = "WAIT"
            return json.dumps(response)


    # get an id for client
    def get_free_id(self):
        i = 1
        try:
            length=len(self.clients)
            i += length
        except:
            pass
        return str(i)
    #compute pagerank and update pr information
    def compute_pagerank(self):
        print("starting computing pagerank")
        time.sleep(10)
        g = nx.DiGraph()
        cursor = self.mongodb.urlpr.find()
        for site in cursor:
            url = site['url']
            links = site['links']
            for link in links:
                g.add_edge(url, link)
        pageranks = nx.pagerank(g, 0.9)
        for url, pr in pageranks.items():
            print('updating %s pr: %f' % (url, pr))
            record = {'pr': pr}
            self.mongodb.mfw.update_one({'_id': hashlib.md5(url.encode("utf-8")).hexdigest()}, {
                                        '$set': record}, upsert=False)
        for client in self.clients.keys():
            self.clients[client]["LAST_REORDER_TIME"] = time.time()
        self.is_checking=False
        print("pagerank computing is done")
    #fetch urls from redis database
    def get_url(self):
        list=[]
        count=0
        length1=self.redis_client.hlen("tmp_urls")
        for i in range(self.last_index+1,length1+1):           
            string=self.redis_client.hget("tmp_urls",str(i)).decode("utf-8")
            key=string.split(",")[0]
            value=int(string.split(",")[1])

            if not self.redis_client.exists(key):
                self.redis_client.set(key,value)
                list.append([key,value])
                count+=1
            if count >=15:
                self.last_index=i
                break
        return list




class ServerSocket:
    # use on_massage func to handle the response of data which send by clinet
    def __init__(self, on_massage,host, port):
        #function handling client requset
        self.on_massage = on_massage
        self.is_checking=False
        self.check_start=False
        # TCP IPV4
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
        self.server.setblocking(True)
        self.server_address = (host, port)
        self.server.bind(self.server_address)
        self.server.listen(5)
        print("starting up on %s port: %s" % self.server_address)

        self.inputs = [self.server]
    
        while self.inputs:
            # select func  automatically return  readble sockets in inputs and save it into readable lsit
            readable, writable, exceptional = select.select(
                self.inputs,[], [])
            for s in readable:
                # server become readable means one clinet has send connect requsets
                if s is self.server:
                    connection,client_address = s.accept()
                    print("new connection from {}".format(str(client_address)))
                    t=threading.Thread(target=self.handle_client,args=(connection,))
                    t.setDaemon(True)
                    t.start()
    #create thread for each socket collected from select function
    def handle_client(self,connection):
        s=connection
        while True:
            try:
                data = s.recv(1024).decode("utf-8")
                data = json.loads(data)
                if not data:
                    continue

                #print request from client which contains information of RUNNING
                try:
                    if data["CLIENT_STATUS"]=="RUNNING":
                        print("receiving live data {} from {}".format(data,s.getpeername()))
                except:
                    pass

                response=self.on_massage(s,data)

                s.send(response.encode("utf-8"))
                response_json=json.loads(response)
                    #print massage send to client by server except for WAIT
                try:
                    if "URLS" in response_json.keys():
                        print("sending {} to {}".format(response_json["URLS"],s.getpeername()))
                except:
                    massage=response_json["MASSAGE"]
                    if massage != "WAIT":
                        print("sending massage {} to {}".format(massage,s.getpeername()))
            except Exception as err:
                    print("expecting exceptional conditions for {} close connection".format(
                    s.getpeername()))
                    print(err)
                    break
 

crawl_master = CrawlMaster(host, port,  mongohost,
                           mongoport, redishost, redisport)
