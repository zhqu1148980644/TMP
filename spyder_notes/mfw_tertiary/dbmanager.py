import pymysql
import hashlib
from twisted.enterprise import adbapi
from twisted.internet import reactor

class CrawlDatabaseManager:

    DB_NAME = 'mfw_pro_crawl'

    SERVER_IP = 'localhost'

    TABLES = {}
    # create new table, using sql
    TABLES['urls'] = (
        '''CREATE TABLE IF NOT EXISTS `urls`(
        `index` int(11) NOT NULL AUTO_INCREMENT, 
        `url` varchar(512) NOT NULL,
        `md5` varchar(32) NOT NULL,
        `status` varchar(11) NOT NULL DEFAULT 'new', 
        `depth` int(11) NOT NULL,
        `queue_time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
        `done_time` timestamp NOT NULL DEFAULT 0 ON UPDATE CURRENT_TIMESTAMP,
        PRIMARY KEY (`index`),
        UNIQUE KEY `md5` (`md5`)
        ) ENGINE=InnoDB''')


    def __init__(self, max_num_thread):
        # connect mysql server
        try:
            cnx = pymysql.Connect(host=self.SERVER_IP, user='root',passwd='a19970507')
        except pymysql.Error as err:
            if err == pymysql.constants.ER.ACCESS_DENIED_ERROR:
                print("Something is wrong with your user name or password")
            elif err== pymysql.constants.ER.BAD_DB_ERROR:
                print("Database does not exist")
            else:
                print('Create Error ' + err)
            exit(1)

        cursor = cnx.cursor()

        # use database, create it if not exist
        try:
            cnx.select_db(self.DB_NAME)
        except pymysql.Error as err:
            print(err) # create database and table
            self.create_database(cursor)
            cnx.select_db(self.DB_NAME)
            self.create_tables(cursor)
            print("creating database success")
            
        finally:
            cursor.close()
            cnx.close()

        dbconfig = {
            "database":self.DB_NAME,
            "user":"root",
            "host":self.SERVER_IP,
            "passwd":'a19970507',
            "db":self.DB_NAME,
            "charset":"utf8"
        }
        
        self.cnxpool = adbapi.ConnectionPool('pymysql',**dbconfig)

    # create databse
    def create_database(self, cursor):
        try:
            cursor.execute(
                "CREATE DATABASE {} DEFAULT CHARACTER SET \'utf8\'".format(self.DB_NAME))
        except pymysql.Error as err:
            print("Failed creating database: {}".format(err))
            exit(1)
    # create table
    def create_tables(self, cursor):
        for name, ddl in self.TABLES.items():
            try:
                cursor.execute(ddl)
                print("Tables created")
            except pymysql.Error as err:
                    print('create tables error ' + err)

    # put an url into queue
    def enqueueUrl(self, url, depth):
        try:
            conn=self.cnxpool.connect()
            cursor=conn.cursor()
            num=cursor.execute("select * from urls where md5='%s'"% hashlib.md5(url.encode("utf-8")).hexdigest())
            if num == 0:
                add_url = ('''INSERT INTO urls (url, md5, depth) VALUES ("%s", "%s", %s)'''%(url, hashlib.md5(url.encode("utf-8")).hexdigest(), depth))
                result=cursor.execute(add_url)
                print("enqueued %s"%(url))
                cursor.execute("commit")   
            else :
                return None           
            cursor.close()
            self.cnxpool.disconnect(conn)
        except pymysql.Error as err:
            print(err)
            return None
    
    # get an url from queue
    def dequeueUrl(self, depth):
        try:
            conn=self.cnxpool.connect()
            cursor=conn.cursor()
            query = ("SELECT `index`, `url`, `depth` FROM urls WHERE status='new' and depth=%d ORDER BY `index`"%(depth))
            result1=cursor.execute(query)
            if result1 <= 0:
                return None
            row=cursor.fetchone()
            update_query = ("UPDATE urls SET `status`='downloading' WHERE `index`=%d") % (row[0])
            result2=cursor.execute(update_query)
            cursor.execute("commit")
            print("dequeued %s ,still left %d need to be downloaded "%(str(row[1]),result1))
            return row
        except pymysql.Error as err:
            print(err)
            return None
        except Exception as err:
            print(err)
            return None



    def finishUrl(self, index):
        try:
            conn=self.cnxpool.connect()
            cursor=conn.cursor()              
            # we don't need to update done_time using time.strftime('%Y-%m-%d %H:%M:%S') as it's auto updated
            update_query = ("UPDATE urls SET `status`='done' WHERE `index`=%d") % (index)
            result3=cursor.execute(update_query)
            result4=cursor.execute('''select `index`, `url`, `depth` FROM urls WHERE `index`=%d'''%(index))
            result5=cursor.fetchone()
            cursor.execute("commit") 
            print("url:%s downloading complete"%(result5[1]))
            cursor.close()
            self.cnxpool.disconnect(conn)          
            return None
        except pymysql.Error as err:
            print(err)
            return None
