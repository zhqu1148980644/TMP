import hashlib
import time
from datetime import datetime, timedelta

import redis
from pymongo import ASCENDING, DESCENDING, IndexModel, MongoClient

#redis set "urls" as a filter ignore duplicate urls
#use redis hashset "tmp_urls" to fetch urls and save to redis key-value as urls have send to client

class MongoRedisUrlManager:

    def __init__(self, server_ip='localhost',port=27017,client=None,):
        """
        client: mongo database client
        expires: timedelta of amount of time before a cache entry is considered expired
        """
        # if a client object is not passed 
        # then try connecting to mongodb at the default localhost port 
        self.client = MongoClient(server_ip, port) if client is None else client
        self.db=self.client.spider
        self.redis_pool=redis.ConnectionPool(host='localhost',port=6379)
        self.redis_client = redis.StrictRedis(connection_pool=self.redis_pool,decode_responses=True) 
        #create collection to store cached webpages,
        # which is the equivalent of a table in a relational database

        # create index if db is empty
        if self.db.mfw.count() is 0:
            self.db.mfw.create_index([("status", ASCENDING), 
                ("pr", DESCENDING)])


    def dequeueUrl(self):
        record = self.db.mfw.find_one_and_update(
            { 'status': 'new'}, 
            { '$set': { 'status' : 'downloading'} }, 
                upsert=False, 
                sort=[('pr', DESCENDING)], # sort by pr in descending 
                returnNewDocument= False
        )
        if record:
            return record
        else:
            return None

    def enqueuUrl(self, url, status, depth):
        try:
            value='%s,%s'%(url,str(depth))
            if not self.redis_client.sismember("urls",url):
                try:
                    self.redis_client.sadd("urls",url)
                except:
                    pass
                try:
                    len=self.redis_client.hlen("tmp_urls")
                except:
                    len=0
                self.redis_client.hsetnx("tmp_urls",str(len+1),value)
                self.db.mfw.insert({
                    '_id': hashlib.md5(url.encode("utf-8")).hexdigest(), 
                    'url': url, 
                    'status': status, 
                    'queue_time': datetime.utcnow(), 
                    'depth': depth,
                    'pr': 0
                })
                # print("enqued {},depth:{}".format(url,depth))
                return True
            else:
                # print("{} already exists in set urls".format(url))
                return False
        except Exception as err:
            print(err)

    def finishUrl(self, url):
        record = {'status': 'done', 'done_time': datetime.utcnow()}
        self.db.mfw.update({'_id': hashlib.md5(url.encode("utf-8")).hexdigest()}, {'$set': record}, upsert=False)
        print("downloaded {}".format(url))

    def set_url_links(self, url, links):
        self.db.urlpr.insert({
            '_id': hashlib.md5(url.encode("utf-8")).hexdigest(), 
            'url': url, 
            'links': links
        })

    def clear(self):
        self.db.mfw.drop()
