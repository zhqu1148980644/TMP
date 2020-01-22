from twisted.enterprise import adbapi
import hashlib
import pymysql


class CrawlDatabaseManager:

    DB_NAME = 'weibo_crawl'

    SERVER_IP = 'localhost'

    TABLES = {}
    # create new table, using sql
    TABLES['uids'] = (
        '''CREATE TABLE `uids` (
           `index` int(11) NOT NULL AUTO_INCREMENT,
           `user_id` varchar(32) NOT NULL,
           `status` varchar(11) NOT NULL DEFAULT 'new',
           `queue_time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
           `done_time` timestamp NOT NULL DEFAULT 0 ON UPDATE CURRENT_TIMESTAMP,
           PRIMARY KEY (`index`)
        ) ENGINE=InnoDB
        charset=utf8mb4''')

    TABLES['users'] = (
        '''CREATE TABLE `users` (
          `index` int(11) NOT NULL AUTO_INCREMENT,
          `user_id` varchar(32) NOT NULL,
          `name` varchar(32) NOT NULL,
          `followers_count` int(11) NOT NULL,
          `follow_count` int(32) NOT NULL,
          `description` varchar(612) NOT NULL,
          PRIMARY KEY (`index`)
          UNIQUE KEY (`user_id`)
        ) ENGINE=InnoDB
        charset=utf8mb4''')

    def __init__(self):
        # connect mysql server
        try:
            cnx = pymysql.Connect(host=self.SERVER_IP, user='root', password='a19970507',charset="utf8")
        
        except pymysql.Error as err:
            if err == pymysql.constants.ER.ACCESS_DENIED_ERROR:
                print("Something is wrong with your user name or password")
            else:
                print('Create Error ' + err)


        cursor=cnx.cursor()
        # use database, create it if not exist
        try:
            cnx.select_db(self.DB_NAME)
        except pymysql.Error as err:
                # create database and table
                self.create_database(cursor)
                cnx.select_db(self.DB_NAME)
                self.create_tables(cursor)
                print("created database")


        finally:
            cursor.close()
            cnx.close()

        dbconfig = {
            "database": self.DB_NAME,
            "user":     "root",
            "password": "a19970507",
            "host":     self.SERVER_IP,
            "charset":  "utf8"
        }
        self.cnxpool =adbapi.ConnectionPool('pymysql',**dbconfig)


    # create databse
    def create_database(self, cursor):
        try:
            cursor.execute(
                "CREATE DATABASE {} DEFAULT CHARACTER SET 'utf8'".format(self.DB_NAME))
        except pymysql.Error as err:
            print("Failed creating database: {}".format(err))
            exit(1)

    def create_tables(self, cursor):
        for name, ddl in self.TABLES.items():
            try:
                cursor.execute(ddl)
                print('Tables created')
            except pymysql.Error as err:
                if err == pymysql.constants.ER.TABLE_EXISTS_ERROR:
                    print('create tables error ALREADY EXISTS')
                else:
                    print('create tables error ' + str(err))



    # insert user into queue
    def enqueue_user(self, user_id, **kwargs):
        con = self.cnxpool.connect()
        cursor = con.cursor()
        try:
            add_uid = ("REPLACE INTO uids (user_id) VALUES (%s)")
            cursor.execute("INSERT INTO uids (user_id) VALUES (%s)"%user_id)
            keys = 'user_id'
            values = (user_id,)
            values_stmt = '%s'
            for key in kwargs:
                keys += ', ' + key
                values_stmt += ', %s'
                values += (kwargs[key],)
            add_user_info = ("REPLACE INTO users (%s) VALUES ") % (keys)
            add_user_info += '(' + values_stmt + ')'

            cursor.execute(add_user_info, values)
            # commit this transaction, please refer to "mysql transaction" for more info
            con.commit()
        except pymysql.Error as err:
            print("enqueueUrl" + str(err))
            return
        finally:
            cursor.close()



    # get an user from queue
    def dequeue_user(self):
        con = self.cnxpool.connect()
        cursor = con.cursor()
        try:
            # use select * for update to lock the rows for read
            query = ("SELECT `index`, `user_id` FROM uids WHERE status='new' ORDER BY `index` ASC LIMIT 1 FOR UPDATE")
            count=cursor.execute(query)
            if count == 0:
                return None
            row = cursor.fetchone()
            if row is None:
                return None
            update_query = ("UPDATE uids SET `status`='downloading' WHERE `index`=%d") % (row[0])
            cursor.execute(update_query)
            con.commit()
            return row
        except pymysql.Error as err:
            print(err)
            return None
        finally:
            cursor.close()

    def finish_user(self, index):
        con = self.cnxpool.connect()
        cursor = con.cursor()
        try:
            # we don't need to update done_time using time.strftime('%Y-%m-%d %H:%M:%S') as it's auto updated
            update_query = ("UPDATE uids SET `status`='done' WHERE `index`=%d"% (index))
            cursor.execute(update_query)
            con.commit()
        except pymysql.Error as err:
            print(err)
            return
        finally:
            cursor.close()


if __name__ == '__main__':
    dbmanager = CrawlDatabaseManager()