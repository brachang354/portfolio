"""
This will be the backend for the song list app

Data stored in SQLite should like similar to this:
Song Title      Genre       Song Artist     Date released
Cool Song       Rock        John Smith      10-20-1998

Will be created with the following SQL:
    CREATE TABLE songlist (song_title text, genre text, song_artist text, date_released text)

"""
from datetime import date
from .Model import Model
import sqlite3
DB_FILE = 'entries.db'    # file for our Database

class model(Model):
    def __init__(self):
        """
        This will check to make sure the database exists.
        Else it will create a new table for our song list
        """
        connection = sqlite3.connect(DB_FILE)
        cursor = connection.cursor()
        try:
            cursor.execute("select count(rowid) from songlist")
        except sqlite3.OperationalError:
            cursor.execute("create table songlist (song_title text, genre text, artist text, date_released text)")
        cursor.close()

    def select(self):
        """
        Gets all rows from the database
        Each row contains: song_title, genre, artist, date_released
        :return: List of lists containing all rows of database
        """
        connection = sqlite3.connect(DB_FILE)
        cursor = connection.cursor()
        cursor.execute("SELECT * FROM songlist")
        return cursor.fetchall()

    #def insert(self, name, email, message):
    def insert(self, song_title, genre, artist, date_released):
        """
        Inserts entry into database
        :param song_title: String
        :param genre: String
        :param artist: String
        :param date_released: String
        :return: none
        :raises: Database errors on connection and insertion
        """
        #params = {'name':name, 'email':email, 'date':date.today(), 'message':message}
        params = {'song_title':song_title, 'genre':genre, 'artist':artist, 'date_released':date_released}
        connection = sqlite3.connect(DB_FILE)
        cursor = connection.cursor()
        #cursor.execute("insert into guestbook (name, email, signed_on, message) VALUES (:name, :email, :date, :message)", params)
        cursor.execute("insert into songlist (song_title, genre, artist, date_released) VALUES (:song_title, :genre, :artist, :date_released)", params)

        connection.commit()
        cursor.close()
        return True
