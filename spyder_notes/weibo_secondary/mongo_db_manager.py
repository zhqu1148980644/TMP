import datetime
from datetime import datetime
from pymongo import MongoClient


class FeedsMongoManager:
    def __init__(self, SERVER_IP = 'localhost', port=27017, client=None):
        # if a client object is not passed
        # then try connecting to mongodb at the default localhost port
        self.client = MongoClient(SERVER_IP, port) if client is None else client
        #create collection to store cached webpages,
        # which is the equivalent of a table in a relational database
        self.db = self.client.spider

    def get_feed_by_user(self, uid, offset, size):
        record = self.db.weibo.find_one(
            {'status': 'new'}
        )
        if record:
            return record
        else:
            return None

    def insert_feed(self, feed, time):
        try:
            self.db.weibo.insert({'uid':feed['mblog']['user']['id'],
                                  'itemid':feed['itemid'],
                                  'scheme':feed['scheme'],
                                  'created_at':feed['mblog']['created_at'],
                                  'text': feed['mblog']['text'],
                                  'feed_id':feed['mblog']['id'],
                                  'reposts_count':feed['mblog']['reposts_count'],
                                  'attitudes_count':feed['mblog']['attitudes_count'],
                                  })
        except Exception as e:
            print(e)
            pass
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
    def clear(self):
        self.db.weibo.drop()